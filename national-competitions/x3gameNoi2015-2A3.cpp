#include <bits/stdc++.h>
using namespace std;

int main()
{
    /**
    one can't win if one of these conditions is fulfilled:
    -p is equal to q and is not a multiple of 3
    -one of the numbers is 3 times lesser than the other.
    **/

    for(int i=0;i<3;i++)
    {
        int64_t p, q;
        cin>>p>>q;

        if(p==q && p%3!=0)puts("0");
        else if(p*3==q || q*3==p)puts("0");
        else
        {
            if(p*3<q)printf("2 %lld\n", q-p*3);
            else if(q*3<p)printf("1 %lld\n", p-q*3);
            else if(p%3==0)printf("2 %lld\n", q-p/3);
            else if(q%3==0)printf("1 %lld\n", p-q/3);
            else if(p>q)printf("1 %lld\n", p-q);
            else if(q>p)printf("2 %lld\n", q-p);
            else puts("0");//this one should not happen
        }
    }
}
