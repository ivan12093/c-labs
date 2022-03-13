#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int number;
    
    printf("Enter the number:\n");
    scanf("%d", &number);
    
    int product = 1;
    for (int i = 0; i < 3; ++i)
    {
        product *= abs(number % 10);
        number /= 10;
    }

    printf("Product of digits: %d\n", product);
    return EXIT_SUCCESS;
}

