#include <unistd.h>
#include <archlab.h>
#define IND(a, x, y, d) a[(x)*(d)+(y)]
#define IND2(a, x,y) a[(x)*(y)]

int MCMPS() {
	uint64_t seed = 1;
	int x = 20000;
	int y = 50000;
	int z = 10000;
	//register int sum = 0;
	int i, j, k;
       	//int d[x][y], e[x][z], f[y][z];
	int *a, *b, *c;
 	a = (int *)malloc(sizeof(int)*x*y);
	b = (int *)malloc(sizeof(int)*x*z);
	c = (int *)malloc(sizeof(int)*y*z);
	for (i = 0; i < x*z; i++) b[i] = (int) fast_rand(&seed);
	for (i = 0; i < y*z; i++) c[i] = (int) fast_rand(&seed);
	for (i = 0; i < x*y; i++) a[i] = 0;
		for (i = 0; i < x ; i++){
			for (j = 0; j < y; j++){
	//			d[i][j] = e[i][j] + f[j][i];
				for (k = 0; k < z; k++) {
			//	d[i][j] = d[i][j] ^ e[i][k] * f[k][j];
				//IND(a,i,j,y) += IND(b,i,k,z) * IND(c,k,j,z);
				IND2(a,i,j) = IND2(a,i,j) ^ IND2(b,i,k) * IND2(c,k,j);
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
