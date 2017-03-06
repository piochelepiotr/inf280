#include <stdio.h>
#include <deque>
#include <algorithm>
#include <deque>
#include <math.h>

using namespace std;
const double PI  =3.141592653589793238463;

typedef struct Point
{
    int x;
    int y;
    int z;
    double r;
}Point;

double rad(int p1,int p2,int p)
{
    if((p1 <= p && p <= p2) || (p2 <= p && p <= p1))
    {
        //ok, inside
        return min(abs(p2-p),abs(p1-p));
    }
    else
    {
        return -1;
    }
}

double rad3(Point const& p1, Point const& p2, Point const& p)
{
    return min(rad(p1.x,p2.x,p.x),min(rad(p1.y,p2.y,p.y),rad(p1.z,p2.z,p.z)));
}

double dist(Point const& p1, Point const& p2)
{
    return sqrt((double)(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) + pow((p1.z-p2.z),2))); 
}

//the last is the one to determine
bool maximumRadius(deque<Point> & points)
{
    double minimum = rad3(points[0],points[1],points.back());
    if(minimum != -1)
    {
        for(int i = 2; i < (int) points.size() - 3; i++)
        {
            minimum = min(minimum,dist(points[i],points.back())-points[i].r);
            if(minimum < 0)
                break;
        }
    }
    if(minimum < 0)
    {
        return false;
    }
    points.back().r = minimum;
    return true;
}

double solve(deque<Point> & placed,deque<Point> remaining, double volume)
{
    printf("volume %f et rest : ",volume);
    for(auto it : remaining)
    {
        printf("%d,",it.x);
    }
    printf("\n");
    double maximum = volume;
    for(int i = 0; i < (int) remaining.size(); i ++)
    {
        placed.push_back(remaining.front());
        remaining.pop_front();
        if(maximumRadius(placed))
        {
            maximum = max(maximum,solve(placed,remaining,volume + PI*(4.0/3.0)*pow(placed.back().r,3)));
        }
        remaining.push_back(placed.back());
        placed.pop_back();
    }
    return maximum;
}

int volume(Point const& p1, Point const& p2)
{
    return abs(p1.x-p2.x)*abs(p1.y-p2.y)*abs(p1.z-p2.z);
}

int main()
{
    int n,boxNum = 1;
    Point p;
    scanf("%d",&n);
    if(!n)
        return 0;
    do
    {
        deque<Point>placed;
        deque<Point>remaining;
        for(int j = 0; j < n + 2; j++)
        {
            scanf("%d %d %d",&p.x,&p.y,&p.z);
            if(j < 2)
                placed.push_back(p);
            else
                remaining.push_back(p);
        }
        for(auto it : remaining)
        {
            if(rad3(placed[0],placed[1],it) == -1)
                printf("dehors\n");
            else
                printf("dedans\n");
        }
        printf("distance %f\n",dist(remaining[0],remaining[1]));
        printf("Box %d: %d\n",boxNum,volume(placed[0],placed[1]) - (int) (round(solve(placed,remaining,0))));
        scanf("%d",&n);
        printf("\n");
        boxNum++;
    }while(n);
    printf("\n");
    return 0;
}
