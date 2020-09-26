#include <bits/stdc++.h>
using namespace std;

struct apple{int x, y;};

vector<apple> rotten;
int n, m, t;

void read()
{
    cin>>n>>m>>t;
    while(!cin.eof())
    {
        int x, y;
        cin>>x>>y;
        rotten.push_back({x, y});
    }
}
void solve()
{
    vector<vector<bool>> used(n+1, vector<bool>(m+1, false));
    queue<apple> bfs;

    int rCount=0;

    for(auto &i : rotten)
    {
        if(!used[i.x][i.y])
        {
            used[i.x][i.y]=true;
            bfs.push(i);
            rCount++;
        }
    }

    for(int tt=0;tt<t;tt++)
    {
        int len=bfs.size();
        for(int i=0;i<len;i++)
        {
            apple c=bfs.front();
            bfs.pop();

            vector<apple> next{{c.x, c.y+1}, {c.x, c.y-1}, {c.x+1, c.y}, {c.x-1, c.y}};
            for(auto &j : next)
            {
                if(j.x>0&&j.y>0&&j.x<=n&&j.y<=m&&(!used[j.x][j.y]))
                {
                    used[j.x][j.y]=true;
                    bfs.push(j);
                    rCount++;
                }
            }
        }
    }

    printf("%d\n", n*m-rCount);
}

int main()
{
    read();
    solve();
}
