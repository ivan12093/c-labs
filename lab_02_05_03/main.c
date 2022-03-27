#include <stdlib.h>
#include <stdio.h>

#define MIN_ARRAY_SIZE 2
#define MAX_ARRAY_SIZE 10
#define ARRAY_CAPACITY 1024

#define INCORRECT_ARRAY_ELEMENT 1
#define INCORRECT_ARRAY_SIZE 2


int scan_array(int *begin, int *end)
{
    for (int *i = begin; i < end; ++i)
        if (scanf("%d", i) != 1)
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}


int min_neighboor_pair(const int *begin, const int *end)
{
    int min = *begin * *(begin + 1);
    for (const int *i = begin + 1; i < end - 1; ++i)
    {
        int pair_product = *i * *(i + 1);
        if (pair_product < min)
            min = pair_product;
    }
    return min;
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
    if (scan_array(numbers, numbers + array_size))
    {
        printf("Error: Incorrect element of array\n");
        return INCORRECT_ARRAY_ELEMENT;
    }

    int min_pair = min_neighboor_pair(numbers, numbers + array_size);
    printf("Minimal pair: %d\n", min_pair);

    return EXIT_SUCCESS;
}
