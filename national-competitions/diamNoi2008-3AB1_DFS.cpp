#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<pair<int, int>>> gr;
vector<vector<int>> linkIndices;

void read()
{
    cin>>n;
    gr.resize(n+1);
    linkIndices.resize(n+1, vector<int>(n+1, -1));
    for(int i=1;i<n;i++)
    {
        int a, b, len;
        cin>>a>>b>>len;
        linkIndices[a][b]=gr[a].size();
        linkIndices[b][a]=gr[b].size();
        gr[a].emplace_back(b, len);
        gr[b].emplace_back(a, len);
    }
}

int memz[1001][1001];
int max_dist(int current, int previous)
{
    if(gr[current].size()==1 && gr[current][0].first==previous){return 0;}

    if(memz[current][previous]!=0){return memz[current][previous];}

    int &maxDist=memz[current][previous];
    for(auto next : gr[current])
    {
        if(next.first==previous){continue;}
        maxDist = max(maxDist, max_dist(next.first, current)+next.second);
    }
    return maxDist;
}

void solve()
{
    int answer=-1;
    for(int i=1;i<=n;i++)
    {
        answer=max(answer, max_dist(i, -1));
    }
    printf("%d\n", answer);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/*
10
4 5 5
4 3 2
4 2 1
5 6 4
5 1 0
5 7 4
3 8 4
3 9 3
3 10 3
*/
