#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	uint64_t seed = 1;
	long int sum = 1;
	for(volatile long int i = 0; i < 1000000000; i++){
		fast_rand(&seed);
		if((seed % 2) == 0){
			sum+=sum;
		}
		
	}

	return sum;
}
