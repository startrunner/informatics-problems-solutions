#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int from, to, price;
    edge(int from, int to, int price)
    {
        this->from=from;
        this->to=to;
        this->price=price;
    }
    edge(){}

    bool operator < (const edge &e)const
    {
        return price<e.price;
    }

    static bool lex_cmp(const edge &a, const edge &b)
    {
        return a.from<b.from||(a.from==b.from&&a.to<b.to);
    }
};

int n, m;
vector<edge> edges;
vector<int> priceOf;

void read()
{
    cin>>n>>m;
    priceOf.resize(n+1);
    for(int i=1;i<=n;i++)cin>>priceOf[i];
    for(int i=0;i<m;i++)
    {
        int a, b, l;
        cin>>a>>b>>l;
        if(a>b)swap(a, b);
        l=(priceOf[a]+priceOf[b])*(l/2)+(l%2)*priceOf[a];
        edges.emplace_back(a, b, l);
    }
}


vector<int> unionOf;
vector<edge> mstEdges;

void unify(int a, int b)
{
    int x=unionOf[a];
    for(int &i : unionOf)if(i==x)i=unionOf[b];
}

void make_mst()
{
    for(int i=0;i<=n;i++)unionOf.push_back(i);

    sort(edges.begin(), edges.end());
    for(edge &e : edges)
    {
        if(unionOf[e.from]!=unionOf[e.to])
        {
            unify(e.to, e.from);
            mstEdges.push_back(e);
        }
    }
}

void solve()
{
    make_mst();
    int price=0;
    for(edge &e : mstEdges)price+=e.price;
    printf("%d\n", price);
    sort(mstEdges.begin(), mstEdges.end(), edge::lex_cmp);
    for(edge &e : mstEdges)
    {
        printf("%d %d\n", e.from, e.to);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
/*
6 10
8 5 15 3 9 6
1 2 2
1 5 10
2 3 5
2 5 4
2 6 8
3 4 11
3 5 7
4 5 3
4 6 4
5 6 6
*/
