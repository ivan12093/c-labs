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


void symmetric_row_swap(int matrix[][ROW_CAPACITY], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows / 2; ++i)
        for (size_t j = i; j < columns - i; ++j)
        {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[rows - i - 1][j];
            matrix[rows - i - 1][j] = tmp;
        }
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
    
    symmetric_row_swap(matrix, rows, columns);

    printf("Modified matrix:\n");
    print_matrix(matrix, rows, columns);
    return EXIT_SUCCESS;
}
