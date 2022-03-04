#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int position_of_dot(double x1, double y1, double x2,
                    double y2, double x3, double y3)
{
    double x_vec_line = x2 - x1;
    double y_vec_line = y2 - y1;
    double x_vec_dot = x3 - x1;
    double y_vec_dot = y3 - y1;

    double oblique_product = x_vec_line * y_vec_dot - x_vec_dot * y_vec_line;

    if (y2 < y1)
        oblique_product = y_vec_line * x_vec_dot - y_vec_dot * x_vec_line;

    if ((x1 > x2 && y1 < y2) || (x2 > x1 && y2 < y1))
        oblique_product *= -1.0;

    if (oblique_product > 0)
        return 0;

    if (oblique_product < 0)
        return 2;

    return 1;
}

int main(void)
{
    double x1, y1;
    double x2, y2;
    double x3, y3;

    const double eps = 1e-8;

    printf("Enter the coordinates of the first point of "
        "the line separated by a space:\n");
    if (scanf("%lf%lf", &x1, &y1) != 2)
        return EXIT_FAILURE;

    printf("Enter the coordinates of the second point of "
        "the line separated by a space:\n");
    if (scanf("%lf%lf", &x2, &y2) != 2)
        return EXIT_FAILURE;

    printf("Enter the coordinates of the third point "
        "separated by a space:\n");
    if (scanf("%lf%lf", &x3, &y3) != 2)
        return EXIT_FAILURE;
    
    if (fabs(x2 - x1) < eps && fabs(y2 - y1) < eps)
        return EXIT_FAILURE;

    int position = position_of_dot(x1, y1, x2, y2, x3, y3);
    printf("Answer is: %d\n", position);
    return EXIT_SUCCESS;
}

