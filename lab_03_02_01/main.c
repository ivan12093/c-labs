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


int product_of_digit(int x)
{
    int product = 1;
    while (x)
    {
        product *= abs(x % 10);
        x /= 10;
    }
    return product;
}


void index_min_by_product_of_digit(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, size_t *i_row, size_t *i_col)
{
    int min_product = product_of_digit(matrix[0][0]);
    size_t row_index = 0;
    size_t column_index = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            int current_product = product_of_digit(matrix[i][j]);
            if (current_product < min_product)
            {
                row_index = i;
                column_index = j;
                min_product = current_product;
            }
        }
    }
    *i_row = row_index;
    *i_col = column_index;
}


void delete_column(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, size_t to_del)
{
    for (size_t j = to_del; j < columns - 1; ++j)
        for (size_t i = 0; i < rows; ++i)
            matrix[i][j] = matrix[i][j + 1];
}


void delete_row(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, size_t to_del)
{
    for (size_t i = to_del; i < rows - 1; ++i)
        for (size_t j = 0; j < columns; ++j)
            matrix[i][j] = matrix[i + 1][j];
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

    size_t row_min, col_min;
    index_min_by_product_of_digit(matrix, rows, columns, &row_min, &col_min);
    delete_row(matrix, rows, columns, row_min);
    --rows;
    delete_column(matrix, rows, columns, col_min);
    --columns;


    if (!rows || !columns)
    {
        printf("Matrix is empty");
        return EMPTY_MATRIX;
    }

    printf("Modified matrix:\n");
    print_matrix(matrix, rows, columns);
    return EXIT_SUCCESS;
}
