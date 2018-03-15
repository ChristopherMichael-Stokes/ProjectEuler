#include <stdio.h>

int main(void)
{
	unsigned long sum = 1;	
	for (unsigned int i = 3; i <= 1001; i += 2) {
		for (unsigned long j = (i-2)*(i-2) + (i-2) + 1; j <= i*i; j += i - 1) {
			sum += j;	
		}	
	}
	printf("sum %ld\n",sum);
	return 0;
}
