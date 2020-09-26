#include <bits/stdc++.h>
using namespace std;

int dumb_solve(int n)
{
    int rt=0;

    for(int diff=1;diff<n*2;diff++)
    {
        //printf("diff: %d\n", diff);
        vector<bool> used(n*2+1, false);
        int usedCount=0;
        for(int i=1;i+diff<=n*2;i++)
        {
            if(!used[i] && !used[i+diff])
            {
                //printf("%d %d\n", i, i+diff);
                used[i]=true;
                used[i+diff]=true;
                usedCount+=2;
            }
        }
        //printf("uc: %d\n", usedCount);
        //puts("");
        if(usedCount==n*2)rt++;
    }

    return rt;
}

int smart_solve(int n)
{
    int rt=0;
    for(int i=1;i<=n;i++)if(n%i==0)rt++;
    return rt;
}

int main()
{
    //for(int i=2;i<=64;i++)
    {
        //printf("%2d %d %d\n", i, dumb_solve(i), smart_solve(i));
    }

    int n;
    cin>>n;
    printf("%d\n", smart_solve(n));
}
