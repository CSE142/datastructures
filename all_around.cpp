#include <unistd.h>
#include <archlab.h>

int all_around() {
	uint64_t seed = 1;
	uint64_t sum = 1;
	for(volatile long int i = 0; i < 500000000; i++) {
		fast_rand(&seed);
		if((seed % 2) == 0) {
			sum = sum + ((seed + i) ^ (seed & i) ^ (seed << i));
		}
	}
	return sum;
}
