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
	//uint64_t array[1024];
	uint64_t sum = 0;
	uint64_t seed = 1;
	for (long int i = 0; i < 1000000000; i++) {
		fast_rand(&seed);
		for (long int j = 0; j < seed; j++) {
			int r1 = j + (seed % 1024);
			int r2 = j + (seed);

			
			sum += r1*r1 + r2*r2;
		}
	}
	return sum;

}
