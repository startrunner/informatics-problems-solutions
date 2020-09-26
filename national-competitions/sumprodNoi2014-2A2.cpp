#include <bits/stdc++.h>
using namespace std;

struct narray
{
    int values[19];

    narray()
    {
        for(int &i : values)i=INT_MIN;
    }

    int& operator [](int index)
    {
        return values[9+index];
    }
};

int n, b, c, d;
vector<int> a;

void read()
{
    cin>>n>>b>>c>>d;
    a.resize(n);
    for(int &i : a)cin>>i;
}

void solve()
{
    vector<narray> dp(n);
    narray prev, curr;

    for(int i=b;i<=c;i++)prev[i]=a[0]*i;

    for(int i=1;i<n;i++)
    {
        for(int cj=b;cj<=c;cj++)
        {
            int lower=max(b, cj-d);
            int upper=min(c, cj+d);
            for(int pj=lower;pj<=upper;pj++)
            {
                curr[cj]=max(curr[cj], prev[pj]+cj*a[i]);
            }
        }
        prev=curr;
        curr=narray();
    }


    int answer=INT_MIN;
    for(int i=b;i<=c;i++)answer=max(answer, prev[i]);
    printf("%d\n", answer);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
