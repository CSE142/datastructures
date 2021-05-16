#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	std::vector<uint32_t> v;
	uint64_t seed = 1;
	uint64_t sum = 1;
	for(volatile long int i = 0; i < 1000000000; i++){
		fast_rand(&seed);
		if((seed % 2) == 0){
			sum+=sum;
		}
		
	}

	return sum;
}
