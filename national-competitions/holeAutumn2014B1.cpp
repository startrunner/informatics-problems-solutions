#include <cstdio>
#include <vector>
#include <malloc.h>
#include <algorithm>
using namespace std;

const int MaxN=1000;

int n, m;
vector<vector<int>> wall;

int main()
{
    scanf("%d", &n);
    m=n-1;

    wall.resize(n, vector<int>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d", &wall[i][j]);
        }
    }

    for(;;);

    vector<vector<int>>
        freeUp(n, vector<int>(n)),
        freeDown(n, vector<int>(n)),
        freeLeft(n, vector<int>(n)),
        freeRight(n, vector<int>(n));

    vector<bool>canBeTopRow(n, false);

    for(int i=1;i<n;i++)
    {
        for(int j=1;j<m;j++)
        {
            if(wall[i-1][j]==wall[i][j])freeUp[i][j]=0;
            else
            {
                freeUp[i][j]=freeUp[i][j-1]+1;
                canBeTopRow[i]=true;
            }
        }
    }

    for(int i=0;i<m;i++)
    {
        for(int j=1;j<m;j++)
        {
            if(wall[i+1][j]==wall[i][j])freeDown[i][j]=0;
            else freeDown[i][j]=freeDown[i][j-1]+1;
        }
    }

    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            if(wall[i][j-1]==wall[i][j])freeLeft[i][j]=0;
            else freeLeft[i][j]=freeLeft[i-1][j]+1;
        }
    }

    for(int i=1;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(wall[i][j+1]==wall[i][j])freeRight[i][j]=0;
            else freeRight[i][j]=freeRight[i-1][j]+1;
        }
    }

#ifdef DEBUG
    {
        printf("up:\n");
        for(auto a : freeUp)
        {
            for(auto b : a)printf("%d ", b);
            printf("\n");
        }

        printf("down:\n");
        for(auto a : freeDown)
        {
            for(auto b : a)printf("%d ", b);
            printf("\n");
        }

        printf("left:\n");
        for(auto a : freeLeft)
        {
            for(auto b : a)printf("%d ", b);
            printf("\n");
        }

        printf("right:\n");
        for(auto a : freeRight)
        {
            for(auto b : a)printf("%d ", b);
            printf("\n");
        }
    }
#endif // DEBUG

    struct{int area=0, x1, y1, x2, y2;} answer;

    for(int x=1;x<m;x++)
    {
        if(!canBeTopRow[x])continue;
        for(int y=1;y<m;y++)
        {
            if(wall[x-1][y]==wall[x][y]||wall[x][y-1]==wall[x][y])continue;
            for(int w=1;freeUp[x][y+w-1]>=w;w++)
            {
                int minH=1;
                if(answer.area!=0)
                {
                    minH=answer.area/w+1;
                    if(x+minH>=m||freeRight[x+minH-1][y+w-1]<minH || freeLeft[x+minH-1][y]<minH)continue;
                }
                //printf("%d %d %d\n", x, y, w);
                for(int h=minH;freeLeft[x+h-1][y]>=h && freeRight[x+h-1][y+w-1]>=h;h++)
                {
                    if(freeDown[x+h-1][y+w-1]>=w)
                    {
                        //printf("%d %d %d %d\n", x, y, w, h);
                        if(w*h>answer.area)
                        {
                            answer.area=w*h;
                            answer.x1=x+1;
                            answer.y1=y+1;
                            answer.x2=x+h;
                            answer.y2=y+w;
                        }
                    }
                }
            }
        }
    }

    printf("%d %d %d %d %d\n", answer.area, answer.x1, answer.y1, answer.x2, answer.y2);

    /*
    }*/

}
/*
6
1 1 4 4 13 14
2 3 3 5 13 14
2 6 7 5 12 12
9 6 7 10 10 15
9 8 8 11 11 15
16 16 17 17 18 18
*/
