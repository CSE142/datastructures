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
	uint64_t seed = 1;
	uint64_t sum = fast_rand(&seed);
	for(long int i = 0; i < 1000000000; i++) {
		for(long int j = 0; j < 10000; j++) }

			if ((i & 2) == 0) {
				sum += sum * j;
			}
		}
	} 
	return sum;
}
