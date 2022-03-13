#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int number;
    
    printf("Enter the number:\n");
    if (scanf("%d", &number) != 1)
        return EXIT_FAILURE;
    
    int product = 1;
    for (int i = 0; i < 3; ++i)
    {
        product *= abs(number % 10);
        number /= 10;
    }
    
    if (number)
        return EXIT_FAILURE;

    printf("Product of digits: %d\n", product);
    return EXIT_SUCCESS;
}

