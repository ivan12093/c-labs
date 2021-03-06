#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MIN_ARRAY_SIZE 1
#define MAX_ARRAY_SIZE 10
#define ARRAY_CAPACITY 1024

#define INCORRECT_ARRAY_SIZE 1
#define INCORRECT_ARRAY_ELEMENT 2
#define NO_POSITIVE_ELEMENTS 3


double geometric_mean_of_positives(int array[], size_t array_size)
{
    int count_positives = 0;
    double product = 1.0;
    
    for (size_t i = 0; i < array_size; ++i)
        if (array[i] > 0)
        {
            product *= array[i];
            ++count_positives;
        }
    if (count_positives)
        return pow(product, 1.0 / count_positives);

    return -1.0;
}


bool scan_array(int array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        if (scanf("%d", &array[i]) != 1)
            return true;
    return false;
}


int main(void)
{
    size_t array_size;

    printf("Enter size of array: ");
    if (scanf("%zu", &array_size) != 1 || array_size < MIN_ARRAY_SIZE || array_size > MAX_ARRAY_SIZE)
    {
        printf("Error: Incorrect size of array\n");
        return INCORRECT_ARRAY_SIZE;
    }

    int numbers[ARRAY_CAPACITY];
    printf("Enter elements of the array: \n");
    if (scan_array(numbers, array_size))
    {
        printf("Error: Incorrect element of array\n");
        return INCORRECT_ARRAY_ELEMENT;
    }

    double geom_mean = geometric_mean_of_positives(numbers, array_size);
    if (geom_mean < 0)
    {
        printf("Error: No positive elements in the array\n");
        return NO_POSITIVE_ELEMENTS;
    }

    printf("Geometric mean of positive elements: %.6lf\n", geom_mean);

    return EXIT_SUCCESS;
}
