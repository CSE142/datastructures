#include <unistd.h>
#include <archlab.h>

int MCMPS() {
	for(volatile long int i = 0; i < 1000000000; i++){
	}

	return 0;
}
