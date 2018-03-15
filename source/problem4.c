#include <stdio.h>
#include <math.h>

#define MAX_FACTORS 999
#define NUM_FACTORS 2
#define DIGITS 3

int isValid(long input){
	int i, j, lowerBound = pow(10,DIGITS-1);

	for (i=pow(10,DIGITS-1); i < MAX_FACTORS; i++){
		if (input % i == 0){
			j = input / i;
			if (i > lowerBound && j > lowerBound &&
					i < MAX_FACTORS && 
					j < MAX_FACTORS){
				return 1;
			}	
		}
	}

	return 0;
}

int isPalindrome(long input){ 
	int numDigits = floor(log10(input)+1), 
	    modifiedInput = input, i,
	    digits[numDigits], high, low;

	for (i = numDigits-1; i >= 0; i--){
		digits[i] = modifiedInput % 10;	
		modifiedInput /= 10;
	}

	high = numDigits-1; 
	low = 0;

	while (high >= low){
		if (digits[high] != digits[low]){
			return 0;
		}			
		high--;
		low++;
	}

	return 1;
}


int main(void){
	long ceiling = pow(MAX_FACTORS, NUM_FACTORS);
	while (ceiling > pow(pow(10,DIGITS-1)-1,NUM_FACTORS)){
		if (isPalindrome(ceiling)){
			if (isValid(ceiling)) break;
		}
		ceiling--;
	}

	printf("largest palindrome that is a product of %d, %d digt integers is: %ld\n",
		       NUM_FACTORS, MAX_FACTORS, ceiling);	

	return 0;
}
