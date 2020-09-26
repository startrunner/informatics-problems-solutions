#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> gr;

void read()
{
    cin>>n>>m;
    gr.resize(n+1);
    for(int i=0;i<m;i++)
    {
        int a, b, len;
        cin>>a>>b>>len;
        gr[b].emplace_back(a, len);
    }
}

void solve()
{
    for(int i=1;i<=n;i++)gr[0].emplace_back(i, 0);

    vector<int> lenTo(n+1, INT_MAX);
    lenTo[0]=0;

    for(int i=0;i<=n;i++)
    for(int from=0;from<=n;from++)
    {
        for(auto &edge : gr[from])
        {
            if(lenTo[from]+edge.second<lenTo[edge.first])
            {
                lenTo[edge.first]=lenTo[from]+edge.second;
            }
        }
    }

    int minLen=INT_MAX;
    for(int x : lenTo)minLen=min(minLen, x);
    for(int i=1;i<=n;i++)printf("%d ", lenTo[i]-minLen);
    puts("");
}

int main()
{
    read();
    solve();
}
/*
5 8
1 2 0
1 5 -1
2 5 1
3 1 5
4 1 4
4 3 -1
5 3 -3
5 4 -3
*/
