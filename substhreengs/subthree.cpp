#include <stdio.h>
#include <deque>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <iostream>
#include <queue>

using namespace std;


int main()
{
    string str;
    while(1)
    {
        cin >> str;
        if(str.empty())
        {
            break;
        }
        vector<int> *adj = new vector<int>[P];
        map<string,int>names;
        int next = 0;
        for(int i = 0; i < R; i++)
        {
            cin >> name1 >> name2;
            int num1 = numOf(name1,names,next);
            int num2 = numOf(name2,names,next);
            adj[num1].push_back(num2);
            adj[num2].push_back(num1);
        }
        int max = 0;
        for(int i = 0; i < P; i++)
        {
            int max2 = BFS(i,P,adj);
            if(max2 > max || max2 == -1)
            {
                max = max2;
            }
            if(max == -1)
            {
                break;
            }
        }
        cout << "Network "<< netNum << ": ";
        if(max == -1)
            cout << "DISCONNECTED";
        else
            cout << max;
        cout << endl;
        cout << endl;
    }
    return 0;
}
