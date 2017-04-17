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

bool dispo(bool init,int delay,int step)
{
    if(delay == 0)
    {
        return init;
    }
    bool pair = (step/delay)%2 == 0;
    if((pair && init) || (!pair && !init))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void voisins(int u, vector<int> & adj,int N)
{
    adj.clear();
    adj.push_back(u);
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

void nextStep(bool *cells,int N,bool *newCells, bool *start, int *delay,int step)
{
    vector<int>nexts;
    for(int i = 0; i < N*N; i++)
    {
        newCells[i] = false;
    }
    for(int i = 0; i < N*N; i++)
    {
        if(cells[i])
        {
            voisins(i,nexts,N);
            for(auto j : nexts)
            {
                if(dispo(start[j],delay[j],step+1))
                {
                    newCells[j] = true;
                }
            }
        }
    }
}

int findMin(bool *start,int *delay,int N)
{
    bool *cells = new bool[N*N];
    bool *newCells = new bool[N*N];
    for(int i =0; i < N*N; i++)
    {
        cells[i] = false;
    }
    cells[0] = true;
    for(int step = 0; step < N*N; step++)
    {
        nextStep(cells,N,newCells,start,delay,step);
        bool *s = cells;
        cells = newCells;
        newCells = s;
        if(cells[N*N-1])
            return step + 1;
    }
    return -1;
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
        int min = findMin(start_opened,delays,N);
        if(min == -1)
            cout << "NO";
        else
            cout << min;
        cout << endl;
    }
    return 0;
}
