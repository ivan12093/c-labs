#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 20

#define INCORRECT_ARRAY_SIZE 1
#define INCORRECT_ARRAY_ELEMENT 2


int reverse_int(int a)
{
    int result = 0;
    while (a)
    {
        result = result * 10 + a % 10;
        a /= 10;
    }
    return result;
}


int insert_in_array(int array[], int elem, size_t index, size_t len)
{
    for (size_t i = len; i > index; --i)
        array[i] = array[i - 1];
    array[index] = elem;
    return EXIT_SUCCESS;
}


int scan_array(int array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        if (scanf("%d", &array[i]) != 1)
            return INCORRECT_ARRAY_ELEMENT;
    return EXIT_SUCCESS;
}


int print_array(const int array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        printf("%d ", array[i]);
    printf("\n");
    return EXIT_SUCCESS;
}


int main(void)
{
    size_t array_size;

    printf("Enter size of array: ");
    if (scanf("%zu", &array_size) != 1 || array_size < 1 || array_size > 10)
    {
        printf("Error: Incorrect size of array\n");
        return INCORRECT_ARRAY_SIZE;
    }

    int numbers[ARRAY_SIZE];
    printf("Enter elements of the array: \n");
    if (scan_array(numbers, array_size))
    {
        printf("Error: Incorrect element of array\n");
        return INCORRECT_ARRAY_ELEMENT;
    }

    for (size_t i = 0; i < array_size; ++i)
        if (numbers[i] > 0)
        {
            int reverse = reverse_int(numbers[i]);
            insert_in_array(numbers, reverse, i + 1, array_size);
            ++array_size;
            ++i;
        }

    printf("The modified array:\n");
    print_array(numbers, array_size);

    return EXIT_SUCCESS;
}
