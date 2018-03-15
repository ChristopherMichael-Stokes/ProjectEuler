#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool is_prime(unsigned long n)
{
	if (n < 2)
		return false;
	for (int i = 2; i < sqrt(n)+1; i++)
		if (n % i == 0)
			return false;
	return true;
}
/*
double round(double a, unsigned int dp)
{
	unsigned long multiplier = (unsigned long)pow(10, dp),
		      b = (unsigned long)a * multiplier;
	if (b % 10 < 5) 
		return floor(b)/multiplier;
	else 
		return ceil(b)/multiplier;	
		
}
*/
int main(void)
{
	const double min = 0.1;
        unsigned long diagonals = 1, primes = 0, i;
	double ratio = 1.0;
	for (i = 3; ratio > min; i+=2) {
		++diagonals;
		for (unsigned long j = (i-2)*(i-2) + (i-2) + 1; j < i*i; j += i - 1){
			++diagonals;
			if (is_prime(j))
				++primes;	
		}
		ratio = primes/(double)diagonals;
	}
	printf("ratio %lf\tside length %ld\n", ratio, i-2);
	
	return 0;
}
