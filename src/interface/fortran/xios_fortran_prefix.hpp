#ifndef __XIOS_SUFFIX__
#define __XIOS_SUFFIX__

/*
 * gfortran -cpp uses a traditional preprocessor mode where '##' is not
 * interpreted as token pasting. Use comment-based concatenation instead so
 * xios(name) expands to xios_name in both cpp and gfortran -cpp modes.
 */
#if defined(__GFORTRAN__)
#define xios(arg) xios_/**/arg
#define txios(arg) xios_/**/arg
#else
#define xios(arg) xios_##arg
#define txios(arg) xios_##arg
#endif

#endif
