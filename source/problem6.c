#include <stdio.h>

#define N 100
#define uLong unsigned long

uLong sumOfSquare(void){
	return (N*(N+1)*(2*N+1))/6;
}

uLong sum(void){
	return (N/2)*(N+1);
}

int main(void){
	uLong squareOfSum = sum()*sum(),
	     difference = squareOfSum-sumOfSquare();

	printf("The difference between the sum of square and "
			"the square of sum of the first %d natural "
			"numbers is %ld\n",N,difference);
	return 0;
}
