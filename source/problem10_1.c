#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define N 2000000 

void eSieve(bool* a){
	uint32_t i, j;

	memset(a, true, sizeof(bool)*N);

	a[0] = false;
	a[1] = false;

	for (i = 2; i < sqrt(N)+1; i++){
		if (a[i] == true){
			for (j = (i*i); j < N; j += i){
				a[j] = false;
			}
		}
	}		
}

int main(void){
	bool* a = malloc(sizeof(bool)*N);
	uint32_t i;
	uint64_t sum = 0;
	
	eSieve(a);
	for (i = 2; i<N; i++){
		if (a[i] == true) sum += i;
	}
	
	printf("The sum of all primes less than %d is %"PRIu64"\n",N,sum);
	free(a);
		
	return 0;	
}
