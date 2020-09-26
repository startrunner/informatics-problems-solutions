#include <bits/stdc++.h>
using namespace std;

const int Q=1000000007;
int n, c1, c2, c3, sumAll=0, biggest=0;
vector<int> items;

void read()
{
    cin>>n>>c1>>c2>>c3;
    items.resize(n);
    for(int &i : items)
    {
        cin>>i;
        sumAll+=i;
        biggest=max(biggest, i);
    }
}

void solve()
{
    vector<vector<int>> dp(c1+biggest+1, vector<int>(c2+biggest+1, 0));
    dp[0][0]=1;
    for(int it : items)
    {
        for(int i=c1;i>=0;i--)
        {
            for(int j=c2;j>=0;j--)
            {
                dp[i+it][j]=(dp[i+it][j]+dp[i][j])%Q;
                dp[i][j+it]=(dp[i][j+it]+dp[i][j])%Q;
            }
        }
    }

    int answer=0;
    for(int i=0;i<=c1;i++)
    {
        for(int j=0;j<=c2;j++)
        {
            int k=sumAll-i-j;
            if(k<0||k>c3)continue;
            answer=(answer+dp[i][j])%Q;
        }
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
5 3 7 4
1 7 2 1 3

23 42 177 113
1 2 3 4 5 6 7 8 9 10 11 12 13
14 15 16 17 18 19 20 21 22 23
*/
