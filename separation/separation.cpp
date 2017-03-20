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

int numOf(string const& name, map<string,int> & names, int & next)
{
    if(names.find(name) == names.end())
    {
        names[name] = next++;
    }
    return names[name];
}

/* modified version of BFS from the course*/

int BFS(int root,int P,vector<int> *adj)
{
    queue<pair<int,int>>Q;//id of vertex and deepth
    bool * Visited = new bool[P];
    for(int i = 0; i < P; i++)
    {
        Visited[i] = false;
    }
    Visited[root] = true;
    Q.push(make_pair(root,0));
    int max_depth = 0;
    while(!Q.empty())
    {
        int u = Q.front().first;
        int depth = Q.front().second;
        if(depth > max_depth)
        {
            max_depth = depth;
        }
        Q.pop();
        for(auto v : adj[u])
        {
            if(!Visited[v])
            {
                Q.push(make_pair(v,depth+1));        // usually do something with v
            }
            Visited[v] = true;
        }
    }
    for(int i = 0; i < P; i++)
    {
        if(!Visited[i])
        {
            return -1;
        }
    }
    return max_depth;
}

int main()
{
    string name1,name2;
    int netNum = 0;
    int P,R;
    while(1)
    {
        cin >> P >> R;
        if(P == 0 && R == 0)
        {
            break;
        }
        /*else if(netNum != 0)
        {
            cout << endl;
        }*/
        netNum++;
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
