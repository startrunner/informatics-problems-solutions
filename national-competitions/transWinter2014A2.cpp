#include <bits/stdc++.h>
using namespace std;

int gaus(int x)
{
    return (x+1)*(x/2) + (x%2)*(x/2+1);
}

void solve(int n, int k)
{
    int sumAll=gaus(n);
    if(sumAll%k!=0)
    {
        puts("NO");
        return;
    }
    int perOne=sumAll/k;
    if(n>perOne)
    {
        puts("NO");
        return;
    }

    if(n==perOne)
    {
        puts("1");
        printf("%d\n", n);
        for(int i=1;i<n/2+n%2;i++)
        {
            puts("2");
            printf("%d %d\n", i, perOne-i);
        }
    }

    if(n==perOne-1)
    {
        for(int i=1;i<n/2;i++)
        {
            puts("2");
            printf("%d %d\n", i, perOne-i);
        }
    }

    return;
}

int main()
{
    int n, k;
    cin>>n>>k;
    solve(n, k);

    //cout<<allCount<<endl;
    //cout<<noCount<<endl;
    //cout<<yesCount<<endl;
    //solve();
}
