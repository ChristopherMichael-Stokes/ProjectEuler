#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#define PRIME_INDEX 10001

int isPrime(uint32_t x){
	uint32_t i;
	
	if (x < 2) return 0;
	else if (x == 2) return 1;

	for (i=2; i<sqrt(x)+1; i++){
		if (x%i==0){
			return 0;
		}
	}
	return 1;
}

int main(void){
	uint32_t count = 0, prime, i;

	for (i=0; i<UINT32_MAX; i++){
		if (isPrime(i)){
			count++;
			if (count==PRIME_INDEX){
				prime = i;
				break;
			}
		}
	}

	printf("The prime at index %d is %"PRIu32"\n",PRIME_INDEX,prime);

	return 0;
}
