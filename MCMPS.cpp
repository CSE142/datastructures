#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	uint64_t seed = 1;
	uint64_t sum = 1;
	//uint64_t arr[1024];
	//fast_rand(&seed);
	int n = 1000000000;
	int *block = malloc(n * sizeof(int));

	for(int i = 0; i < n/10; i++){
		fast_rand(&seed);
		//seed % n;
		block[seed] = 0;
		
	}

	return sum;
}
