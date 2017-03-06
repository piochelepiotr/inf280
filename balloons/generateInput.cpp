#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

int random(int min,int max)
{
    return ((int) (rand()%(max-min+1))) + min;
}

int main()
{
    srand (time(NULL));
    int number = random(1,300);
    for(int i = 0; i < number; i++)
    {
        int n = random(1,6);
        printf("%d\n",n);
        for(int j = 0; j < n+2; j++)
        {
            printf("%d %d %d\n",random(-10,10),random(-10,10),random(-10,10));
        }
    }
    printf("0\n");
}
