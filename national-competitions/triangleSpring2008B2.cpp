#include <bits/stdc++.h>
using namespace std;
using ldouble=long double;

struct point{ldouble x, y;};
istream& operator >> (istream &in, point &p){in>>p.x>>p.y; return in;}

bool common_coord(point a, point b){return a.x==b.x||a.y==b.y;}

struct triangle
{
    point a, b, c;

    mutable int _area2i=-1;
    int area2i()const
    {
        if(_area2i==-1)_area2i=abs(a.x*b.y + a.y*c.x + b.x*c.y - a.y*b.x - a.x*c.y - b.y*c.x);
        return _area2i;
    }
    ldouble area()const
    {
        return ((ldouble)area2i())/2.0l;
    }

    bool valid()const
    {
        return (common_coord(a, b)||common_coord(a, c)||common_coord(b, c))&&(area2i()&1)==0;
    }
};
istream& operator >> (istream &in, triangle &t){in>>t.a>>t.b>>t.c; return in;}

int n;
vector<triangle> triangles;

void read()
{
    cin>>n;
    triangles.assign(n, {});
    for(triangle &t : triangles)cin>>t;
}

void solve()
{
    //set<pair<int, int>> prev, next;
    list<pair<int, int>> prev;
    set<pair<int, int>> next;
    prev.emplace_back(0, 0);
    for(triangle &t : triangles)
    {
        if(!t.valid())continue;
        for(auto &p : prev)
        {
            int area=t.area2i();
            next.emplace(p.first, p.second+area);
            next.emplace(p.first+area, p.second);
        }
        prev={next.begin(), next.end()};
        next.clear();
    }

    pair<int, int> answer;
    int minDiff=10000000;
    for(auto &p : prev)
    {
        int diff=abs(p.first-p.second);
        if(diff<minDiff)
        {
            minDiff=diff;
            answer=p;
            if(diff==0)break;
        }
    }

    printf("%d %d\n", answer.first/2, answer.second/2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/*
6
8 4 9 4 8 1
1 0 0 0 4 4
9 8 3 5 1 5
8 3 4 5 1 3
8 3 4 5 1 3
9 4 3 2 8 5
*/
