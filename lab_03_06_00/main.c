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


void fill_matrix_boustrophedon(size_t matrix[][ROW_CAPACITY], size_t rows, size_t columns)
{
    size_t counter = 1;
    for (size_t k = 0; k < columns; ++k)
        for (size_t i = 0; i < rows; ++i, ++counter)
        {
            size_t row_index = k % 2 ? rows - i - 1 : i;
            matrix[row_index][k] = counter;
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
        rows < MIN_ROWS || columns > MAX_COLUMNS || columns < MIN_COLUMNS)
    {
        printf("Error: incorrect matrix size\n");
        return INCORRECT_MATRIX_SIZE;
    }

    size_t matrix[COLUMN_CAPACITY][ROW_CAPACITY];
    fill_matrix_boustrophedon(matrix, rows, columns);

    printf("Modified matrix:\n");
    print_matrix(matrix, rows, columns);
    return EXIT_SUCCESS;
}
