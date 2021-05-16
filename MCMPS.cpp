#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	uint64_t seed = 1;
	uint64_t sum = 1;
	//uint64_t arr[1024];
	//fast_rand(&seed);
	//int n = 1000000000;
	//int block[n];

	for(int i = 0; i < 1000000000; i++){
		fast_rand(&seed);
		//seed % n;
		if ((seed % 2) == 0) {
			sum += (seed * sum);
		}
		
	}

	return sum;
}
