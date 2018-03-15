#include <stdio.h>
#include <inttypes.h>

#define N 1000000

int collatz(uint32_t n){
	int sum = 1;

	while (n > 1){
		if (n % 2 == 0){
			n /= 2;
			sum++;
		} else {
			n = (3*n + 1)/2;
			sum += 2;
		}
	}

	return sum;
}
	
int main(void){
	uint32_t n = 1, maxChainLen = collatz(n), maxN = n;
	int tempChainLen;

	for (; n < N; n++){
		tempChainLen = collatz(n);
		if (tempChainLen > maxChainLen) {
			maxChainLen = tempChainLen;
			maxN = n;
		}
	}
	
	printf("The longest chain from all numbers less than %d is %"PRIu32"\n", N, maxN);
		
	return 0;	
}

