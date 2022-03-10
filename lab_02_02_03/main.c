#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 10

#define INCORRECT_ARRAY_SIZE 1
#define INCORRECT_ARRAY_ELEMENT 2
#define NO_NARCISSISTIC_NUMBERS 3


int pow_int(int basis, int exponent)
{
    int result = 1;

    while (exponent)
    {
        if (exponent % 2)
            result *= basis;

        basis *= basis;
        exponent /= 2;
    }

    return result;
}


bool is_narcissistic(int a)
{
    if (a < 0)
        return false;

    int length = 0;
    int a_copy = a;
    while (a_copy)
    {
        a_copy /= 10;
        ++length;
    }

    int check_sum = 0;
    a_copy = a;
    for (int i = 0; i < length; ++i)
    {
        check_sum += pow_int(a_copy % 10, length);
        a_copy /= 10;

    }

    return check_sum == a;
}


int scan_array(int array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
    {
        if (scanf("%d", &array[i]) != 1)
            return INCORRECT_ARRAY_ELEMENT;
    }
    return EXIT_SUCCESS;
}


int print_array(int array[], size_t array_size)
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

    int narcissistic_numbers[ARRAY_SIZE];
    size_t len_narciss = 0;
    for (size_t i = 0; i < array_size; ++i)
    {
        if (is_narcissistic(numbers[i]))
        {
            narcissistic_numbers[len_narciss] = numbers[i];
            ++len_narciss;
        }
    }

    if (!len_narciss)
    {
        printf("Error: No narcissistic numbers in array\n");
        return NO_NARCISSISTIC_NUMBERS;
    }

    printf("Array of narcissistic numbers:\n");
    print_array(narcissistic_numbers, len_narciss);

    return EXIT_SUCCESS;
}
