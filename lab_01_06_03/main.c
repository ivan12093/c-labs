#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int position_of_dot(double oblique_product)
{
	if (oblique_product > 0)
	{
		return 0;
	}
	if (oblique_product < 0)
	{
		return 2;
	}
	return 1;
}

int main(void)
{
	double x1, y1;
	double x2, y2;
	double x3, y3;
	
	printf("Enter the coordinates of the first point of "
			"the line separated by a space:\n");
	if (scanf("%lf%lf", &x1, &y1) != 2)
	{
		return EXIT_FAILURE;
	}
	
	printf("Enter the coordinates of the second point of "
			"the line separated by a space:\n");
	if (scanf("%lf%lf", &x2, &y2) != 2)
	{
		return EXIT_FAILURE;
	}

	printf("Enter the coordinates of the third point "
			"separated by a space:\n");
	if (scanf("%lf%lf", &x3, &y3) != 2)
	{
		return EXIT_FAILURE;
	}
	
	double x_vector = fabs(x2 - x1);
	double y_vector = fabs(y2 - y1);
	
	double oblique_product = x_vector * y3 - x3 * y_vector;
	unsigned int position = position_of_dot(oblique_product);
	
	printf("Answer is: %u\n", position);
	return EXIT_SUCCESS;
}

