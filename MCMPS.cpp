#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	uint64_t seed = 1;
	uint64_t sum = 1;
	//uint64_t arr[1024];
	//fast_rand(&seed);
	long int n = 1000000000;
	long int *block = malloc(n * sizeof(int));

	for(long int i = 0; i < n/10; i++){
		fast_rand(&seed);
		seed % n;
		block[seed] = 0;
		
	}

	return 0;
}
