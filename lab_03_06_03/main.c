#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define COLUMN_CAPACITY 256
#define ROW_CAPACITY 256

#define MAX_ROWS 10
#define MIN_ROWS 1
#define MAX_COLUMNS 10
#define MIN_COLUMNS 1

#define INCORRECT_MATRIX_SIZE 1


void fill_matrix_counterclockwise(size_t matrix[][ROW_CAPACITY], size_t rows, size_t columns)
{
    size_t counter = 1;
    for (size_t i = 0; counter <= rows * columns; ++i)
    {
        // Filling left border
        for (size_t k = i; k < rows - i && counter <= rows * columns; ++k, ++counter)
            matrix[k][i] = counter;
        
        // Filling lower border
        for (size_t k = i + 1; k < columns - i && counter <= rows * columns; ++k, ++counter)
            matrix[rows - i - 1][k] = counter;
        
        // Filling right border
        for (size_t k = i + 1; k < rows - i && counter <= rows * columns; ++k, ++counter)
            matrix[rows - k - 1][columns - i - 1] = counter;
        
        // Filling upper border
        for (size_t k = i + 1; k < columns - i - 1 && counter <= rows * columns; ++k, ++counter)
            matrix[i][columns - k - 1] = counter;
    }
}


void print_array(const size_t array[], size_t array_size)
{
    for (size_t i = 0; i < array_size; ++i)
        printf("%zu ", array[i]);
    printf("\n");
}


void print_matrix(size_t matrix[][ROW_CAPACITY], size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; ++i)
        print_array(matrix[i], columns);
}


int main(void)
{
    size_t rows, columns;

    printf("Enter the number of rows and columns in the matrix:\n");
    if (scanf("%zu%zu", &rows, &columns) != 2 || rows > MAX_ROWS || 
        rows < MIN_ROWS || columns > MAX_COLUMNS || columns < MIN_COLUMNS || rows != columns)
    {
        printf("Error: incorrect matrix size\n");
        return INCORRECT_MATRIX_SIZE;
    }

    size_t matrix[COLUMN_CAPACITY][ROW_CAPACITY];
    fill_matrix_counterclockwise(matrix, rows, columns);

    printf("Modified matrix:\n");
    print_matrix(matrix, rows, columns);
    return EXIT_SUCCESS;
}
