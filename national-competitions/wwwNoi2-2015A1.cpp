#include <bits/stdc++.h>
using namespace std;

int r, d, n;
const long double PI=atan(1)*4;

void read()
{
    cin>>r>>d>>n;
}

void solve()
{
    long double angleUnit=360.0/n;
    long double maxAngle=2*(asin((d/2.0)/r)*180/PI);
    int64_t conn=maxAngle/angleUnit;
    if(2*r<=d)conn=n-1;
    int64_t answer=n*conn;
    if(2*r<=d)answer/=2;
    printf("%lld\n", answer);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
