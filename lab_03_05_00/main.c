#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COLUMN_CAPACITY 256
#define ROW_CAPACITY 256

#define MAX_ROWS 10
#define MIN_ROWS 1
#define MAX_COLUMNS 10
#define MIN_COLUMNS 1

#define INCORRECT_MATRIX_SIZE 1
#define INCORRECT_MATRIX_ELEMENT 2
#define NO_PRIME_NUMBERS 3


void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


bool is_prime(int x)
{
    if (x < 2 || (x != 2 && x % 2 == 0))
        return false;

    for (int i = 3; i * i <= x; i += 2)
        if (x % i == 0)
            return false;
    return true;
}


size_t copy_if(const int src[], size_t len_src, int dst[], bool (*predicate)(int))
{
    size_t len_dst = 0;
    for (size_t i = 0; i < len_src; ++i)
        if (predicate(src[i]))
        {
            dst[len_dst] = src[i];
            ++len_dst;
        }
    return len_dst;
}


void reverse_array(int array[], size_t len)
{
    for (size_t i = 0; i < len / 2; ++i)
        swap(&array[i], &array[len - i - 1]);
}


size_t copy_primes(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, int array[])
{
    size_t len_array = 0;
    for (size_t i = 0; i < rows; ++i)
        len_array += copy_if(matrix[i], columns, array + len_array, is_prime);
    return len_array;
}


void overwrite_primes(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, int primes[])
{
    size_t prime_index = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            if (is_prime(matrix[i][j]))
            {
                matrix[i][j] = primes[prime_index];
                ++prime_index;
            }
}


int scan_matrix(int matrix[][ROW_CAPACITY], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            if (scanf("%d", &matrix[i][j]) != 1)
                return true;
    return false;
}


void print_array(const int array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}


void print_matrix(int matrix[][ROW_CAPACITY], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i)
        print_array(matrix[i], columns);
}


int main(void)
{
    size_t rows, columns;

    printf("Enter the number of rows and columns in the matrix:\n");
    if (scanf("%zu%zu", &rows, &columns) != 2 || rows > MAX_ROWS || 
        rows < MIN_ROWS || columns > MAX_COLUMNS || columns < MIN_COLUMNS)
    {
        printf("Error: incorrect matrix size\n");
        return INCORRECT_MATRIX_SIZE;
    }

    int matrix[COLUMN_CAPACITY][ROW_CAPACITY];
    printf("Enter elements of matrix:\n");
    if (scan_matrix(matrix, rows, columns))
    {
        printf("Error: incorrect matrix element\n");
        return INCORRECT_MATRIX_ELEMENT;
    }
    
    int primes[ROW_CAPACITY * COLUMN_CAPACITY];
    size_t count_primes = copy_primes(matrix, rows, columns, primes);
    if (!count_primes)
    {
        printf("Error: no prime numbers\n");
        return NO_PRIME_NUMBERS;
    }
    reverse_array(primes, count_primes);
    overwrite_primes(matrix, rows, columns, primes);

    printf("Modified matrix:\n");
    print_matrix(matrix, rows, columns);
    return EXIT_SUCCESS;
}
