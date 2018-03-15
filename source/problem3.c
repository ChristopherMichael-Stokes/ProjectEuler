#include <stdio.h> 
#include <math.h>
/* when compiling use -lm flag to link the maths library */
#include <stdbool.h>

#define uLong const unsigned long

bool isPrime(uLong input){
	int i;
	for(i=2; i<(int)(sqrt(input))+1; i++){
		if (input%i==0) return false;
	}
	return true;
}

int factorise(uLong input){
	int i;

	for(i=(int)(sqrt(input))+1; i>1; i--){
		if(input%i==0 && isPrime(i)){
			return i;
		}
	}

	return -1;
}

int main(void){
	uLong divisor = 600851475143;
	printf("largest prime factor of %ld:\t%d\n",divisor,factorise(divisor));
	return 0;
}
