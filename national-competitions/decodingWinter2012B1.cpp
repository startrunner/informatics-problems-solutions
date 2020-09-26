#include <bits/stdc++.h>
using namespace std;

vector<int> n;

void read()
{
    string s;
    cin>>s;
    n.push_back(0);
    for(char c : s)n.push_back(c-'0');
}

void solve()
{
    vector<uint64_t> dp(n.size(), 0);
    dp[0]=1;
    for(int i=1;i<n.size();i++)
    {
        if(n[i]!=0)dp[i]+=dp[i-1];
        if(n[i-1]!=0&&n[i-1]*10+n[i]<=26)dp[i]+=dp[i-2];
    }
    printf("%llu\n", dp.back());
}

int main()
{
    read();
    solve();
}
