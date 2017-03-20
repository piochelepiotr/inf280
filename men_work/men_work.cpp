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

//he is at step-1 on the cell and wants to know how much time he can stay on it
int maxStay(

int timeToOpen(bool initialState,int delay,int step,bool initialStateStart,int delayStart)
{
    if(delay == 0)
    {
        return (initialState) ? 0 : MAXLEN;
    }
    //delay != 0
    bool pair = ((int) (step/delay)) % 2 == 0;
    if((pair && initialState) || (!pair && !initialState))
    {
        return 0;
    }
    else
    {
        //have to check that the cell on witch we are is free until the end
        int steps = delay - (step % delay); //time it has to wait on the current cell
        if(delayStart == 0)
        {
            if(initialStateStart)
                return steps;
            else
                return MAXLEN;
        }
        //we know that during the previous step, it was OK, we look for the place of the change
        for(int i = 0; i < steps; i++)
        {
            if((step+i)%delayStart == 0)
                return MAXLEN;
        }
        return steps;
        //if(steps <= (delayStart - (step % delayStart))%delayStart)
        //    return steps;
        return steps;
    }
}

void getAdj(int u, vector<int> & adj,int N)
{
    int line = u / N;
    int column = u % N;
    if(line > 0)
    {
        adj.push_back((line-1)*N+(column));
    }
    if(line < N-1)
    {
        adj.push_back((line+1)*N+(column));
    }
    if(column > 0)
    {
        adj.push_back((line)*N+(column-1));
    }
    if(column < N-1)
    {
        adj.push_back((line)*N+(column+1));
    }
}

/*Modified version of Djikstra from the course*/
int Dijkstra(bool *starts,int *delay,int N)
{
    int root = 0;
    unsigned int *Dist = new unsigned int[N*N];
    priority_queue<WeightNode, std::vector<WeightNode>,std::greater<WeightNode> > Q;
    fill_n(Dist, N*N, MAXLEN);
    Dist[root] = 0;
    Q.push(make_pair(0, root));
    while(!Q.empty())
    {
        int u = Q.top().second;
        cout << "sommet : " << u << endl;
        // get node with least priority
        Q.pop();
        vector<int>adj;
        getAdj(u,adj,N);
        for(auto tmp : adj)
        {
            int v = tmp;
            unsigned int weight = 1 + timeToOpen(starts[v],delay[v],Dist[u]+1,starts[u],delay[u]);
            if(Dist[v] > Dist[u] + weight)
            {
                // shorter path found?
                Dist[v] = Dist[u] + weight;
                Q.push(make_pair(Dist[v], v));
                // simply push, no update here
            }
        }
    }
    return Dist[N*N-1];
}

int main()
{
    int N;
    int n = 0;
    char c;
    while(1)
    {
        N = -1;
        cin >> N;
        if(N == -1)
        {
            break;
        }
        else if(n != 0)
        {
            cout << endl;
        }
        n++;
        bool *start_opened = new bool[N*N];
        int *delays  = new int[N*N];
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                cin >> c;
                start_opened[i*N+j] = (c == '.');
            }
        }
        for(int i = 0; i < N; i++)
        {
            for(int j=0; j < N; j++)
            {
                    cin >> c;
                    delays[i*N+j] = c - '0';
            }
        }
        int min = Dijkstra(start_opened,delays,N);
        if(min == MAXLEN)
            cout << "NO";
        else
            cout << min;
        cout << endl;
    }
    return 0;
}
