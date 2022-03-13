#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double start_speed;
    double acceleration;
    double time;
    
    printf("Enter start speed:\n");
    scanf("%lf", &start_speed);

    printf("Enter acceleration:\n");
    scanf("%lf", &acceleration);
    
    printf("Enter time:\n");
    scanf("%lf", &time);

    double moving = start_speed * time + acceleration * time * time / 2.0;
    
    printf("Moving is: %.6lf metres\n", moving);
    return EXIT_SUCCESS;
}
