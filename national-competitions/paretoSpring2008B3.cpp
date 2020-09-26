#include <bits/stdc++.h>
using namespace std;

struct node
{
    node *a, *b;
    pair<int, int> range;
    int maxVal=INT_MIN;

    node(register const pair<int, int> &range)
    {
        this->range=range;
        if(range.first!=range.second)
        {
            int split=(range.first+range.second)/2;
            a=new node({range.first, split});
            b=new node({split+1, range.second});
        }
    }

    int size(){return range.second-range.first+1;}

    void set(int index, int value)
    {
        if(index>=range.first && index<=range.second)
        {
            if(value>maxVal)maxVal=value;
            if(size()>1)
            {
                a->set(index, value);
                b->set(index, value);
            }
        }
    }

    int rmq(const pair<int, int> &range)
    {
        register int rt;
        if(this->range.first>=range.first && this->range.second<=range.second)rt=maxVal;
        else if(this->range.second<range.first || this->range.first>range.second)rt=INT_MIN;
        else rt=max(a->rmq(range), b->rmq(range));
        return rt;
    }

    void reset()
    {
        maxVal=INT_MIN;
        if(size()>1)
        {
            a->reset();
            b->reset();
        }
    }

    ~node()
    {
        if(size()>1)
        {
            delete a;
            delete b;
        }
    }
};

struct point
{
    int x, y;
    bool operator < (const point &p)const
    {
        return x<p.x||(x==p.x&&y<p.y);
    }
};

int n, maxX=INT_MIN, maxY=INT_MIN;
vector<point> points;

void read()
{
    cin>>n;
    points.resize(n);
    for(point &p : points)
    {
        cin>>p.x>>p.y;
        maxX=max(maxX, p.x);
        maxY=max(maxY, p.y);
    }
}

void solve()
{
    node x({1, maxX}), y({1, maxY});
    for(point &p : points)
    {
        x.set(p.x, p.y);
        y.set(p.y, p.x);
    }

    set<point> optimal;
    for(point &p : points)
    {
        if(x.rmq({p.x, p.x})>p.y || x.rmq({p.x+1, maxX})>=p.y){}
        else if(y.rmq({p.y, p.y})>p.x || y.rmq({p.y+1, maxY})>=p.x){}
        else optimal.insert(p);
    }

    x.reset();
    y.reset();
    vector<point> nonOptimal;
    for(point &p : points)
    {
        if(optimal.find(p)!=optimal.end())continue;
        nonOptimal.push_back(p);
        x.set(p.x, p.y);
        y.set(p.y, p.x);
    }

    int subCount=0;
    for(point &p : nonOptimal)
    {
        if(x.rmq({p.x, p.x})>p.y || x.rmq({p.x+1, maxX})>=p.y){}
        else if(y.rmq({p.y, p.y})>p.x || y.rmq({p.y+1, maxY})>=p.x){}
        else subCount++;
    }

    printf("%d %d\n", optimal.size(), subCount);
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
1 1
2 1
3 1
1 2
2 2
1 3
*/
