#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cmath>
#define null nullptr
using namespace std;
using mdouble=long double;

const mdouble Pi=atan(1)*4;

mdouble p, q, r;

mdouble areaSq(mdouble n)
{
    if(n<=0)return numeric_limits<mdouble>::max();
    if(n>=numeric_limits<mdouble>::max()-1000)return numeric_limits<mdouble>::max();

    mdouble alpha=atan2(n, p)*180/Pi;
    mdouble m=tan((90-alpha)*Pi/180)*(p+q);

    mdouble rt=(n*n+p*p)*((p+q)*(p+q)+m*m);

    return rt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(null); cout.tie(null);
    cout<<setprecision(4)<<fixed;

    cin>>p>>q>>r;
    if(p!=r){cout<<"0\n"; return 0;}


    cout<<sqrt(areaSq(p))<<endl;
}
