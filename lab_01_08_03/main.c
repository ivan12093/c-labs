#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t swap_bits(uint32_t number)
{
	uint32_t even_bits = number & 0xAAAAAAAA;
	uint32_t odd_bits = number & 0x55555555;
	
	even_bits >>= 1;
	odd_bits <<= 1;
	
	return even_bits | odd_bits;
}

void print_bin(uint32_t number, unsigned char depth)
{
	if (!number && depth == 32)
	{
		return;
	}
	
	print_bin(number / 2, depth + 1);
	printf("%u", number % 2);
}

int main(void)
{
	uint32_t number;
	
	printf("Enter unsigned number:\n");
	if (scanf("%u", &number) != 1)
	{
		printf("Error: can`t recognize input as unsigned number");
		return EXIT_FAILURE;
	}
	
	uint32_t swapped_number = swap_bits(number);
	
	printf("Result: ");
	print_bin(swapped_number, 0);
	printf("\n");
}

