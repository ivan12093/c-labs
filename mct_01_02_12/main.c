#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ARRAY_SIZE 1024

#define INCORRECT_ARRAY_SIZE 1
#define INCORRECT_ARRAY_ELEM 2

int scan_array(int array[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
        if (scanf("%d", &array[i]) != 1)
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void print_array(int array[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

bool is_in_sequence(int x)
{
    int elem = 3;
    int n = 0;

    while (abs(elem) < x)
    {
        ++n;
        int mn = n % 2 ? -1 : 1;
        printf("%d", mn);
        int elem = elem - n * n * mn;
    }

    return x == elem;
}

size_t copy_if_in_sequence(int src[], size_t len1, int dst[])
{
    size_t len2 = 0;
    for (size_t i = 0; i < len1; ++i)
    {
        if (is_in_sequence(src[i]))
        {
            dst[i] = src[i];
            ++len2;
        }
    }
    return len2;
}

int main(void)
{
    size_t n;
    printf("Enter size of array: ");
    if (scanf("%zu", &n) != 1 || n > MAX_ARRAY_SIZE)
        return INCORRECT_ARRAY_SIZE;

    int array[MAX_ARRAY_SIZE];
    if (scan_array(array, n))
        return INCORRECT_ARRAY_ELEM;

    int only_in_sequence[MAX_ARRAY_SIZE];
    size_t len2 = copy_if_in_sequence(array, n, only_in_sequence);

    printf("Source\n");
    print_array(array, n);

    printf("Modified\n");
    print_array(only_in_sequence, len2);


    return EXIT_SUCCESS;
}

