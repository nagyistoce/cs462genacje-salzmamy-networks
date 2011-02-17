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


/*
 * To use the above:
 */


typedef unsigned char byte;

byte* to_little_endian(byte* bytes)
{
#ifdef __BO_BIG_ENDIAN
	swapByteOrder(bytes);
#endif

	return bytes;
}
/*
int endian() {
	// Create a number large enough to screw up byte ordering across big/little endian platforms
	uint32_t num = 123456789;
	
	// Create a place to store a 32 bit integer
	byte bytes[4];
	
	// Copy the byte value of num into bytes (the bytes will be in a different order on big/little endian machines)
	memcpy(&dest[0], &num, sizeof(uint32_t));
	
	// Force little-endian before sending over the network
	to_little_endian(bytes);
	
	return 0;
}*/
