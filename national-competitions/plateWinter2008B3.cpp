#include <bits/stdc++.h>
using namespace std;

using ldouble=long double;

ldouble a, b;

void enclose(ldouble &x, ldouble &y, ldouble accuracy)
{
    ldouble minDiff=numeric_limits<ldouble>::max(), newX, newY;

    for(ldouble i=x-20*accuracy;i<=x+20*accuracy;i+=accuracy)
    {
        if(i<0||i>100)continue;
        for(ldouble j=y-20*accuracy;j<=y+20*accuracy;j+=accuracy)
        {
            if(j<0||j>100)continue;
            ldouble diff=0;
            diff+=abs(hypotl(i, j)+hypotl(i, 100-j)-a);
            diff+=abs(hypotl(i, j)+hypotl(100-i, j)-b);
            if(diff<minDiff)
            {
                minDiff=diff;
                newX=i;
                newY=j;
            }
        }
    }

    x=newX;
    y=newY;
}

int main()
{
    cin>>a>>b;
    ldouble x=0, y=0;

    for(ldouble i=3;i>=-17;i--)
    {
        ldouble accuracy=pow(10, i);
        enclose(x, y, accuracy);
    }

    enclose(x, y, pow(10, -17)/2);

    printf("%.2lf\n", hypotl(x, y)+hypotl(100-x, y)+hypotl(x, 100-y)+hypotl(100-x, 100-y));
}
/*
130 167.08
*/
