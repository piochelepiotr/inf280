#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
#define INF 100000000000.0
#define PREC 0.001

struct point
{
    double x, y;
    point() {
        x=0.0; y=0.0;
    }
    point(double in_x, double in_y): x(in_x), y(in_y) {}
};

void minToEnd(double &a, double &b, double &c,point &pa, point &pb, point &pc)
{
    if(a < b)
    {
        if(a < c)
        {
            double tmp = a;
            a = c;
            c = tmp;
            point ptmp = pa;
            pa = pc;
            pc = ptmp;
        }
        //else max = c, ok
    }
    else
    {
        if(b < c)
        {
            double tmp = b;
            b = c;
            c = tmp;
            point ptmp = pb;
            pb = pc;
            pc = ptmp;
        }
        //else max = c, ok
    }
}

//fonction finds center of the circumscribed cercle
point findCenter(point const& p1, point const& p2, point const& p3)
{
    //mediatrice p1 to p2
    double dist = p2.x - p1.x;
    double a1 = (dist == 0) ? INF : (p2.y - p1.y)/(dist);
    point m1 = point((p1.x+p2.x)/2,(p1.y+p2.y)/2);
    //mediatrice p1 to p3
    dist = p3.x - p1.x;
    double a2 = (dist == 0) ? INF : (p3.y - p1.y)/(dist);
    point m2 = point((p1.x+p3.x)/2,(p1.y+p3.y)/2);
    //mediatrice p2 to p3
    dist = p3.x - p2.x;
    double a3 = (dist == 0) ? INF : (p3.y - p2.y)/(dist);
    point m3 = point((p3.x+p2.x)/2,(p3.y+p2.y)/2);
    //if an a is 0, it will be put at the end
    minToEnd(a1,a2,a3,m1,m2,m3);


    double ap1 = -1/a1;
    double ap2 = -1/a2;

    double x = (m2.y-m1.y+ap2*(m1.x-m2.x))/(ap1-ap2);
    double y = m1.y + ap1*x;

    point center = point(m1.x+x,y);
    return center;
}

double computeAngle(point a, point b,point center)
{
    return fabs(atan2(a.x-center.x, a.y-center.y)-atan2(b.x-center.x, b.y-center.y));
}

double computePgcd(double angle1, double angle2)
{
    while(angle1*angle2 > PREC)
    {
        if(angle1 > angle2)
        {
            angle1 -= angle2;
        }
        else
        {
            angle2 -= angle1;
        }
    }
    if(fabs(angle1) < PREC)
    {
        return angle2;
    }
    else
    {
        return angle1;
    }
}

double commonPgcd(point const& p1, point const& p2, point const& p3,point const& center)
{
    return computePgcd(computePgcd(computeAngle(p1,p2,center),computeAngle(p1,p3,center)),computeAngle(p2,p3,center));
}

int main()
{
    point p1,p2,p3;
    cin >> p1.x;
    while(1)
    {
        cin >> p1.y;
        cin >> p2.x >> p2.y;
        cin >> p3.x >> p3.y;
        point center = findCenter(p1,p2,p3);
        double angle = commonPgcd(p1,p2,p3,center);
        int minVertexes = 2*M_PI / angle;

        cout << minVertexes << endl;

        string str;
        cin >> str;
        if(str == "END")
            break;
        else
            p1.x = atof(str.c_str());
    }
    return 0;
}

