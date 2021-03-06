#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <iostream>

#define ZERO 0.000000001
#define INF 1000000000000
#define STEP 0.001

using namespace std;

struct point
{
    double x, y;
    point() {
        x=0.0; y=0.0;
    }
    point(double in_x, double in_y): x(in_x), y(in_y) {}
};

double computeAngle(point const& center, point const& p)
{
    double x = p.x - center.x;
    double y = p.y - center.y;
    if(fabs(x) < ZERO)
    {
        if(y > 0)
            return M_PI/2;
        else
            return -M_PI/2;
    }
    return atan(y/x) -M_PI*((x < 0) ? 1 : 0);
}

double distToPoint(point const& center, double rotAngle,point const& p)
{
    double angle = computeAngle(center,p)-rotAngle;
    double R = sqrt(pow(p.x-center.x,2) + pow(p.y - center.y,2));
    return R*sin(angle);
}

double solve(point *points,int n)
{
    double min = INF;
    for(double rotAngle = 0; rotAngle < M_PI; rotAngle += STEP)
    {
        double maxUp = 0;
        double maxDown = 0;
        for(int k = 0; k < n; k++)
        {
            if(k != 0)
            {
                double dist = distToPoint(points[0], rotAngle, points[k]);
                if(dist > maxUp)
                {
                    maxUp = dist;
                }
                else if(dist < maxDown)
                {
                    maxDown = dist;
                }
            }
        }
        double max = maxUp - maxDown;
        if(max < min)
        {
            min = max;
        }
    }
    return min;
}

int main()
{
    int num = 0,n;
    cout.precision(2);
    while(1)
    {
        num++;
        cin >> n;
        if(n == 0)
        {
            break;
        }
        point *points = new point[n];
        for(int i = 0; i < n; i++)
        {
            cin >> points[i].x >> points[i].y;
        }
        cout << "Case " << num << ": " << fixed << solve(points,n) << endl;
        delete [] points;
    }
    return 0;
}

