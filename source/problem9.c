#include <stdio.h>

#define uLong unsigned long
#define SUM_ABC 1000


void getAbc(uLong abc[3], uLong nm[2]){
	/* a = n(^2) - m(^2) */
	abc[0] = (nm[0]*nm[0])-(nm[1]*nm[1]);
	/* b = 2nm */
	abc[1] = 2*nm[0]*nm[1];
	/* c = n(^2) + m(^2) */
	abc[2] = (nm[0]*nm[0])+(nm[1]*nm[1]);
}


int main(void){
	uLong nm[] = {1,2}, abc[3], multiplier, product;
	getAbc(abc,nm);

	while ((abc[0] + abc[1] + abc[2]) % SUM_ABC != 0){
		getAbc(abc,nm);
		
		if (nm[0]*(nm[0]+nm[1]) >(double) SUM_ABC/2){
			nm[1]++;
			nm[0] = nm[1] + 1;
		} else {
			nm[0]++;
		}
	}	

	multiplier = (nm[0] * (nm[0] + nm[1])) / (SUM_ABC/2);
	nm[0] *= multiplier;
	nm[1] *= multiplier;

	product = abc[0]*abc[1]*abc[2];

	printf("The product abc, where a, b and c satisfy the "
			"equations a(^2) + b(^2) = c(^2) and "
			"a + b + c = %d, is %ld\n", SUM_ABC, product);
	
	return 0;
}
