#include <stdio.h>
#include <deque>
#include <algorithm>
#include <vector>

using namespace std;

bool tooHeavy(vector<int> & w,int s, int n, int c)
{
    int sum = 0;
    for(int i = s; i < s+n; i++) sum += w[i];
    return sum > c;
}

int minToOrigin(vector<int> & x, vector<int> & y, int s, int n,int lastX,int lastY,vector<int> & passed)
{
    if((int) passed.size() == n)
    {
        return lastX + lastY;
    }
    int globMin = -1;
    for(int i = 0; i < n; i++)
    {
        if(find(passed.begin(),passed.end(),i+s) == passed.end())
        {
            passed.push_back(i+s);
            int minPath = minToOrigin(x,y,s,n,x[i+s],y[i+s],passed) + abs(lastX-x[i+s])+abs(lastY-y[i+s]);
            passed.pop_back();
            if(globMin == -1)
            {
                globMin = minPath;
            }
            else
            {
                globMin = min(minPath,globMin);
            }
        }
    }
    return globMin;
}

int minTrip(vector<int> &x,vector<int> & y, int s, int n)
{
    vector<int> passed;
    int minTo = minToOrigin(x,y,s,n,0,0,passed);
    return minTo;
}

int solve(vector<int> & x,vector<int> & y, vector<int> & w, int n,int c, vector<int> & min_dist, int s)
{
    min_dist[s] = 2*(x[s]+y[s]);
    if(s == n-1)
    {
        return min_dist[s]; 
    }
    
    min_dist[s] += solve(x,y,w,n,c,min_dist,s+1);//the case when we take only one package
    for(int i = 2; i <= n-s; i++)
    {
        //i represents the number of products this trip
        if(!tooHeavy(w,s,i,c))
        {
            min_dist[s] = min(min_dist[s],minTrip(x,y,s,i) + ((s+i == n) ? 0 : min_dist[s+i]));
        }
    }
    return min_dist[s];
}

int main()
{
    int number_cases,n,c,xp,yp,wp;
    scanf("%d",&number_cases);
    for(int i = 0; i < number_cases ; i++)
    {
        scanf("%d\n%d",&c,&n);
        vector<int>x;
        vector<int>y;
        vector<int>w;
        for(int j = 0; j < n ; j++)
        {
            scanf("%d %d %d",&xp,&yp,&wp);
            x.push_back(xp);
            y.push_back(yp);
            w.push_back(wp);
        }
        vector<int>min_dist(n);
        printf("%d\n",solve(x,y,w,n,c,min_dist,0));
        if(i + 1 != number_cases)
        {
            printf("\n");
        }
    }
    return 0;
}
