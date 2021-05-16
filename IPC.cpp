#include <unistd.h>
#include <archlab.h>


int IPC() {
	uint64_t seed = 1; // you must initialize the seed to a non-zero
			// value or fast_rand will just return 0
			// forever.
	/*
	for(int i= 0; i < 1; i++) {
		// You should _definitely not_ print anything out in
		// your actual code.  This is just to demonstrate that
		// fast_rand() is working.
		std::cout << fast_rand(&s) << "\n";
	}
*/
	register volatile int sum = 1;
	for(volatile long int i = 0; i < 1000000000; i++) {
		fast_rand(&seed);
		sum = sum + ((seed + i) ^ (seed & i) ^ (seed << i) ^ (seed * sum) * (sum ^ seed));	
  	}
	return sum;
}
