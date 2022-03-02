#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    double x;
    double eps;
    
    printf("Enter x:\n");
    if (scanf("%lf", &x) != 1)
    {
        return EXIT_FAILURE;
    }
    
    printf("Enter epsilon:\n");
    if (scanf("%lf", &eps) != 1)
    {
        return EXIT_FAILURE;
    }

    if (fabs(x) > 1)
    {
        return EXIT_FAILURE;
    }

    if (fabs(x) < eps)
        return EXIT_FAILURE;
    
    double sum = 0;
    double elem = x;
    int n = 0;
    while (fabs(elem) > eps)
    {
        sum += elem;
        ++n;
        elem = pow(-1, n) * pow(x, 2 * n + 1) / (2 * n + 1);
    }

    double accurate_value = atan(x);
    double absolute_delta = fabs(accurate_value - sum);
    double relative_delta = fabs((accurate_value - sum) / accurate_value);
    
    printf("s(x): %.6lf\n", sum);
    printf("f(x): %.6lf\n", accurate_value);
    printf("Absolute delta: %.6lf\n", absolute_delta);
    printf("Relative_delta: %.6lf\n", relative_delta);

    return EXIT_SUCCESS;
}
