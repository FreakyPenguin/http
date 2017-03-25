#ifdef __linux__
#   include <bsd/stdlib.h>
#   include <bsd/string.h>
#   include <bsd/sys/cdefs.h>
#endif

#ifndef __dead
#   define __dead __dead2
#endif

#ifdef __linux__
#   define pledge(x,y) (0)
#endif

#ifdef __linux__
#define basename_c basename_const
#define dirname_c dirname_const
char *dirname_const(const char *p);
char *basename_const(const char *p);
#else
#define basename_c basename
#define dirname_c dirname
#endif
