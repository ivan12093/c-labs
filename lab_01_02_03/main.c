#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI acos(-1.0)

int main(void)
{
    // Permissible error rate
    const double eps = 1e-8; 

    double a, b;
    double angle_degrees;
    
    printf("Enter the two sides of the triangle separated by a space:\n");
    if (scanf("%lf%lf", &a, &b) != 2)
        return EXIT_FAILURE;
    
    printf("Enter the angle in degrees between the two sides:\n");
    if (scanf("%lf", &angle_degrees) != 1)
        return EXIT_FAILURE;
    
    if (a < eps || b < eps)
        return EXIT_FAILURE;
    
    double angle_radians = angle_degrees * PI / 180;
    
    double square = a * b / 2 * fabs(sin(angle_radians));
    
    if (square < eps)
        return EXIT_FAILURE;
    
    printf("Square of triangle: %.6lf\n", square);
    return EXIT_SUCCESS;
}

