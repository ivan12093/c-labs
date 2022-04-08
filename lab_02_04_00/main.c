#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MIN_ARRAY_SIZE 1
#define MAX_ARRAY_SIZE 10
#define ARRAY_CAPACITY 1024

#define EMPTY_ARRAY 1
#define ARRAY_OVERFLOW 100


void bubble_sort(int array[], size_t array_size)
{
    for (size_t i = array_size; i > 0; --i)
        for (size_t j = 0; j < i - 1; ++j)
            if (array[j + 1] < array[j])
            {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
}


bool scan_array(int array[], size_t *array_size)
{
    int input;
    size_t i = 0;
    while (scanf("%d", &input) == 1)
    {
        if (i == *array_size)
            return true;
        
        array[i] = input;
        ++i;
    }

    *array_size = i;
    return false;
}


void print_array(const int array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}


int main(void)
{
    int return_code = EXIT_SUCCESS;
    size_t array_size = MAX_ARRAY_SIZE;
    int numbers[ARRAY_CAPACITY];

    printf("Enter elements of the array: \n");
    if (scan_array(numbers, &array_size))
        return_code = ARRAY_OVERFLOW;

    if (array_size < MIN_ARRAY_SIZE)
        return EMPTY_ARRAY;

    bubble_sort(numbers, array_size);
    printf("Sorted array:\n");
    print_array(numbers, array_size);

    return return_code;
}
