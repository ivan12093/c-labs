#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MIN_ARRAY_SIZE 1
#define MAX_ARRAY_SIZE 10
#define ARRAY_CAPACITY 1024

#define INCORRECT_ARRAY_SIZE 1
#define INCORRECT_ARRAY_ELEMENT 2


int reverse(int a)
{
    int result = 0;
    while (a)
    {
        result = result * 10 + a % 10;
        a /= 10;
    }
    return result;
}


size_t insert_reverse_after_positives(int array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        array[array_size + i] = array[i];

    size_t modified_array_size = 0;
    for (size_t i = array_size; i < 2 * array_size; ++i)
    {
        array[modified_array_size] = array[i];
        ++modified_array_size;
        if (array[i] > 0)
        {
            array[modified_array_size] = reverse(array[i]);
            ++modified_array_size;
        }
    }
    return modified_array_size;
}


bool scan_array(int array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        if (scanf("%d", &array[i]) != 1)
            return true;
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

    array_size = insert_reverse_after_positives(numbers, array_size);
    printf("The modified array:\n");
    print_array(numbers, array_size);

    return EXIT_SUCCESS;
}
