#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	
	uint64_t seed = 1;
	register int sum = 1;
	for(volatile long int i = 0; i < 1000000000; i++){
		fast_rand(&seed);
		for (uint64_t int j = seed; j < sizeof(seed); j++){
		//seed % n;
		//if ((seed % 2) == 0) {
			sum += (seed * sum);
		}
		
	}

	return sum;


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

	/*
	//int array[1024][1024];
	uint64_t sum = 0;
	uint64_t seed = 1;
	register long int n = 8*sizeof(sum);
	for (volatile long int x = 0; x < 100000000; x++) {
		for (volatile long int i = 0; i < n ; i++) {
			fast_rand(&seed);
			for (volatile long int j = 0; j < n; j+=x) {
				if((seed % 2) == 1) {
				sum += sum * (seed ^ j);
				}
			}
		}
	}
	return sum;
	*/

}
