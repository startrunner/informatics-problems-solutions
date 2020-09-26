#include <bits/stdc++.h>
using namespace std;

struct mine
{
    int x, y;

    mine(int x, int y)
    {
        this->x=x;
        this->y=y;
    }

    bool operator < (const mine &m)const
    {
        return x<m.x || (x==m.x && y<m.y);
    }
};

const double PI=atan(1.0)*4.0;

int n, r;
double avgX=0, avgY=0;
vector<mine> mines;

double clockwise_angle(double x, double y)
{
    double rt=atan2(x, y);
    if(rt<0)rt+=2*PI;
    return rt*180/PI;
}

bool sort_clockwise(mine a, mine b)
{
    double clockA=clockwise_angle(a.x-avgX, a.y-avgY);
    double clockB=clockwise_angle(b.x-avgX, b.y-avgY);
    return clockA<clockB;
}

double dist(mine a, mine b)
{
    return hypot(a.x-b.x, a.y-b.y);
}

bool right_turn(mine a, mine b, mine c)
{
    double a1=clockwise_angle(b.x-a.x, b.y-a.y);
    double a2=clockwise_angle(c.x-b.x, c.y-b.y);

    double tt=a1+180+720-a2;
    while(tt>=360)tt-=360;
    return tt<=180;
}

void read()
{
    cin>>n>>r;
    set<mine> mineSet;
    for(int i=0, x, y;i<n;i++)
    {
        cin>>x>>y;
        mineSet.emplace(x, y);
    }

    mines={mineSet.begin(), mineSet.end()};

    n=mines.size();
    //for(auto &x : mines)
    for(int i=0;i<n;i++)
    {
        auto &x=::mines[i];

        avgX+=x.x;
        avgY+=x.y;
    }
    avgX/=n;
    avgY/=n;
}

void solve()
{
    int leftmost=0;
    sort(mines.begin(), mines.end(), sort_clockwise);
    for(int i=1;i<n;i++)if(mines[i]<mines[leftmost])leftmost=i;

    //printf("lm: %d\n", leftmost);

    //for(mine x : mines)
    {
        //printf(" %d %d\n", x.x, x.y);
    }

    //printf("%.2f %.2f\n", (float)avgX, (float)avgY);

    vector<int> hull;

    for(int i=leftmost;;)
    {
        mine current=mines[i];

        while(hull.size()>1 && !right_turn(mines[hull[hull.size()-2]], mines[hull.back()], current))hull.pop_back();
        hull.push_back(i);

        i=(i+1)%n;
        if(hull.back()==leftmost && hull.size()>1) break;
    }

    double answer=2.0*PI*r;
    for(int i=1;i<hull.size();i++)
    {
        mine &a=mines[hull[i]];
        mine &b=mines[hull[i-1]];
        answer+=dist(a, b);
    }

    //puts("hull: ");
    //for(int x : hull)printf("%d at %d %d\n", x, mines[x].x, mines[x].y);

    printf("%.3f\n", answer);
}

int main()
{
    /*
    cout<<clockwise_angle(0, 1)<<endl;
    cout<<clockwise_angle(1, 1)<<endl;
    cout<<clockwise_angle(1, 0)<<endl;
    cout<<clockwise_angle(1, -1)<<endl;
    cout<<clockwise_angle(0, -1)<<endl;
    cout<<clockwise_angle(-1, -1)<<endl;
    cout<<clockwise_angle(-1, 0)<<endl;
    cout<<clockwise_angle(-1, 1)<<endl;
    cout<<clockwise_angle(0, 1)<<endl;
    */

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/**
8 1
1 4
3 2
7 9
5 4
9 5
6 7
9 1
11 8
*/
