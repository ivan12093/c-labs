#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint32_t swap_bits(uint32_t number)
{
    uint32_t even_bits = number & 0xAAAAAAAA;
    uint32_t odd_bits = number & 0x55555555;
    
    even_bits >>= 1;
    odd_bits <<= 1;
    
    return even_bits | odd_bits;
}

void print_bin(uint32_t number)
{
    for (int i = 31; i >= 0; --i)
    {
        uint32_t current_bit = (number >> i) & 1;
        printf("%"PRIu32, current_bit); 
    }
}

int main(void)
{
    uint32_t number;
    
    printf("Enter unsigned number:\n");
    if (scanf("%"SCNu32, &number) != 1)
    {
        printf("Error: can`t recognize input as unsigned number");
        return EXIT_FAILURE;
    }
    
    uint32_t swapped_number = swap_bits(number);
    
    printf("Result: ");
    print_bin(swapped_number);
    printf("\n");
}

