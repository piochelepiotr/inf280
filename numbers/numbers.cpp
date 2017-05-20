#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

#define MAX_POW 55

long long *V;
long long *P;

void findPows(int maxPow)
{
    V = new long long[maxPow];
    P = new long long[maxPow];
    V[0] = 0;
    P[0] = 1;
    for(int i = 1; i < maxPow; i++)
    {
        V[i] = 2*V[i-1]+P[i-1];
        P[i] = 2*P[i-1];
    }
}

long long numberTo(long long n)
{
    long long oneNumber = 0;
    long long total = 0;
    //int maxPow = (int) log(n,2);
    int maxPow = MAX_POW;
    for(int i = maxPow; i >= 1; i--)
    {
        if(n >> (i-1) & 1)
        {
            total += (oneNumber*P[i-1] + V[i-1] + 1);
            oneNumber++;
        }
    }
    return total;
}

int main()
{
    findPows(MAX_POW);
    long long A,B;

    //long long E = 15;
    //if(E & (1 << 4))
    //{
    //    cout << "dsfsqdf" << endl;
    //}
    //cout << numberTo(4) << endl;
    while (1)
    {
        A = -1;
        B = -1;
        cin >> A >> B;
        if(A == -1 && B == -1)
        {
            break;
        }
        cout << numberTo(B) - numberTo(A-1) << endl;
    }
    return 0;
}
