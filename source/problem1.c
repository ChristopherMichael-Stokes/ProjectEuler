#include <stdio.h>

int main(void){
	const int M1 = 3;
	const int M2 = 5;
	
	int i=0;
	int sum=0;
	int temp=0;

	while ((M1*++i) < 1000){
		sum+=M1*i;	
	}	
	
	i=0;
	while ((temp = M2*++i) < 1000){
		if (temp%3!=0){
			sum+=temp;	
		}		
	}
	
	printf("sum of three %d\n",sum);


	return 0;
}
