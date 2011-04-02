// PRNG f function provided by Dr. Jack Tan

#ifndef __F_CPP__
#define	__F_CPP__


static long f(long nonce) {
    const long A = 48271;
    const long M = 2147483647;
    const long Q = M/A;
    const long R = M%A;

	static long state = 1;
	long t = A * (state % Q) - R * (state / Q);

	if (t > 0)
		state = t;
	else
		state = t + M;
	return (long)(((double) state/M)* nonce);
}



#endif /* __F_CPP__ */






