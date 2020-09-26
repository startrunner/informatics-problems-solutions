#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<pair<int, int>>> gr;

vector<int> lens_to(int from)
{
    struct dijkstra
    {
        int to, len;
        dijkstra(int to, int len) {this->to=to; this->len=len;};
        bool operator < (const dijkstra &that)const
        {
            return len<that.len || (len==that.len && to<that.to);
        }
    };

    set<dijkstra> progress;
    vector<int> minLen(n+1, INT_MAX);
    minLen[from]=0;
    progress.emplace(from, 0);
    while(!progress.empty())
    {
        dijkstra current=*progress.begin();
        progress.erase(progress.begin());

        for(auto &i : gr[current.to])
        {
            dijkstra next(i.first, i.second+current.len);
            if(next.len<minLen[next.to])
            {
                progress.insert(next);
                minLen[next.to]=next.len;
            }
        }
    }

    return std::move(minLen);
}

void read()
{
    cin>>n;
    gr.resize(n+1);
    for(int i=1;i<n;i++)
    {
        int a, b, l;
        cin>>a>>b>>l;
        gr[a].emplace_back(b, l);
        gr[b].emplace_back(a, l);
    }
}

void solve()
{
    vector<int> lensFromOne=lens_to(1);
    int farthestFromOne=1;
    for(int i=2;i<lensFromOne.size();i++)
    {
        if(lensFromOne[i]>lensFromOne[farthestFromOne])
        {
            farthestFromOne=i;
        }
    }

    int answer=0;
    vector<int> farthestFromFarthest=lens_to(farthestFromOne);
    for(int i=1;i<farthestFromFarthest.size();i++)
    {
        answer=max(answer, farthestFromFarthest[i]);
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
