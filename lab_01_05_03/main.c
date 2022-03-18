#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    while (b)
    {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    
    return a;
}

int main(void)
{
    int a, b;
    
    printf("Enter two natural numbers separated by a space:\n");
    if (scanf("%d%d", &a, &b) != 2)
        return EXIT_FAILURE;

    if (a <= 0 || b <= 0)
        return EXIT_FAILURE;

    int answer = gcd(a, b);

    printf("GCD is: %d\n", answer);
    return EXIT_SUCCESS;
}

