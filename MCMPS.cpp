#include <unistd.h>
#include <archlab.h>
#define IND(A, x, y, d) A[(x)*(d)+(y)]

int MCMPS() {

/*
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
*/
/*THIS has right runtime but not right values	
	uint64_t seed = 1;
	register int sum = 1;
	for(volatile long int i = 0; i < 1000000000; i++){
		fast_rand(&seed);
		int arr[seed][seed];
		for (uint64_t j = seed; j < sizeof(seed); j++){
			for(uint64_t k = seed; k < sizeof (seed); k++){
				sum = sum * arr[j][k] * arr[k][j]; 
			}
		}
	}
	return sum;
*/	
	uint64_t seed = 1;
	
	int x = 20000;
	int y = 50000;
	int z = 10000;
	//register int sum = 0;
	int i, j, k;
       	//int a[x][y], b[x][z], c[y][z];
	int *a, *b, *c;
 	a = (int *)malloc(sizeof(int)*x*y);
	b = (int *)malloc(sizeof(int)*x*z);
	c = (int *)malloc(sizeof(int)*y*z);
	for (i = 0; i < x*z; i++) b[i] = (int) fast_rand(&seed);
	for (i = 0; i < y*z; i++) c[i] = (int) fast_rand(&seed);
	for (i = 0; i < x*y; i++) a[i] = 0;
	//int n = 1024;
		for (i = 0; i < n ; i++){
			for (j = 0; j < n; j++){
				//a[i][j] = a[i][j] + b[j][i];
				for (k = 0; k < n; k++) {
				c[i][j] = c[i][j] ^ a[i][k] * b[k][j];

			}
		}
	}
	return 0;



	/*
	uint64_t seed = 1;
	uint64_t sum = 1;
	for(uint64_t i = 0; i < 1000000000; i++) {
		fast_rand(&seed);
		if ((seed & 2) == 0) {
			sum += (seed + i);
		}
	} 
	return sum;
	*/

	/*
	//int array[1024][1024];
	uint64_t sum = 0;
	uint64_t seed = 1;
	register long int n = 8*sizeof(sum);
	for (volatile long int x = 0; x < 100000000; x++) {
		for (volatile long int i = 0; i < n ; i++) {
			fast_rand(&seed);
			for (volatile long int j = 0; j < n; j+=x) {
				if((seed % 2) == 1) {
				sum += sum * (seed ^ j);
				}
			}
		}
	}
	return sum;
	*/
}
