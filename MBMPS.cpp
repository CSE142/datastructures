#include <unistd.h>
#include <archlab.h>

int MBMPS() {
	for(volatile long int i = 0; i < 1000000000; i++);
	return 0;
}

