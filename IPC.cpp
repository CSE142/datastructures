#include <unistd.h>
#include <archlab.h>


int IPC() {
	uint64_t seed = 1; 
	register volatile int sum = 1;
	for(volatile long int i = 0; i < 1000000000; i++) {
		fast_rand(&seed);
		sum = sum + ((seed + i) ^ (seed & i) ^ (seed << i) ^ (seed + sum));	
  	}
	return sum;
}
