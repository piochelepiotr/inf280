#include <stdio.h>
#include <deque>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <iostream>
#include <queue>
#include <stack>
#define MAXLEN 100000000
#define MAX_COLOR 51

//goal is to find an eulerian circuit

using namespace std;

//this code has been taken from the course
bool Hierholzer(vector<int> *Adj,vector<int> &Circuit,int N)
{
    int v = 0;
    //if there is a node with odd degree return false
    for(int u=0; u < N && v == 0; u++)
    {
        if(Adj[v].size() == 0 && Adj[u].size() > 0)
        {
            v = u;
        }
        if(Adj[u].size() & 1)
        {
            return false;
        }
        // node with odd degree
    }
    stack<int> Stack;
    Stack.push(v);
    while(!Stack.empty())
    {
        if(!Adj[v].empty())
        {
            // follow edges until stuck
            Stack.push(v);
            int tmp = *Adj[v].begin();
            Adj[v].erase(find(Adj[v].begin(),Adj[v].end(), tmp));
            // remove edge, modifying graph
            Adj[tmp].erase(find(Adj[tmp].begin(),Adj[tmp].end(), v));
            //Adj[tmp].erase(Adj[tmp].begin() + v);
            v = tmp;
        }
        else
        {
            // got stuck: stack contains a circuit
            Circuit.push_back(v);
            // append node at the end of circuit
            v = Stack.top();
            // backtrack using stack, find larger circuit
            Stack.pop();
        }
    }
    return true;
}

void display_result(vector<int> &v)
{
    int previous = v.front();
    for(int i = 1; i < (int)v.size(); i++)
    {
        cout << previous << " " << v[i] << endl;
        previous = v[i];
    }
}

int main()
{
    vector<int> *adj = new vector<int>[MAX_COLOR];
    int T,N;
    cin >> T;
    int a,b;
    for(int n = 0; n < T; n++)
    {
        for(int i = 0; i < MAX_COLOR; i++)
        {
            adj[i].clear();
        }
        if(n > 0)
        {
            cout << endl;
        }
        cin >> N;
        for(int i = 0; i < N; i++)
        {
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        cout << "Case #"<<n+1<<endl;
        vector<int> Circuit;
        if(!Hierholzer(adj,Circuit,MAX_COLOR))
        {
            cout << "some beads may be lost"<<endl;
        }
        else
        {
            display_result(Circuit);
            cout << endl;
        }
    }
    return 0;
}

