/*
 * Detect Endianness
 */


/* Define LITTLE_ENDIAN if the system hasn't done so already */
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif

/* Define BIG_ENDIAN if the system hasn't done so already */
#ifndef BIG_ENDIAN
#define BIG_ENDIAN 4321
#endif

/* If the system doesn't already tell us its byte order, try to guess it */
#ifndef BYTE_ORDER

/* Solaris/SunOS (Shiva) */
#if defined (__SVR4) && defined (__sun)
#define BYTE_ORDER BIG_ENDIAN

/* All others (Andy/Clark) */
#else
#define BYTE_ORDER LITTLE_ENDIAN
#endif

#endif

/* Define some quick tests for endianness */
#if BYTE_ORDER == BIG_ENDIAN
#define __BO_BIG_ENDIAN
#else
#define __BO_LITTLE_ENDIAN
#endif



