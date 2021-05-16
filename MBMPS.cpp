#include <unistd.h>
#include <archlab.h>

//volatile int bar = 2;
//volatile uint64_t t =0;

#define IMPL 2
#if (IMPL == 0)
int MBMPS() {
	//uint64_t seed = 1;
	uint_64_t sum = 0;
	//for(volatile long int i = 0; i < 1000000000; i++);
	//return 0;
	
	for(uint64_t i = 0; i < 2000000000; i++){
	}
	return sum;
}//only returns 0;

#elif(IMPL == 1)
//misleading excellence
int MBMPS() {
	//uint64_t seed = 1;
	volatile int sum = 2;
	for(uint64_t i = 0; i < 20000000; i++) {
		if ((i % 2) == 0) {
			sum += sum;
		}
	}
	return sum;
}

#elif (IMPL == 2)
//realistic measurement now
int MBMPS() {
	uint64_t seed = 1;
	uint64_t sum = 1;
	for(volatile long int i = 0; i < 200000000; i++) {
		fast_rand(&seed);
		if((seed % 2) == 1) {
			sum+=(sum*sum+sum/(sum+2));
		}
	}
	return sum;
}

#elif (IMPL == 3)
//cond move
int MBMPS() {
	uint64_t seed = 1;
	uint64_t sum = fast_rand(&seed);
	for(uint64_t i = 0; i < 20000000; i++) {
		if (i % 2 == 0) {
			sum += sum;
		}
	} 
	return sum;
}

#elif (IMPL == 4)
int MBMPS () {
	uint64_t seed = 1;
	uint64_t sum = 1;
	volatile long int i = 20000000;
	while (i != 0) {
		fast_rand(&seed);
		if((seed & 2) == 0) {
			sum += (sum * sum + sum / (sum + 2));
		}
		else if ((seed % 2) == 1) {
			sum += sum;
		}
		else if ((seed % 2) == 0) {
			sum +- sum;
		}
		else {
			sum++;
		}
		i--;
	}
	return sum;
}
#endif

