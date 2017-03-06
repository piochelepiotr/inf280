#include <stdio.h>
#include <deque>
#include <algorithm>

using namespace std;

struct c_unique
{
    int current;
    c_unique() { current=1; }
    int operator()(){return current++;}
}UniqueNumber;

bool solve(int x, int k, int *value,int *numbers, int max = -1)
{
    numbers[0] = x / value[0];
    if(numbers[0] > max && max != -1) numbers[0] = max;
    if(k == 1)
    {
        return numbers[0] * value[0] == x;
    }
    //k > 1
    while(numbers[0] >= 0)
    {
        if(solve(x-numbers[0]*value[0],k-1,value+1,numbers+1,numbers[0]))
            return true;
        numbers[0]--;
    }
    return false;
}

int main()
{
    int n,k,x;
    int value[5];
    int numbers[5];
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
    {
        if(i != 0)
        {
            printf("\n");
        }
        scanf("\n%d %d",&x,&k);
        for(int j = 0; j < k; j++)
        {
            scanf("%d",value+j);
        }
        if(solve(x,k,value,numbers))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}
