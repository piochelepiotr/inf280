#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

int main()
{
    findPows(MAX_POW);
    long long A,B;
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
