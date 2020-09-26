#include <bits/stdc++.h>
using namespace std;

using ldouble = long double;

struct circle
{
    ldouble x, y, r;
};

istream& operator >> (istream &in, circle &c){in>>c.x>>c.y>>c.r; return in;}

int n;
vector<circle> circles;

void read()
{
    cin>>n;
    circles.resize(n);
    for(circle &c : circles)cin>>c;
}

void solve()
{
    vector<vector<int>> gr(n);
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            circle &a=circles[i], &b=circles[j];
            ldouble d=hypotl(a.x-b.x, a.y-b.y);
            if(d==0&&a.r==b.r)continue;
            if(d>=a.r+b.r)continue;
            if(d+a.r<=b.r)continue;
            if(d+b.r<=a.r)continue;
            gr[i].push_back(j);
            gr[j].push_back(i);
        }
    }

    int answer=0;
    bitset<1001> used;
    queue<int> q;
    q.push(0);
    used[0]=true;
    for(answer=0;!used[n-1]&&!q.empty();answer++)
    {
        int len=q.size();
        for(int i=0;i<len;i++)
        {
            int current=q.front();
            q.pop();
            for(int next : gr[current])
            {
                if(!used[next])
                {
                    used[next]=true;
                    q.push(next);
                }
            }
        }
    }
    if(used[n-1])printf("%d\n", answer);
    else puts("-1");
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/*
3
0 0 1
4 0 4
1 0 2
*/

