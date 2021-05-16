#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	/*
	uint64_t seed = 1;
	uint64_t sum = 1;
	for(int i = 0; i < 1000000000; i++){
		fast_rand(&seed);
		//seed % n;
		if ((seed % 2) == 0) {
			sum += (seed * sum);
		}
		
	}

	return sum;
	*/

	/*
	uint64_t seed = 1;
	uint64_t sum = 1;
	for(uint64_t i = 0; i < 1000000000; i++) {
		fast_rand(&seed);
		if ((seed & 2) == 0) {
			sum += (seed + i);
		}
	} 
	return sum;
	*/
	int array[1024];
	uint64_t sum = 0;
	uint64_t seed = 1
	for (volatile long int i = 0; i < 1000000000; i++) {
		fast_rand(&seed);
		sum += array[seed % 1024];
	}
	return sum;

}
