#include <stdio.h>
#include <deque>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

void first_answer(vector<long> & pages, vector<long> & weight, vector<long> & sep,long m, long k)
{
    for(long i = 0; i < k-1;i++)
    {
        sep.push_back(i);
        weight.push_back(pages[i]);
    }
    weight.push_back(pages[k-1]);
    for(long i = k; i < m; i++)
    {
        weight[k-1] += pages[i];
    }
}

void display_result(vector<long> & pages,vector<long> & sep, long m)
{
    long prec = 0;
    sep.push_back(m-1);
    for(auto it : sep)
    {
        for(long j = prec; j < it+1; j++, prec++)
        {
            if(j != 0)
            {
                printf(" ");
            }
            printf("%ld",pages[j]);
        }
        if(prec != m)
        {
            printf(" /");
        }
    }
    sep.pop_back();
    printf("\n");
}

void display_result(vector<long> & pages,vector<long> & sep,long m, std::string str)
{
    printf("%s :",str.c_str());
    display_result(pages,sep,m);
} 

void display(vector<long> & v, std::string str)
{
    printf("%s : [", str.c_str());
    for(auto it : v)
    {
        printf("%ld,",it);
    }
    printf("]\n");
}

bool improve_left(vector<long> &pages,vector<long> & weight, vector<long> &sep,long i,long MAX, long m)
{
    //printf("i = %ld\n",i);
    //display_result(pages,sep,m,"avant left");
    if(i == -1)
        return false;
    if(i == 0)
        return weight[0] < MAX;
    long n = 0;
    while(weight[i] >= MAX)
    {
        n++;
        //moves the sep
        weight[i] -= pages[sep[i-1]+1];
        weight[i-1] += pages[sep[i-1]+1];
        sep[i-1]++;
    }
    //display_result(pages,sep,m,"apres left");
    if(!improve_left(pages,weight,sep,i-1,MAX,m))
    {
        for(long j = 0; j < n; j++)
        {
            //moves the sep
            sep[i-1]--;
            weight[i] += pages[sep[i-1]+1];
            weight[i-1] -= pages[sep[i-1]+1];
        }
        return false;
    }
    else
    {
        return true;
    }
}

bool improve_right(vector<long> &pages,vector<long> & weight, vector<long> &sep, long k,long i,long MAX,long m)
{
    //display_result(pages,sep,m,"avant right");
    if(i == k)
        return false;
    if(i == k-1)
        return weight[k-1] < MAX;
    long n = 0;
    while(weight[i] >= MAX)
    {
        n++;
        //moves the sep
        weight[i] -= pages[sep[i]];
        weight[i+1] += pages[sep[i]];
        sep[i]--;
    }
    //display_result(pages,sep,m,"apres right");
    if(!improve_right(pages,weight,sep,k,i+1,MAX,m))
    {
        for(long j = 0; j < n; j++)
        {
            //moves the sep
            sep[i]++;
            weight[i] += pages[sep[i]];
            weight[i+1] -= pages[sep[i]];
        }
        return false;
    }
    else
    {
        return true;
    }
}

bool improve(vector<long> & pages, vector<long> & weight, vector<long> & sep, long k,long m)
{
    long MAX = weight[0],ind_max = 0;
    for(long i = 1; i < k; i++)
    {
        if(weight[i] > MAX)
        {
            MAX = weight[i];
            ind_max = i;
        }
    }
    bool modif = improve_left(pages,weight,sep,ind_max,MAX,m);
    if(modif)
        return true;
    return improve_right(pages,weight,sep,k,ind_max,MAX,m);
}

void solve(vector<long> & pages, vector<long> & weight, vector<long> & sep, long m,long k)
{
    first_answer(pages,weight,sep,m,k);
    while(improve(pages,weight,sep,k,m)){}
}

int main()
{
    long n,m,k,p;
    scanf("%ld",&n);
    for(long i = 0; i < n; i++)
    {
        vector<long>pages;
        vector<long>weight;
        vector<long>sep;
        scanf("%ld %ld",&m,&k);
        for(long j = 0; j < m; j++)
        {
            scanf("%ld",&p);
            pages.push_back(p);
        }
        solve(pages,weight,sep,m,k);
        //display answer
        display_result(pages,sep,m);
    }
    return 0;
}
