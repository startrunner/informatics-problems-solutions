#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

int n;
vector<vector<bool>> rooms;
void read()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    rooms.resize(n, vector<bool>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            static char c;
            cin>>c;
            rooms[i][j]=(c=='1');
        }
    }
}

//35 pts.
int dfs(int x, int y, bool even);
//100 pts.
int dp()
{
    vector<vector<int>>  dp(n, vector<int>(n, numeric_limits<int>::max()-5));
    dp[0][0]=0;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(j<n-1)//Move to the right
            {
                if(rooms[i][j+1]==true)//can be jumped to only at odd times
                {
                    if(rooms[i][j]==false)dp[i][j+1]=min(dp[i][j+1], dp[i][j]+1);
                    else dp[i][j+1]=min(dp[i][j+1], dp [i][j]+2);
                }
                else//can be jumped to only at even times
                {
                    if(rooms[i][j]==true)dp[i][j+1]=min(dp[i][j+1], dp[i][j]+1);
                    else dp[i][j+1]=min(dp[i][j+1], dp[i][j]+2);
                }
            }
            if(i<n-1)//Move downwards
            {
                if(rooms[i+1][j]==true)//can be jumped to only at odd times
                {
                    if(rooms[i][j]==false)dp[i+1][j]=min(dp[i+1][j], dp[i][j]+1);
                    else dp[i+1][j]=min(dp[i+1][j], dp [i][j]+2);
                }
                else//can be jumped to only at even times
                {
                    if(rooms[i][j]==true)dp[i+1][j]=min(dp[i+1][j], dp[i][j]+1);
                    else dp[i+1][j]=min(dp[i+1][j], dp[i][j]+2);
                }
            }

        }
    }

    return dp.back().back();
}

int main()
{
    read();
    printf("%d\n", dp()+1);
}

inline int dfs(int x, int y, bool even)
{
    if(x==n||y==n)return numeric_limits<int>::max()-3;
    if(rooms[x][y]==even)return numeric_limits<int>::max()-3;
    if(x==n-1&&x==y)return 0;

    static vector<vector<int>> memz1(n, vector<int>(n, -1));
    static vector<vector<int>> memz2(n, vector<int>(n, -1));
    if(even==true&&memz1[x][y]!=-1)return memz1[x][y];
    if(even==false&&memz2[x][y]!=-1)return memz2[x][y];

    int rt=numeric_limits<int>::max()-3;

    rt=min(rt, dfs(x+1, y, !even)+1);
    rt=min(rt, dfs(x, y+1, !even)+1);
    rt=min(rt, dfs(x+1, y, even)+2);
    rt=min(rt, dfs(x, y+1, even)+2);

    if(even)memz1[x][y]=rt;
    else memz2[x][y]=rt;

    return rt;
}
#if true==false
4
0 1 1 1
0 1 0 0
1 0 1 1
1 0 1 1
#endif // true
