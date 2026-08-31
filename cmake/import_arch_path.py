#!/usr/bin/env python3
# ---------------------------------------------------------------------------
# import_arch_path.py
# ---------------------------------------------------------------------------
#
# Bridges legacy FCM arch-<NAME>.path files into the environment variables
# expected by CMake's Find modules (cmake/Find*.cmake).
#
# arch.path files are bash fragments, not flat KEY=VALUE data: they reference
# other environment variables (e.g. ${NETCDF_DIR}) and sometimes use shell
# loops (see arch-LINUX_PAR.path), so they must be sourced, not parsed, to
# resolve correctly. Once sourced though, their variables carry FCM compiler
# flags baked in (-I, -L, -l, -Wl,...), which is not what find_path/
# find_library HINTS expect, and CMake never sources the file itself.
#
# This script sources the file in bash, strips those flags from every
# *_INCDIR / *_LIBDIR / *_LIB / *_ROOTDIR variable it ends up with, and
# prints `export` statements for the clean directories under both the
# FCM-style name (<PKG>_INCDIR) and the underscored CMake-style name
# (<PKG>_INC_DIR), since Find modules in this tree accept either spelling.
#
# Usage (eval the output so the exports reach the caller's shell):
#   eval "$(python3 cmake/import_arch_path.py arch/arch-X64_JEANZAY_Python.path)"
# ---------------------------------------------------------------------------

import re
import shlex
import subprocess
import sys

_VAR_RE = re.compile(r"^([A-Za-z0-9]+)_(INCDIR|LIBDIR|LIB|ROOTDIR)$")


def split_flags(value, collect_bare):
    """Split a flag string into (include_dirs, lib_dirs, bare_tokens).

    Bare tokens are only kept when collect_bare is set, i.e. for
    *_ROOTDIR variables that hold a single plain path (e.g. XIOS_ROOTDIR=
    "$PWD/../XIOS"). For every other role a bare token is a link flag we
    don't recognize (or an already-consumed -l name), and gets dropped.
    """
    tokens = value.split()
    inc, lib, bare = [], [], []
    i = 0
    while i < len(tokens):
        tok = tokens[i]
        if tok == "-I":
            if i + 1 < len(tokens):
                inc.append(tokens[i + 1])
            i += 2
        elif tok.startswith("-I"):
            inc.append(tok[len("-I"):])
            i += 1
        elif tok == "-L":
            if i + 1 < len(tokens):
                lib.append(tokens[i + 1])
            i += 2
        elif tok.startswith("-L"):
            lib.append(tok[len("-L"):])
            i += 1
        elif tok.startswith("-l") or tok == "-Wl" or tok.startswith("-Wl,"):
            i += 1
        else:
            if collect_bare:
                bare.append(tok)
            i += 1
    return inc, lib, bare


def source_and_dump_env(path_file):
    """Source path_file in bash and return its resulting environment.

    Runs in the caller's own CWD and inherited environment (not a copy),
    so $PWD, $ROOT, ${NETCDF_DIR}, etc. resolve exactly as they would if
    FCM's make_xios had sourced the file directly.
    """
    # arch.path files assign plain shell variables, not exported ones, so
    # `env` alone would see nothing. `set -a` auto-exports every assignment
    # the sourced file makes.
    result = subprocess.run(
        ["bash", "-c", 'set -a && source "$1" >/dev/null && env', "_", path_file],
        capture_output=True, text=True,
    )
    if result.returncode != 0:
        sys.exit(f"import_arch_path.py: failed to source {path_file}:\n{result.stderr}")

    env = {}
    for line in result.stdout.splitlines():
        name, sep, value = line.partition("=")
        if sep:
            env[name] = value
    return env


def main():
    if len(sys.argv) != 2:
        sys.exit("usage: import_arch_path.py <arch.path file>")
    path_file = sys.argv[1]

    pkg_inc, pkg_lib, pkg_root = {}, {}, {}
    for name, value in source_and_dump_env(path_file).items():
        match = _VAR_RE.match(name)
        if not match:
            continue
        pkg, role = match.groups()
        inc, lib, bare = split_flags(value, collect_bare=(role == "ROOTDIR"))
        if inc:
            pkg_inc.setdefault(pkg, []).extend(inc)
        if lib:
            pkg_lib.setdefault(pkg, []).extend(lib)
        if bare:
            pkg_root.setdefault(pkg, []).extend(bare)

    def emit(buckets, *names):
        for pkg, paths in buckets.items():
            joined = shlex.quote(":".join(paths))
            for name in names:
                print(f"export {name.format(pkg=pkg)}={joined}")

    emit(pkg_inc, "{pkg}_INCDIR", "{pkg}_INC_DIR")
    emit(pkg_lib, "{pkg}_LIBDIR", "{pkg}_LIB_DIR")
    emit(pkg_root, "{pkg}_ROOT", "{pkg}_DIR")


if __name__ == "__main__":
    main()
