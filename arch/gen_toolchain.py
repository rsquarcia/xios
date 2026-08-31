#!/usr/bin/env python3
"""
Generate a hierarchical CMake toolchain file from an FCM arch file.

Usage
-----
    python arch/gen_toolchain.py <arch>

The output includes the appropriate common/<family>.cmake file and only
emits the flags that differ from it (appended or overridden).

All translation rules (compiler renaming, flag mapping, FCM→CMake
incompatibility fixes) are encoded in this script.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------

# FCM placeholder defines that carry no semantic content
_STRIP_FLAGS: frozenset[str] = frozenset({"-D__NONE__", "-D__NONE_"})

# Libraries supplied by CMake find_package(NetCDF/HDF5/…) — drop from BASE_LD
_PACKAGE_LIBS: frozenset[str] = frozenset({
    "-lz", "-lcurl", "-lhdf5", "-lnetcdf", "-lnetcdff",
})

# Bare "-Wl" without a comma is a malformed FCM artifact (arch-X64_ATHENA)
_MALFORMED_LD: frozenset[str] = frozenset({"-Wl"})

# FCM uses the C MPI wrapper; CMake builds XIOS as C++ and needs the C++ one
_CXX_RENAME: dict[str, str] = {
    "mpicc":  "mpic++",
    "mpiCC":  "mpic++",
    "mpiicc": "mpiicpc",
}

# Column at which the quoted value starts in set() lines (cosmetic alignment)
_ALIGN_COL = 52

# ---------------------------------------------------------------------------
# Per-architecture overrides (only rules that cannot be derived generically)
# ---------------------------------------------------------------------------

_PER_ARCH: dict[str, dict] = {
    # Hardcoded oneapi + Cray MPICH -L/-l paths are superseded by MPI wrappers
    "arch-X64_ADASTRA_INTEL": {"drop_base_ld": True},
}

# ---------------------------------------------------------------------------
# Common-file baselines (loaded at import time from the actual common files)
#
# Each key is a family name (= common/<key>.cmake filename stem).
# Values are the flag tokens that the common file sets for each CMake variable.
# Variables absent from the dict are not set by the common file.
# ---------------------------------------------------------------------------

_SET_RE = re.compile(r'(?:set_flags|set)\((\w+)\s+(?:"([^"]*)"|(\S+))(?:\s+CACHE\s+\w+\s+"[^"]*")?(?:\s+FORCE)?\s*\)')


def _load_common_baselines(common_dir: Path) -> dict[str, dict[str, list[str]]]:
    """Parse all set() calls in common/*.cmake and return {family: {var: tokens}}."""
    baselines: dict[str, dict[str, list[str]]] = {}
    for path in sorted(common_dir.glob("*.cmake")):
        fields: dict[str, list[str]] = {}
        for raw in path.read_text().splitlines():
            line = raw.split("#")[0]            # strip comments
            m = _SET_RE.search(line)
            if m:
                var   = m.group(1)
                value = m.group(2) if m.group(2) is not None else (m.group(3) or "")
                fields[var] = value.split()
        baselines[path.stem] = fields
    return baselines


_COMMON_BASELINE: dict[str, dict[str, list[str]]] = _load_common_baselines(
    Path(__file__).parent / "toolchains" / "common"
)

# Human-readable description for each family (used in the file header)
_FAMILY_LABEL: dict[str, str] = {
    "gcc-openmpi":   "GCC + OpenMPI",
    "intel-openmpi": "Intel + OpenMPI",
    "intel-impi":    "Intel + IntelMPI",
    "cray-mpich":    "Cray + MPICH",
}

# ---------------------------------------------------------------------------
# Arch display-name formatter
# ---------------------------------------------------------------------------

# Whole-stem overrides (arch stem → exact display string)
_ARCH_DISPLAY: dict[str, str] = {
    "XC30_Cray": "XC30_Cray",
    "XE6_LYNX":  "XE6_Lynx",
}

# Name-part overrides (uppercase name token → display string)
_NAME_DISPLAY: dict[str, str] = {
    "LSCE":     "LSCE",
    "CICLAD":   "CICLAD",
    "MESOIPSL": "MESOIPSL",
    "MACOSX":   "Mac OSX",
    "JEANZAY":  "Jean-Zay",
}


def _arch_display_name(stem: str) -> str:
    """
    Map a stripped arch stem to a readable header name.

    Pattern: <group>_<name>[_<kind>]  →  Name [(KIND)]

    Name is sentence-cased unless overridden in _NAME_DISPLAY.
    Kind preserves its original case; underscores are replaced with spaces.
    Whole-stem overrides in _ARCH_DISPLAY take priority.
    """
    if stem in _ARCH_DISPLAY:
        return _ARCH_DISPLAY[stem]
    parts = stem.split("_", 2)          # at most [group, name, kind]
    if len(parts) < 2:
        return stem.capitalize()
    name_raw = parts[1]
    name = _NAME_DISPLAY.get(name_raw, name_raw.capitalize())
    if len(parts) == 3:
        kind = parts[2].replace("_", " ")
        return f"{name} ({kind})"
    return name

# ---------------------------------------------------------------------------
# FCM parser
# ---------------------------------------------------------------------------


def parse_fcm(path: Path) -> dict[str, str]:
    """Return {KEY: value} for every active %KEY line in an FCM arch file."""
    fields: dict[str, str] = {}
    for raw in path.read_text().splitlines():
        line = raw.split("#")[0].strip()        # strip inline/full-line comments
        m = re.match(r"%(\w+)\s*(.*)", line)
        if m:
            fields[m.group(1)] = m.group(2).strip()
    return fields

# ---------------------------------------------------------------------------
# Compiler-family detection
# ---------------------------------------------------------------------------


def _bare_compiler(tokens: list[str]) -> str:
    """Extract the actual compiler binary, handling a leading scorep prefix."""
    if not tokens:
        return ""
    if tokens[0] == "scorep":
        try:
            idx = tokens.index("--user")
            return tokens[idx + 1] if idx + 1 < len(tokens) else ""
        except ValueError:
            return ""
    return tokens[0]


def detect_family(fields: dict[str, str]) -> str:
    """
    Return one of: "intel-impi", "intel-openmpi", "gcc-openmpi", "cray-mpich".

    Heuristic (in order):
      1. mpiicc / mpiifort in CCOMPILER / FCOMPILER  → Intel + IntelMPI
      2. CC in CCOMPILER                             → Cray + MPICH
      3. -traceback anywhere in flags                → Intel + OpenMPI
      4. -fbacktrace anywhere in flags               → GCC + OpenMPI
      5. default                                     → GCC + OpenMPI
    """
    ccomp = _bare_compiler(fields.get("CCOMPILER", "").split())
    fcomp = _bare_compiler(fields.get("FCOMPILER", "").split())
    all_flags = " ".join(fields.get(k, "") for k in (
        "BASE_CFLAGS", "DEV_CFLAGS", "DEBUG_CFLAGS",
        "BASE_FFLAGS", "DEV_FFLAGS", "DEBUG_FFLAGS",
    ))

    if ccomp == "mpiicc" or fcomp == "mpiifort":
        return "intel-impi"
    if ccomp == "CC":
        return "cray-mpich"
    if "-traceback" in all_flags:
        return "intel-openmpi"
    if "-fbacktrace" in all_flags:
        return "gcc-openmpi"
    return "gcc-openmpi"

# ---------------------------------------------------------------------------
# Compiler-field parsers
# ---------------------------------------------------------------------------


def _rename_cxx(raw: str) -> str:
    """Rename mpicc/mpiCC/mpiicc to their C++ equivalents.
    Absolute paths are returned verbatim (no binary rename)."""
    if raw.startswith("/"):
        return raw
    slash = raw.rfind("/")
    if slash >= 0:
        prefix, base = raw[: slash + 1], raw[slash + 1:]
        return prefix + _CXX_RENAME.get(base, base)
    return _CXX_RENAME.get(raw, raw)


def _scorep_split(tokens: list[str]) -> tuple[list[str], list[str]]:
    """Split 'scorep … --user <compiler> [flags]' into (launcher, rest)."""
    try:
        idx = tokens.index("--user")
        return tokens[: idx + 1], tokens[idx + 1:]
    except ValueError:
        return tokens[:-1], tokens[-1:]


def parse_ccompiler(field: str) -> tuple[str, list[str], list[str]]:
    """
    Parse %CCOMPILER.
    Returns (cxx_compiler, extra_cxx_flags, cxx_launcher_parts).

    Handles:
      plain   "mpicc"                          → mpic++, [], []
      ITAC    "mpicc -trace -DITAC -I$DIR"     → mpic++, [extra…], []
      Score-P "scorep … --user mpicc -DSCOREP" → mpic++, [-DSCOREP], [scorep…]
    """
    tokens = field.split()
    if not tokens:
        return "", [], []

    launcher: list[str] = []
    if tokens[0] == "scorep":
        launcher, tokens = _scorep_split(tokens)

    compiler = _rename_cxx(tokens[0])
    # Trailing tokens = per-compiler flags (ITAC: -trace -DITAC -I$DIR).
    # Drop -EP (FCM preprocessor flag, not passed to the C++ compiler).
    extra = [_env(t) for t in tokens[1:] if t != "-EP"]
    return compiler, extra, launcher


def parse_fcompiler(field: str) -> tuple[str, list[str], list[str]]:
    """Parse %FCOMPILER → (fc_compiler, extra_fc_flags, fc_launcher_parts)."""
    tokens = field.split()
    if not tokens:
        return "", [], []

    launcher: list[str] = []
    if tokens[0] == "scorep":
        launcher, tokens = _scorep_split(tokens)

    fc = tokens[0]                          # mpif90 / mpiifort – no renaming
    extra = [_env(t) for t in tokens[1:]]
    return fc, extra, launcher


def parse_linker(field: str) -> list[str]:
    """
    Parse %LINKER → extra linker flags.

    Strips:
      - the leading linker binary
      - the whole scorep launcher + compiler binary (Score-P)
      - -nofor-main  (CMake's Fortran main handling makes it unnecessary)
      - preprocessor -D* defines  (irrelevant to the linker)
    Translates $VAR → $ENV{VAR}.
    """
    tokens = field.split()
    if not tokens:
        return []

    start = 1                               # skip linker binary
    if tokens[0] == "scorep":
        try:
            idx = tokens.index("--user")
            start = idx + 2                 # skip --user + compiler binary
        except ValueError:
            start = len(tokens)

    return [
        _env(f)
        for f in tokens[start:]
        if f != "-nofor-main" and not f.startswith("-D")
    ]

# ---------------------------------------------------------------------------
# Flag-processing utilities
# ---------------------------------------------------------------------------


def _env(s: str) -> str:
    """Translate $VAR shell references to CMake $ENV{VAR}."""
    return re.sub(r"\$([A-Za-z_][A-Za-z0-9_]*)", r"$ENV{\1}", s)


def _strip_external_refs(tokens: list[str]) -> list[str]:
    """
    Remove -I (include paths), -L (library search paths), and any -l flags
    that immediately follow a -L group.  Handles both attached (-Lfoo) and
    space-separated (-L foo) forms.
    """
    result: list[str] = []
    i = 0
    after_L = False
    while i < len(tokens):
        t = tokens[i]
        # Space-separated: "-L /path" or "-I /path"
        if t in ("-L", "-I") and i + 1 < len(tokens) and not tokens[i + 1].startswith("-"):
            after_L = (t == "-L")
            i += 2
        # Attached: "-L/path" or "-I/path"
        elif t.startswith("-L") or t.startswith("-I"):
            after_L = t.startswith("-L")
            i += 1
        # -l immediately following a -L group
        elif after_L and t.startswith("-l"):
            i += 1
        else:
            after_L = False
            result.append(t)
            i += 1
    return result


def process_flags(raw: str, extra_strip: frozenset[str] = frozenset()) -> list[str]:
    """
    Tokenize raw FCM flags; merge split '-D MACRO' pairs;
    strip noise tokens; translate $VAR → $ENV{VAR}.
    """
    strip = _STRIP_FLAGS | extra_strip
    tokens = _strip_external_refs(raw.split())
    out: list[str] = []
    i = 0
    while i < len(tokens):
        t = tokens[i]
        # '-D' followed by a bare word (not another flag) → merge into '-DMACRO'
        if t == "-D" and i + 1 < len(tokens) and not tokens[i + 1].startswith("-"):
            t = "-D" + tokens[i + 1]
            i += 2
        else:
            i += 1
        t = _env(t)
        if t not in strip and not t.startswith("-std="):
            out.append(t)
    return out

# ---------------------------------------------------------------------------
# BASE_LD handling
# ---------------------------------------------------------------------------


def process_base_ld(
    raw: str,
    family: str,
    arch_overrides: dict,
) -> tuple[list[str], str | None]:
    """
    Returns (linker_flags, fortran_stdlib).

    Rules applied:
      - arch-specific drop_base_ld: entire value discarded (Adastra).
      - _PACKAGE_LIBS: dropped (provided by CMake find_package).
      - _MALFORMED_LD: dropped (bare -Wl without comma, Athena).
      - -lstdc++: moved to fortran_stdlib for GCC; dropped for Intel/Cray
        (Intel toolchain links the C++ runtime automatically).
    """
    if arch_overrides.get("drop_base_ld"):
        return [], None

    tokens = _strip_external_refs(raw.split())
    tokens = [t for t in tokens if t not in _PACKAGE_LIBS | _MALFORMED_LD | _STRIP_FLAGS]

    fortran_stdlib: str | None = None
    if "-lstdc++" in tokens:
        tokens.remove("-lstdc++")
        if family.startswith("gcc"):
            fortran_stdlib = "-lstdc++"

    return [_env(t) for t in tokens], fortran_stdlib

# ---------------------------------------------------------------------------
# CMake output helpers
# ---------------------------------------------------------------------------


def _set(var: str, value: str) -> str | None:
    if not value:
        return None
    pad = max(1, _ALIGN_COL - 4 - len(var))
    return f'set({var}{" " * pad}"{value}")'


def _set_flag(var: str, tokens: list[str]) -> str:
    """Like _set but always emits (even for empty token list)."""
    value = " ".join(tokens)
    pad = max(1, _ALIGN_COL - 10 - len(var))
    return f'set_flags({var}{" " * pad}"{value}")'


def _set_list(var: str, items: list[str]) -> str | None:
    if not items:
        return None
    pad = max(1, _ALIGN_COL - 4 - len(var))
    return f'set({var}{" " * pad}"{";".join(items)}")'


def _append(var: str, tokens: list[str]) -> str:
    value = " ".join(tokens)
    pad = max(1, _ALIGN_COL - 10 - len(var))
    return f'add_flags({var}{" " * pad}"{value}")'


def _section(title: str) -> str:
    bar = "-" * 75
    return f"\n# {bar}\n# {title}\n# {bar}"

# ---------------------------------------------------------------------------
# Flag diff
# ---------------------------------------------------------------------------


def _flag_diff(
    generated: list[str],
    baseline: list[str],
) -> tuple[str, list[str]]:
    """
    Compare generated tokens against the common-file baseline.

    Returns one of:
      ("same",     [])       – no output needed
      ("append",   extras)   – baseline is non-empty strict subset; emit string(APPEND)
      ("override", tokens)   – emit set() with the full generated value
    """
    if generated == baseline:
        return "same", []
    base_set = set(baseline)
    gen_set  = set(generated)
    if base_set == gen_set:
        return "same", []           # same elements, different order – treat as same
    if baseline and base_set < gen_set:
        extras = [t for t in generated if t not in base_set]
        return "append", extras
    return "override", generated

# ---------------------------------------------------------------------------
# Generator
# ---------------------------------------------------------------------------


def generate(fcm_path: Path) -> str:
    arch_name    = fcm_path.stem
    display_name = _arch_display_name(arch_name.removeprefix("arch-"))
    fields       = parse_fcm(fcm_path)
    overrides    = _PER_ARCH.get(arch_name, {})
    family       = detect_family(fields)
    baseline     = _COMMON_BASELINE[family]

    # -- Compilers ----------------------------------------------------------
    cxx, extra_cxx, cxx_launcher = parse_ccompiler(fields.get("CCOMPILER", ""))
    fc,  extra_fc,  fc_launcher  = parse_fcompiler(fields.get("FCOMPILER", ""))
    linker_extra = parse_linker(fields.get("LINKER", ""))

    # -- C++ flags ----------------------------------------------------------
    base_cxx = process_flags(fields.get("BASE_CFLAGS", ""))

    if "-D__XIOS_EXCEPTION" not in base_cxx:
        base_cxx.append("-D__XIOS_EXCEPTION")

    if family.startswith("intel") and "-diag-disable" not in base_cxx:
        base_cxx = ["-diag-disable", "1125", "-diag-disable", "279"] + base_cxx

    base_cxx.extend(extra_cxx)

    prod_cxx  = process_flags(fields.get("PROD_CFLAGS",  ""))
    dev_cxx   = process_flags(fields.get("DEV_CFLAGS",   ""))
    debug_cxx = process_flags(fields.get("DEBUG_CFLAGS", ""))

    # -- Fortran flags ------------------------------------------------------
    base_fc = process_flags(fields.get("BASE_FFLAGS", ""))

    if family.startswith("gcc"):
        has_line_ctrl = any(
            "free-line-length" in f or "free-form" in f for f in base_fc
        )
        if not has_line_ctrl:
            base_fc.append("-ffree-line-length-none")

    base_fc.extend(extra_fc)

    prod_fc  = process_flags(fields.get("PROD_FFLAGS",  ""))
    dev_fc   = process_flags(fields.get("DEV_FFLAGS",   ""))
    debug_fc = process_flags(fields.get("DEBUG_FFLAGS", ""))

    # -- Linker flags -------------------------------------------------------
    ld_flags, fortran_stdlib = process_base_ld(
        fields.get("BASE_LD", ""), family, overrides
    )

    linker_flags: list[str] = []
    if family.startswith("gcc"):
        linker_flags.append("-pthread")
    linker_flags.extend(ld_flags)
    linker_flags.extend(linker_extra)

    # -- Compute diffs against common-file baseline -------------------------
    flag_vars: list[tuple[str, list[str]]] = [
        ("CMAKE_CXX_FLAGS",                      base_cxx),
        ("CMAKE_CXX_FLAGS_RELEASE",              prod_cxx),
        ("CMAKE_CXX_FLAGS_RELWITHDEBINFO",       dev_cxx),
        ("CMAKE_CXX_FLAGS_DEBUG",                debug_cxx),
        ("CMAKE_Fortran_FLAGS",                  base_fc),
        ("CMAKE_Fortran_FLAGS_RELEASE",          prod_fc),
        ("CMAKE_Fortran_FLAGS_RELWITHDEBINFO",   dev_fc),
        ("CMAKE_Fortran_FLAGS_DEBUG",            debug_fc),
        ("CMAKE_EXE_LINKER_FLAGS",               linker_flags),
    ]

    appends:     list[str] = []
    overr_lines: list[str] = []

    for var, gen_toks in flag_vars:
        base_toks = baseline.get(var, [])
        status, payload = _flag_diff(gen_toks, base_toks)
        if status == "append":
            appends.append(_append(var, payload))
        elif status == "override":
            overr_lines.append(_set_flag(var, gen_toks))

    # CMAKE_Fortran_STANDARD_LIBRARIES is set-only (no append semantics)
    stdlib_gen  = [fortran_stdlib] if fortran_stdlib else []
    stdlib_base = baseline.get("CMAKE_Fortran_STANDARD_LIBRARIES", [])
    std_status, _ = _flag_diff(stdlib_gen, stdlib_base)
    if std_status == "override":
        overr_lines.append(_set_flag("CMAKE_Fortran_STANDARD_LIBRARIES", stdlib_gen))

    # Compiler overrides (only when the compiler differs from the common baseline,
    # e.g. an absolute path)
    cxx_base = (baseline.get("CMAKE_CXX_COMPILER") or [""])[0]
    fc_base  = (baseline.get("CMAKE_Fortran_COMPILER") or [""])[0]
    comp_overrides: list[str] = []
    if cxx != cxx_base:
        line = _set("CMAKE_CXX_COMPILER", cxx)
        if line:
            comp_overrides.append(line)
    if fc != fc_base:
        line = _set("CMAKE_Fortran_COMPILER", fc)
        if line:
            comp_overrides.append(line)
    if comp_overrides:
        overr_lines = comp_overrides + ([""] if overr_lines else []) + overr_lines

    # -- Assemble -----------------------------------------------------------
    bar = "-" * 75
    out: list[str] = [
        f"# {bar}",
        f"# Toolchain for {display_name} – {_FAMILY_LABEL[family]}",
        f"# {bar}",
        "",
        f'include("${{CMAKE_CURRENT_LIST_DIR}}/common/{family}.cmake")',
    ]

    if cxx_launcher or fc_launcher:
        out.append(_section("Compiler launcher"))
        for line in filter(None, [
            _set_list("CMAKE_CXX_COMPILER_LAUNCHER",     cxx_launcher),
            _set_list("CMAKE_Fortran_COMPILER_LAUNCHER", fc_launcher),
        ]):
            out.append(line)

    if appends:
        out.append(_section("Appended flags"))
        out.extend(appends)

    if overr_lines:
        out.append(_section("Overrides"))
        out.extend(overr_lines)

    return "\n".join(out) + "\n"

# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("arch",
                    help="Arch name, e.g. X64_JEANZAY")
    args = ap.parse_args()

    script_dir = Path(__file__).parent
    fcm_path   = script_dir / f"arch-{args.arch}.fcm"
    out_path   = script_dir / "toolchains" / f"arch-{args.arch}.cmake"

    if not fcm_path.exists():
        sys.exit(f"error: {fcm_path} not found")

    content = generate(fcm_path)

    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(content)
    print(f"Wrote {out_path}")


if __name__ == "__main__":
    main()
