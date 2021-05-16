#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	uint64_t seed = 1;
	uint64_t sum = 1;
	uint64_t arr[1024];
	fast_rand(&seed);
	for(long int i = seed; i < 1000000000; i++){
		sum += arr[i];
		
	}

	return sum;
}
