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
    printf("%d\n",number);
    for(int i = 0; i < number; i++)
    {
        int m = random(1,500);
        int k = random(1,m);
        printf("%d %d\n",m,k);
        for(int j = 0; j < m; j++)
        {
            printf("%d",random(1,10000000));
            if(j + 1 == m)
                printf("\n");
            else
                printf(" ");
        }
    }
}
