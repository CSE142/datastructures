#include <unistd.h>
#include <archlab.h>
#define IND(A, x, y, d) A[(x)*(d)+(y)]

int all_around() {
	/*
	uint64_t seed = 1;
	uint64_t sum = 1;
	for(volatile long int i = 0; i < 500000000; i++) {
		fast_rand(&seed);
		if((seed % 2) == 0) {
			sum = sum + ((seed + i) ^ (seed & i) ^ (seed << i));
		}
	}
	return sum;
	*/	
	
	double *A; double *B; double *C;
	int i,j,k;
	uint64_t seed = 1;
	register int x;
	register int y;
	register int z;
	x = 20000;
	y = 50000;
	z = 10000;
	A = (double *)malloc(sizeof(double)*x*y);
	B = (double *)malloc(sizeof(double)*x*z);
	C = (double *)malloc(sizeof(double)*y*z);

	for (i=0; i < x*z; i++) B[i] = (double) fast_rand(&seed);
	for (i=0; i < y*z; i++) C[i] = (double) fast_rand(&seed);
	for (i=0; i < x*y; i++) A[i] = 0;

	for (i = 0; i < x; i++){
		for(j=0; j < y; j++){
			for(k=0; k<z; k++){
				//A[i][j] += B[i][k] + C[k][j];
				IND(A,i,j,y) += IND(B,i,k,z) * IND(C,k,j,z);
			}
		}
	}
	return 0;
}
