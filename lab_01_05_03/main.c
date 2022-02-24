#include <stdio.h>
#include <stdlib.h>

unsigned int gcd(unsigned int a, unsigned int b)
{
	while (a && b)
	{
		if (a > b)
		{
			a %= b;
		}
		else
		{
			b %= a;
		}
	}

	return a ? a : b;
}

int main(void)
{
	unsigned int a, b;
	
	printf("Enter two natural numbers separated by a space:\n");
	if (scanf("%u%u", &a, &b) != 2)
	{
		return EXIT_FAILURE;
	}

	unsigned int answer = gcd(a, b);

	printf("GCD is: %u\n", answer);
	return EXIT_SUCCESS;
	
}

