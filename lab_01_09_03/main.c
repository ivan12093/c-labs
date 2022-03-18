#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double x;
    double power = 1;

    printf("Enter a sequence of positive numbers. "
        "To stop typing, enter a negative number.\n");
    if (scanf("%lf", &x) != 1 || x < 0.0)
        return EXIT_FAILURE;

    for (int i = 1; x >= 0.0; ++i)
    {
        power *= 1.0 / (x + i);
        if (scanf("%lf", &x) != 1)
            return EXIT_FAILURE;
    }
    
    double result = exp(power);
    printf("Result: %.6lf\n", result);  

    return EXIT_SUCCESS;
}
