#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<float> pointsx;
    vector<float> pointsy;
    int nx,ny;
    float w;
    float current;
    for(int j = 0; j < 4; j++)
    {
LOOP:
        scanf("%d %d %f",&nx,&ny,&w);
        float w2 = w/2;
        if(nx == 0 && ny == 0 && w == 0)
        {
            return 0;
        }
        pointsx.clear();
        for(int i = 0; i < nx; i++)
        {
            scanf("%f",&current);
            pointsx.push_back(current);
        }
        pointsy.clear();
        for(int i = 0; i < ny; i++)
        {
            scanf("%f",&current);
            pointsy.push_back(current);
        }
        sort(pointsx.begin(),pointsx.end());
        pointsx.push_back(75+w2);
        current = -w2;;
        for(auto t : pointsx)
        {
            if(w < t-current)
            {
                printf("NO\n");
                goto LOOP;
            }
            current = t;
        }
        sort(pointsy.begin(),pointsy.end());
        pointsy.push_back(100-w2);
        current = -w2;
        for(auto t : pointsy)
        {
            if(w < t-current)
            {
                printf("NO\n");
                goto LOOP;
            }
            current = t;
        }
        printf("YES\n");
    }
    return 0;
}
