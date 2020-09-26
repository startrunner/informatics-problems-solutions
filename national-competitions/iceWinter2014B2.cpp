#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

int n;
int frozenCount=0;
bool frozen[5002][5002];
int meltTime[5002][5002];

void read()
{
    cin>>n;
    char s[5001];
    for(int i=1;i<=n;i++)
    {
        cin>>(s+1);
        for(int j=1;j<=n;j++)
        {
            if(s[j]=='1')
            {
                frozen[i][j]=true;
                frozenCount++;
            }
        }
    }
}

inline bool try_melt(int x, int y, int t)
{
    if(!frozen[x][y])return false;
    register short rt=0;
    if(!frozen[x+1][y]&&meltTime[x+1][y]<t)rt++;
    if(!frozen[x-1][y]&&meltTime[x-1][y]<t)rt++;
    if(!frozen[x][y+1]&&meltTime[x][y+1]<t)rt++;
    if(!frozen[x][y-1]&&meltTime[x][y-1]<t)rt++;
    if(rt>1)
    {
        frozen[x][y]=false;
        meltTime[x][y]=t;
        frozenCount--;
        return true;
    }
    return false;
}

inline bool should_add(int x, int y, int t)
{
    return try_melt(x, y, t)&&(frozen[x+1][y]||frozen[x-1][y]||frozen[x][y+1]||frozen[x][y-1]);
}

void solve()
{
    int t;
    queue<pair<int, int>> changed;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(!frozen[i][j]&&(frozen[i+1][j]||frozen[i-1][j]||frozen[i][j+1]||frozen[i][j-1]))
            {
                changed.emplace(i, j);
            }
        }
    }

    for(t=1;frozenCount!=0;t++)
    {
        int len=changed.size();
        for(int i=0;i<len;i++)
        {
            int x=changed.front().first, y=changed.front().second;
            changed.pop();

            if(should_add(x+1, y, t))changed.emplace(x+1, y);
            if(should_add(x-1, y, t))changed.emplace(x-1, y);
            if(should_add(x, y+1, t))changed.emplace(x, y+1);
            if(should_add(x, y-1, t))changed.emplace(x, y-1);
        }
    }
    printf("%d\n", t-1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/*
8
00000000
01111010
01011010
01010110
01110010
01110110
00001110
00000000
*/
