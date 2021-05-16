#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	uint64_t seed = 1;
	uint64_t sum = 1;
	uint64_t arr[2048];
	for(long int i = 0; i < 1000000000; i++){
		fast_rand(&seed);
		if((seed % 2) == 0){
			sum += arr[seed];
		}
		
	}

	return sum;
}
