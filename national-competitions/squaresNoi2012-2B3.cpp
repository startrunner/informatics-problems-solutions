#include <bits/stdc++.h>
using namespace std;

int s;
vector<int> squares;

void read(){cin>>s;}

void solve()
{
    int answer=0;
    vector<bool> used(s+1, false);
    for(int i=0;i*i<=s;i++)squares.push_back(i*i);
    for(int i=0;i<squares.size();i++)
    {
        for(int j=i;j<squares.size();j++)
        {
            int cs=squares[i]+squares[j];
            if(cs<=s&&!used[cs])
            {
                used[cs]=true;
                answer++;
            }
        }
    }
    //for(int i=0;i<=s;i++)if(used[i])printf("%d ", i);
    //puts("");
    printf("%d\n", answer-1);
}

int main()
{
    read();
    solve();
}
