#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INCORRECT_X 1
#define INCORRECT_EPS 2

#define MIN_ABS_X 1e-6

double series(double x, double eps)
{
    double elem = x / 2.0; 
    double series_value = elem; 
    for (int i = 1; fabs(elem) > eps * eps; ++i)
    {
        elem *= -1.0 * x * x * x * (i + 2) / (i + 1) / (i + 3);
        printf("%lf", elem);
        series_value += elem;
    }
    return series_value;
}

int main(void)
{
    double x;
    printf("Enter x: ");
    if (scanf("%lf", &x) != 1 || fabs(x) < MIN_ABS_X)
        return INCORRECT_X;

    double eps;
    printf("Enter eps: ");
    if (scanf("%lf", &eps) != 1 || eps <= 0)
        return INCORRECT_EPS;

    double func_value = -1.0 / (x * x * x * x * x) * exp(-1.0 * x * x * x) * (1 + x) * (1 - x + x * x);
    double series_value = series(x, eps);

    printf("Function value: %e\n", func_value);
    printf("Series value: %g\n", series_value);
    return EXIT_SUCCESS;
}

