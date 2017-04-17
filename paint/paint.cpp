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

void print_str(int *str, int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        cout << str[i] << " | ";
    }
    cout << endl;
}



//KMP algorithm taken from course and adapted

void KMP(int *p,int *s,int np, int ns)
{
    print_str(p,np);
    print_str(p+3,np-3);
    int *T = new int[np+1];
    T[0] = -1;
    int cnd = 0;
    for (int i = 1; i <= np; i++)
    {
        T[i] = cnd;
        while (cnd >= 0 && (p[cnd] != p[i] && p[i] != 2 && p[cnd] != 2))
        {
            cnd = T[cnd];
        }
        cnd++;
    }
    print_str(T,np+1);
    cnd = 0;
    // position courante dans le motif p
    for (int i = 0; i <= ns; i++)
    {
        // tant qu'on ne lit pas
        while (cnd >= 0 && (p[cnd] != 2 && p[cnd] != s[i]))// le prochain char de p
        {
            cnd = T[cnd];
        }
        // on recule dans p
        cnd++;
        // maintenant que le prochain char convient, avancer
        if (cnd == np)
        {
            // on a atteint la fin de p, donc on a trouvé un match
            printf("match at %d\n", i - np + 1);
            // on recule dans p au cas où le prochain match chevauche
            cnd = T[cnd];
        }
    }
}

int main()
{
    int hp,wp,hm,wm;
    string str;
    while (1)
    {
        hp = 0;
        cin >> hp >> wp >> hm >> wm;
        if (hp == 0)
        {
            break;
        }
        int p_size = wm*hp+wp-wm;
        int *p = new int [p_size];
        int *s = new int [hm*wm];
        for(int i = 0; i < hp; i++)
        {
            cin >> str;
            for(int j = 0; j < wp; j++)
            {
                p[wm*i+j] = (str[j] == 'o') ? 1 : 0;
            }
            if(i != hp - 1)
            {
                for(int j = wp; j < wm; j++)
                {
                    p[wm*i+j] = 2;
                }
            }
        }

        for(int i = 0; i < hm; i++)
        {
            cin >> str;
            for(int j = 0; j < wm; j++)
            {
                s[wm*i+j] = (str[j] == 'o') ? 1 : 0;
            }
        }

        //print_str(s+36,p_size);
        //print_str(p,p_size);

        KMP(p,s,p_size,hm*wm);

        delete [] p;
        delete [] s;
        cout << endl;
    }
    return 0;
}
