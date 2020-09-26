#include <bits/stdc++.h>
using namespace std;

int getnextint()
{
    static int integer=0;
    return integer++;
}

int main()
{
    int p, m;
    cin>>p>>m;

    vector<int*> vars(p);
    vector<int*> allocated;
    allocated.reserve(500000);

    for(int i=0;i<p;i++)
    {
        vars[i]=new int(getnextint());
        allocated.push_back(vars[i]);
    }

    for(int i=0;i<m;i++)
    {
        char c; int x, y;
        cin>>c>>x;
        switch(c)
        {
        case 'R':
            cin>>y;
            vars[x]=vars[y];
            break;
        case 'C':
            cin>>y;
            *vars[x]=*vars[y];
            break;
        case 'N':
            vars[x]=new int(getnextint());
            allocated.push_back(vars[x]);
            break;
        }
    }


    for(int i=0;i<p;i++)printf("%d ", *vars[i]);
    puts("");

    for(int *i : allocated)delete i;
}
/*
7 5
R 1 0
C 2 0
C 0 3
R 4 5
N 5
*/
