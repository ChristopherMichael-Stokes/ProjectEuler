#include <stdio.h>

#define MAX 4000000

/* use a loop to generate fibonacci terms */
int fibLoop(void){
	int sum=0, prev=1, next=1, temp, i;
	temp = prev+next;

	for(i=0; temp<MAX; i++){
		temp = prev+next;
		prev = next;
		next = temp;
		if (temp%2==0) sum += temp;
	}

	return sum;
}

int main(void){
	printf("sum of even fib: %d",fibLoop());
	return 0;	
}
