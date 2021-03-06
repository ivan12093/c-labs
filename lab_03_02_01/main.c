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
#define EMPTY_MATRIX 3


int sum_of_digits(int x)
{
    int sum = 0;
    while (x)
    {
        sum += abs(x % 10);
        x /= 10;
    }
    return sum;
}


void index_min_sum_of_digits(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, size_t *i_row, size_t *i_col)
{
    int min_sum = sum_of_digits(matrix[0][0]);
    size_t row_index = 0;
    size_t column_index = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            int current_sum = sum_of_digits(matrix[i][j]);
            if (current_sum < min_sum)
            {
                row_index = i;
                column_index = j;
                min_sum = current_sum;
            }
        }
    }
    *i_row = row_index;
    *i_col = column_index;
}


void delete_column(int matrix[][ROW_CAPACITY], size_t rows, size_t *columns, size_t index)
{
    for (size_t j = index; j < *columns - 1; ++j)
        for (size_t i = 0; i < rows; ++i)
            matrix[i][j] = matrix[i][j + 1];
    --(*columns);
}


void delete_row(int matrix[][ROW_CAPACITY], size_t *rows, size_t columns, size_t index)
{
    for (size_t i = index; i < *rows - 1; ++i)
        for (size_t j = 0; j < columns; ++j)
            matrix[i][j] = matrix[i + 1][j];
    --(*rows);
}


bool scan_matrix(int matrix[][ROW_CAPACITY], size_t rows, size_t columns)
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

    size_t row_min, col_min;
    index_min_sum_of_digits(matrix, rows, columns, &row_min, &col_min);
    delete_row(matrix, &rows, columns, row_min);
    delete_column(matrix, rows, &columns, col_min);


    if (!rows || !columns)
    {
        printf("Matrix is empty\n");
        return EMPTY_MATRIX;
    }

    printf("Modified matrix:\n");
    print_matrix(matrix, rows, columns);
    return EXIT_SUCCESS;
}
