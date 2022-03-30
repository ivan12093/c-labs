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
#define INCORRECT_KEY_NUMBER 3
#define EMPTY_MATRIX 4
#define MATRIX_WAS_NOT_CHANGED 5


bool number_contains_digit(int number, int digit)
{
    while (number)
    {
        if (number % 10 == digit)
            return true;
        number /= 10;
    }
    return false;
}


size_t delete_columns_if_digit_contains(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, int digit)
{
    size_t columns_after = 0;
    for (size_t j = 0; j < columns; ++j)
    {
        bool contains = false;
        for (size_t i = 0; i < rows; ++i)
        {
            if (number_contains_digit(matrix[i][j], digit))
            {
                contains = true;
                break;
            }
        }

        if (!contains)
        {
            for (size_t i = 0; i < rows; ++i)
                matrix[i][columns_after] = matrix[i][j];
            ++columns_after;
        }
    }
    return columns_after;
}

int scan_matrix(int matrix[][ROW_CAPACITY], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            if (scanf("%d", &matrix[i][j]) != 1)
                return EXIT_FAILURE;
    return EXIT_SUCCESS;
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
        printf("Error: incorrect matrix size");
        return INCORRECT_MATRIX_SIZE;
    }

    int matrix[COLUMN_CAPACITY][ROW_CAPACITY];
    printf("Enter elements of matrix:\n");
    if (scan_matrix(matrix, rows, columns))
    {
        printf("Error: incorrect matrix element");
        return INCORRECT_MATRIX_ELEMENT;
    }

    int key_digit;
    printf("Enter key number: ");
    if (scanf("%d", &key_digit) != 1 || key_digit < 0 || key_digit > 9)
    {
        printf("Error: invalid key number");
        return INCORRECT_KEY_NUMBER;
    }

    columns_after = delete_columns_if_digit_contains(matrix, rows, columns, key_digit);

    if (!columns_after)
    {
        printf("Matrix is empty");
        return EMPTY_MATRIX;
    }

    if (columns == columns_after)
    {
        printf("Matrix wasn't changed");
        return MATRIX_WAS_NOT_CHANGED;
    }

    printf("Modified matrix:\n");
    print_matrix(matrix, rows, columns);
    return EXIT_SUCCESS;
}
