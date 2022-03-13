#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI acos(-1.0)

int main(void)
{
    double a, b;
    double angle_degrees;
    
    printf("Enter the two sides of the triangle separated by a space:\n");
    scanf("%lf%lf", &a, &b);
    
    printf("Enter the angle in degrees between the two sides:\n");
    scanf("%lf", &angle_degrees);

    double angle_radians = angle_degrees * PI / 180.0;
    
    double square = a * b / 2.0 * fabs(sin(angle_radians));
    
    printf("Square of triangle: %.6lf\n", square);
    return EXIT_SUCCESS;
}

