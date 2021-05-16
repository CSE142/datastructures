#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	std::vector<uint32_t> v;
	//uint64_t seed = 1;
	uint64_t sum = 1;
	uint32_t *restrict velt = &v[0];
	uint32_t *restrict vend = velt + v.size();
	
	while(velt < vend) {
		sum += *velt;
		velt++;
	}

	/*
	for(volatile long int i = 0; i < 1000000000; i++){
		fast_rand(&seed);
		if((seed % 2) == 0){
			sum+=sum;
		}
		
	}

	return sum;
	*/
}
