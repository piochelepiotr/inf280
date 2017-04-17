#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define INF numeric_limits<int>::max()

// goal is to find an eulerian circuit

using namespace std;

map<int, pair<int, unsigned int>> Sets;    // map to parent & rank

void MakeSet(int x) { Sets.insert(make_pair(x, make_pair(x, 0))); }

int Find(int x) {
    if (Sets[x].first == x)
        return x;    // Parent == x ?
    else
        return Sets[x].first = Find(Sets[x].first);    // Get Parent
}

void Union(int x, int y) {
    int parentX = Find(x), parentY = Find(y);
    int rankX = Sets[parentX].second, rankY = Sets[parentY].second;
    if (parentX == parentY)
        return;
    else if (rankX < rankY)
        Sets[parentX].first = parentY;
    else
        Sets[parentY].first = parentX;
    if (rankX == rankY) Sets[parentX].second++;
    ;
}

vector<pair<int, pair<int, int>>> Edges;
int Kruskal() {
    int dist = 0;
    for (auto tmp : Edges) {
        auto edge = tmp.second;
        if (Find(edge.first) != Find(edge.second)) {
            Union(edge.first, edge.second);    // update Union-Find DS
            dist += tmp.first;
        }
    }
    return dist;
}

int initSet(vector<int> *subNets, unsigned char chosen, int q, vector<int> & prices,int N)
{
    Sets.clear();
    int price = 0;
    for (int u = 0; u < N; u++)
    {
        MakeSet(u);    // Initialize Union-Find DS
    }
    for(int j = 0; j < q; j++)
    {
        if(chosen & (1 << j))
        {
            int first = subNets[j].front();
            price += prices[j];
            for (int i = 1; i < (int) subNets[j].size(); i++)
            {
                Union(first, subNets[j][i]);
            }
        }
    }
    return price;
}

void display_result(vector<int> &v) {
    int previous = v.front();
    for (int i = 1; i < (int)v.size(); i++) {
        cout << previous << " " << v[i] << endl;
        previous = v[i];
    }
}

int solveR(int n, int q, vector<int> *subNets,vector<int> & prices,vector<int> & rest, unsigned char chosen,int price)
{
    if(rest.empty())
    {
        return price;
    }
    for(auto i : rest)
    {
        int newPrice = initSet(subNets,chosen + pow(2,i),q,prices,n);
        if(newPrice < price)
        {
            newPrice += Kruskal();
            if(newPrice < price)
            {
                price = newPrice;
                newPrice = solveR(n,q,subNets,prices,rest2,chosen + pow(2,i),price);
                if(newPrice < price)
                    return price;
}

int solve(int n, int q, vector<int> *subNets,vector<int> & prices)
{
    unsigned char chosen = 0;
    int price = initSet(subNets,0,q,prices,n);
    price += Kruskal();
    for(int i = 0; i < q; i++)
    {
        int newPrice = initSet(subNets,pow(2,i),q,prices,n);
        if(newPrice < price)
        {
            newPrice += Kruskal();
            if(newPrice < price)
            {
                chosen += pow(2,i);
            }
        }
    }
    cout << "sol : " << (int) chosen << endl;
    price = initSet(subNets,chosen,q,prices,n);
    price += Kruskal();
    return price;
}

void make_edges(vector<pair<int,int>> & cities, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            Edges.push_back(make_pair(pow(cities[i].first-cities[j].first,2)+pow(cities[i].second-cities[j].second,2),make_pair(i+1,j+1)));
        }
    }
    sort(Edges.begin(), Edges.end());                // Sort edges by weight
}

int main()
{
    int numberCases;
    cin >> numberCases;
    int a, b, n, q;
    vector<int> *subNets = 0;
    vector<int> prices;
    vector<pair<int,int>>cities;
    for (int i = 0; i < numberCases; i++)
    {
        if (i != 0)
        {
            cout << endl;
        }
        cin >> n >> q;
        subNets = new vector<int>[q];
        prices.clear();
        cities.clear();
        for (int j = 0; j < q; j++)
        {
            int nbr, w;
            cin >> nbr >> w;
            prices.push_back(w);
            for (int k = 0; k < nbr; k++)
            {
                cin >> a;
                subNets[j].push_back(a);
            }
        }
        for(int j = 0; j < n; j++)
        {
            cin >> a >> b;
            cities.push_back(make_pair(a,b));
        }
        make_edges(cities,n);
        cout << solve(n,q,subNets,prices) << endl;
    }
    return 0;
}
