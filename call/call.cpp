#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

#define PMAX 100000


//algorithm from the course to find prime numbers
bitset<10000001> P;
vector<long long> premiers;

void findPrimeNumbers()
{
    P.set();
    // initialisation
    P[0] = P[1] = 0;
    for (long long i = 2; i < PMAX; i++)
    {
        if(P[i])
        {
            for (long long j = i * i; j < PMAX; j += i)
            {
                P[j] = 0;
            }
            premiers.push_back(i);
        }
    }
}

void solve(int m, int a, int b, int & p, int & q)
{
    //vector<long long> newprem;
    //for(auto x : premiers)
    //{
    //    if(x < m)
    //    {
    //        newprem.push_back(x);
    //    }
    //    else
    //    {
    //        break;
    //    }
    //}
    p = 0;
    q = 0;
    for(auto newq : premiers)
    {
        if(newq > m)
        {
            break;
        }
        for(auto newp : premiers)
        {
            if(newp > newq)
            {
                break;
            }
            int newarea = newp*newq;
            if(newarea > m)
            {
                break;
            }
            if(newarea > p*q)
            {
                if(newq*a <= newp*b)
                {
                    p = newp;
                    q = newq;
                }
            }
        }
    }
}

int main()
{
    findPrimeNumbers();
    int m, a, b, p, q;
    while (1)
    {
        cin >> m >> a >> b;
        if (m == 0 && a == 0 && b == 0)
        {
            break;
        }
        solve(m,a,b,p,q);
        cout << p << " " << q << endl;
    }
    return 0;
}
