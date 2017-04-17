#include <stdio.h>
#include <deque>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <iostream>
#include <queue>

#define MAXLEN 100000000

using namespace std;
typedef pair<unsigned int,int> WeightNode;// weight goes first

void remove(vector<pair<int,int>> &adj,int ind)
{
    for(int i = 0; i < (int) adj.size(); i++)
    {
        if(adj[i].first == ind)
        {
            adj.erase(adj.begin()+i);
        }
    }
}

/*Modified version of Djikstra from the course*/
int Dijkstra(vector<pair<int,int>> *adj,int N, int root, int D)
{
    vector<int> *prev = new vector<int>[N];
    unsigned int *Dist = new unsigned int[N];
    priority_queue<WeightNode, std::vector<WeightNode>,std::greater<WeightNode> > Q;
    fill_n(Dist, N, MAXLEN);
    Dist[root] = 0;
    Q.push(make_pair(0, root));
    while(!Q.empty())
    {
        int u = Q.top().second;
        // get node with least priority
        Q.pop();
        for(auto tmp : adj[u])
        {
            int v = tmp.first;
            unsigned int weight = tmp.second;
            if(Dist[v] > Dist[u] + weight)
            {
                prev[v].clear();
                prev[v].push_back(u);
                // shorter path found?
                Dist[v] = Dist[u] + weight;
                Q.push(make_pair(Dist[v], v));
                // simply push, no update here
            }
            else if(Dist[v] == Dist[u] + weight)
            {
                prev[v].push_back(u);
            }
        }
    }
    bool *visited = new bool[N];
    for(int i = 0; i < N; i++)
    {
        visited[i] = false;
    }
    deque<int>remaining;
    remaining.push_back(D);
    while(!remaining.empty())
    {
        int s = remaining.front();
        remaining.pop_front();
        if(!visited[s])
        {
            visited[s] = true;
            for(auto vert : prev[s])
            {
                remove(adj[vert],s);
                remaining.push_back(vert);
            }
        }
    }
    //now, path without the shortests paths
    fill_n(Dist, N, MAXLEN);
    Dist[root] = 0;
    //Q is empty
    Q.push(make_pair(0, root));
    while(!Q.empty())
    {
        int u = Q.top().second;
        // get node with least priority
        Q.pop();
        for(auto tmp : adj[u])
        {
            int v = tmp.first;
            unsigned int weight = tmp.second;
            if(Dist[v] > Dist[u] + weight)
            {
                // shorter path found?
                Dist[v] = Dist[u] + weight;
                Q.push(make_pair(Dist[v], v));
                // simply push, no update here
            }
        }
    }

    return Dist[D];
}

int main()
{
    int N,M;
    int S,D;
    int n = 0;
    int a,b,w;
    while(1)
    {
        cin >> N >> M;
        if(N == 0 && M == 0)
        {
            break;
        }
        cin >> S >> D;
        n++;
        vector<pair<int,int>> *adj = new vector<pair<int,int>>[N];

        for(int i = 0; i < M; i++)
        {
            cin >> a >> b >> w;
            adj[a].push_back(make_pair(b,w));
        }
        int min = Dijkstra(adj,N,S,D);
        if(min == MAXLEN)
            cout << "-1";
        else
            cout << min;
        cout << endl;
    }
    return 0;
}
