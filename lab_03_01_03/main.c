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


bool is_monotonic(const int array[], size_t array_size)
{
    if (array_size < 2)
        return false;

    // sign shows what sequence do: decreasing -1, increasing 1, equality - 0 
    int sign = (array[1] - array[0] > 0) - (array[1] - array[0] < 0);
    int new_sign;

    for (size_t i = 1; i < array_size - 1; ++i)
    {
        new_sign = (array[i + 1] - array[i] > 0) - (array[i + 1] - array[i] < 0);

        if (sign && new_sign)
        {
            if (sign != new_sign)
                return false;
            sign = new_sign;
        }
    }

    return (!(sign && new_sign) || sign == new_sign);
}


void mask_matrix(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, int mask[], bool (*predicate)(const int[], size_t))
{
    for (size_t i = 0; i < rows; ++i)
        mask[i] = predicate(matrix[i], columns);
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

    int mask[COLUMN_CAPACITY];
    mask_matrix(matrix, rows, columns, mask, is_monotonic);

    printf("Mask for matrix:\n");
    print_array(mask, rows);
    return EXIT_SUCCESS;
}