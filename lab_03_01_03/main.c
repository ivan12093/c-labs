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

    bool increasing = true;
    for (size_t i = 1; i < array_size; ++i)
        if (array[i] < array[i - 1])
        {
            increasing = false;
            break;
        }
    
    bool decreasing = true;
    for (size_t i = 1; i < array_size; ++i)
        if (array[i] > array[i - 1])
        {
            decreasing = false;
            break;
        }

    return decreasing || increasing;
}


void mask_matrix(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, int mask[], bool (*predicate)(const int[], size_t))
{
    for (size_t i = 0; i < rows; ++i)
        mask[i] = predicate(matrix[i], columns);
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
