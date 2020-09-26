#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> gr;

read()
{
    cin>>n>>m;
    gr.resize(n+m+2);
    for(int i=1;i<=m;i++)
    {
        int a, b;
        cin>>a>>b;
        gr[n+i].push_back(a);
        gr[n+i].push_back(b);
        gr[a].push_back(n+i);
        gr[b].push_back(n+i);
    }
}

vector<int> bridge_points(const vector<vector<int>> &gr)
{
    int start, n=gr.size();

    set<int> rt;
    vector<bool> used(n, false);
    vector<int> parentOf(n, -1), depthOf(n), lowReach(n);

    function<void(int, int)> go=[&](int current, int depth)
    {
        int children=0;
        used[current]=true;
        depthOf[current]=depth;
        lowReach[current]=depth;

        for(int i : gr[current])
        {
            if(!used[i])
            {
                parentOf[i]=current;
                children++;
                go(i, depth+1);
                lowReach[current]=min(lowReach[current], lowReach[i]);
            }
            else if(parentOf[current]!=i)lowReach[current]=min(lowReach[current], depthOf[i]);

            if(current!=start)if(lowReach[i]>=depthOf[current])rt.insert(current);
            else if(children>1)rt.insert(current);
        }
    };

    for(start=0;start<n;start++)if(!used[start])go(start, 0);

    return std::move(vector<int>(rt.begin(), rt.end()));
}

solve()
{
    int answer=0;
    for(int i : bridge_points(gr))if(i>n)answer++;
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
7 8
5 1
1 2
2 6
3 4
4 7
6 7
2 5
3 6

16 20
1 2
2 3
3 4
1 4
4 5
4 6
4 7
7 8
8 9
8 12
12 11
11 10
9 10
6 5
7 5
8 13
13 14
13 15
15 8
14 16

10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
*/
