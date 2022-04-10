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
#define INCORRECT_MATRIX_ELEMENT 2
#define NO_NUMBERS_WITH_SUM_OF_DIGITS_GT_10 3


bool digit_sum_gt_10(int x)
{
    int sum_of_digit = 0;
    while (x)
    {
        sum_of_digit += abs(x % 10);
        x /= 10;
    }
    return sum_of_digit > 10;
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


void shift_left_array(int array[], size_t len, size_t times)
{
    for (size_t i = 0; i < times; ++i)
    {
        int front = array[0];
        for (size_t j = 0; j < len - 1; ++j)
            array[j] = array[j + 1];
        array[len - 1] = front;
    }
}


size_t copy_if_digit_sum_gt_10(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, int array[])
{
    size_t len_array = 0;
    for (size_t i = 0; i < rows; ++i)
        len_array += copy_if(matrix[i], columns, array + len_array, digit_sum_gt_10);
    return len_array;
}


void overwrite_digit_sum_gt_10(int matrix[][ROW_CAPACITY], size_t rows, size_t columns, int array[])
{
    size_t arr_index = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            if (digit_sum_gt_10(matrix[i][j]))
            {
                matrix[i][j] = array[arr_index];
                ++arr_index;
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
    
    int numbers[ROW_CAPACITY * COLUMN_CAPACITY];
    size_t count_numbers = copy_if_digit_sum_gt_10(matrix, rows, columns, numbers);
    if (!count_numbers)
    {
        printf("Error: no numbers with sum of digit greater than 10\n");
        return NO_NUMBERS_WITH_SUM_OF_DIGITS_GT_10;
    }
    shift_left_array(numbers, count_numbers, 3);
    overwrite_digit_sum_gt_10(matrix, rows, columns, numbers);

    printf("Modified matrix:\n");
    print_matrix(matrix, rows, columns);
    return EXIT_SUCCESS;
}
