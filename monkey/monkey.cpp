#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;


void print_state(unsigned long state, int n)
{
    cout << "state " << state << " : ";
    for(int i = 0; i < n; i++)
    {
        if((1 << i) & state)
        {
            cout << "1";
        }
        else
        {
            cout << "0";
        }
    }
    cout << endl;
}

unsigned long next_state(unsigned long state,vector<int> * Adj, int n)
{
    unsigned long new_state = 0;
    for(int i = 0;i < n ; i++)
    {
        if(state & 1 << i)
        {
            for(auto v : Adj[i])
            {
                new_state |= 1 << v;
            }
        }
    }
    return new_state;
}

//modified version of BFS from the course
vector<int> BFS(bool *Visited,int n,vector<int> *Adj)
{
    queue<pair<int,vector<int>>> Q;
    vector<int> empty;
    Q.push(make_pair(pow(2,n)-1,empty));
    while (!Q.empty())
    {
        int state = Q.front().first;
        vector<int>shots = Q.front().second;
        if(state == 0)
            return shots;
        Q.pop();
        if (Visited[state]) continue;
        Visited[state] = true;
        for (int tree = 0; tree < n; tree++)
        {
            shots.push_back(tree);
            unsigned long state2 = state & ~(1 << tree);
            Q.push(make_pair(next_state(state2 & ~(1 << n),Adj,n),shots));
            shots.pop_back();
        }
    }
    return empty;
}

int main()
{
    int n, m, a, b;
    while (1)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
        {
            break;
        }
        vector<int> *Adj = new vector<int>[n];
        for (int i = 0; i < m; i++)
        {
            cin >> a >> b;
            Adj[a].push_back(b);
            Adj[b].push_back(a);
        }
        int max = (int) pow(2,n);
        bool *Visited = new bool[max];
        for(int i = 0; i < max; i++)
        {
            Visited[i] = false;
        }
        vector<int> res = BFS(Visited,n,Adj);
        if (res.empty())
            cout << "Impossible";
        else
        {
            cout << res.size() << ":";
            for(auto v : res)
            {
                cout << " " << v;
            }
        }
        delete [] Visited;
        delete [] Adj;
        cout << endl;
    }
    return 0;
}
