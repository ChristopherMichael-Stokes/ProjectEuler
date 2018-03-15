#include <stdio.h>
#include <math.h>

#define MAX 20

int valid(long x){
	int i;
	for (i=2; i<=MAX; i++){
		if (x % i != 0){
			return 0;
		}
	}
	return 1;
}

int main(void){
	long result = MAX;

	while (!valid(result)){
		result += 20;
	}

	printf("the lcd of all natural numbers lower than %d is %ld\n",
			MAX, result);
	return 0;
}
