#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#define N 2000000 

int isPrime(uint32_t x){
	uint32_t i;
	if (x < 2) return 0;
	else if (x == 2) return 1;

	for (i = 2; i < sqrt(x)+1; i++){
	       if (x % i == 0) return 0;
	}
	
	return 1;
}

int main(void){
	uint64_t sum = 0, i;
	for (i = 0; i<=N; i++){
		if (isPrime(i)) sum += i;
	}

	printf("Sum of all primes lower than %d is %"PRIu64"\n",N,sum);
	return 0;
}

