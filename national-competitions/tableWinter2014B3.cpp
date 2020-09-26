#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int n, m;

void read(){cin>>n>>m;}

void solve()
{
    vector<int> dp(n/2+1, 0);
    dp[0/2]=dp[2/2]=1;
    for(int i=4;i<=n;i+=2)
    {
        for(int j=2;j<=i;j+=2)
        {
            int l=j-2;
            int r=i-l-2;
            dp[i/2]+=dp[l/2]*dp[r/2];
            dp[i/2]%=m;
        }
    }
    printf("%d\n", dp[n/2]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
