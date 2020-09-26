#include <bits/stdc++.h>
using namespace std;

string word;

bool is_palindrome(int from, int to)
{
    if(from==to)return true;
    if(from+1==to)return word[from]==word[to];
    if(word[from]!=word[to])return false;

    static vector<vector<int>> memz(word.size(), vector<int>(word.size(), -1));

    if(memz[from][to]==-1)memz[from][to]=(int)is_palindrome(from+1, to-1);

    return memz[from][to]==1;
}

void solve()
{
    if(is_palindrome(0, word.size()-1))
    {
        puts("0");
        return;
    }

    vector<int> dp(word.size(), INT_MAX);
    for(int i=word.size()-1;i>=0;i--)
    {
        if(is_palindrome(i, word.size()-1))dp[i]=0;

        for(int split=i;split<word.size()-1;split++)
        {
            if(is_palindrome(i, split))dp[i]=min(dp[i], dp[split+1]+1);
        }
    }

    printf("%d\n", dp[0]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>word;
    solve();
}
