#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double start_speed;
    double acceleration;
    double time;
    
    printf("Enter start speed:\n");
    if (scanf("%lf", &start_speed) != 1)
        return EXIT_FAILURE;
    
    printf("Enter acceleration:\n");
    if (scanf("%lf", &acceleration) != 1)
        return EXIT_FAILURE;
    
    printf("Enter time:\n");
    if (scanf("%lf", &time) != 1)
        return EXIT_FAILURE;
    
    if (time < 0)
        return EXIT_FAILURE;

    double moving = start_speed * time + acceleration * time * time / 2;
    
    printf("Moving is: %.6lf metres\n", moving);
    return EXIT_SUCCESS;
}

