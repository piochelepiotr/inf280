#include <stdio.h>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct c_unique
{
    int current;
    c_unique() { current=1; }
    int operator()(){return current++;}
}UniqueNumber;

void extract1(deque<int> & order, int numToExtract)
{
    order.erase(find(order.begin(),order.end(),numToExtract));
    order.push_front(numToExtract);
}

int next_candidate1(deque<int> & order)
{
    int n = order.front();
    order.push_back(n);
    order.pop_front();
    return n;
}

void extract2(vector<int> & extracted, int numToExtract)
{
    if(find(extracted.begin(), extracted.end(),numToExtract) == extracted.end())
    {
        extracted.push_back(numToExtract);
    }
}

int next_candidate2(vector<int> & extracted, int & num)
{
    do
    {
        num++;
    }while(find(extracted.begin(), extracted.end(),num) != extracted.end());
    return num;
}

void solve1(int p, int c)
{
    char action;
    int prioritary;
    deque<int>order(p);
    generate(order.begin(),order.end(),UniqueNumber);
    for(int i = 0; i < c; i++)
    {
        scanf("\n%c",&action);
        if(action == 'E')
        {
            scanf("%d",&prioritary);
            extract1(order,prioritary);
        }
        else
        {
            printf("%d\n",next_candidate1(order));
        }
    }
}

void solve2(int c)
{
    int prioritary;
    char action;
    deque<int>firsts;
    vector<int>extracted;
    int num = 0;
    for(int i = 0; i < c; i++)
    {
        scanf("\n%c",&action);
        if(action == 'E')
        {
            scanf("%d",&prioritary);
            extract2(extracted,prioritary);
            firsts.push_back(prioritary);
        }
        else
        {
            if(!firsts.empty())
            {
                printf("%d\n",firsts.front());
                firsts.pop_front();
            }
            else
            {
                next_candidate2(extracted,num);
                printf("%d\n",num);
            }
        }
    }
}

int main()
{
    int p,c,numCase = 0;
    while(1)
    {
        numCase++;
        scanf("%d %d",&p,&c);
        if(p == 0 && c == 0)
        {
            return 0;
        }
        printf("Case %d:\n",numCase);
        if(c > p)
        {
            solve1(p,c);
        }
        else
        {
            solve2(c);
        }
           
    }
    return 0;
}
