#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI acos(-1)

int main(void)
{
	// Permissible error rate
	const double EPS = 1e-6; 

	double a, b;
	double angle_degrees;
	
	printf("Enter the two sides of the triangle separated by a space:\n");
	if (scanf("%lf%lf", &a, &b) != 2)
	{
		return EXIT_FAILURE;
	}
	
	printf("Enter the angle in degrees between the two sides:\n");
	if (scanf("%lf", &angle_degrees) != 1)
	{
		return EXIT_FAILURE;
	}
	
	if (a < EPS || b < EPS)
	{
		return EXIT_FAILURE;
	}
	
	double angle_radians = angle_degrees * PI / 180;
	
	double square = a * b * fabs(acos(angle_radians));
	
	if (square < EPS)
	{
		return EXIT_FAILURE;
	}
	
	printf("Square of triangle: %lf\n", square);
	return EXIT_SUCCESS;
}

