#include <bits/stdc++.h>
using namespace std;

struct point
{
    int x, y;

    double dist_to(const point &to) const
    {
        int a = x - to.x;
        int b = y - to.y;
        return sqrt(a*a + b*b);
    }
};

struct circle
{
    point center;
    int radius;
};

int n, m, q;
vector<circle> circles;
vector<point> points;
vector<int> queries;

void read()
{
    cin>>n>>m>>q;

    circles.resize(n);
    points.resize(m);
    queries.resize(q);

    for(auto &x : circles)cin>>x.center.x>>x.center.y>>x.radius;
    for(auto &x : points)cin>>x.x>>x.y;
    for(auto &x : queries)cin>>x;
}

vector<vector<double>> build_distances()
{
    vector<vector<double>> distancesOf(m, vector<double>(n));

    for(int i=0;i<m;i++)
    {
        point &p = points[i];
        for(int j=0;j<n;j++)
        {
            circle &c = circles[j];
            distancesOf[i][j] = p.dist_to(c.center) + c.radius;
        }

        sort(distancesOf[i].begin(), distancesOf[i].end());
    }

    return move(distancesOf);
}

int solve(int radius, const vector<vector<double>> &distancesOf)
{
    int result = 0;

    for(int pointI=0;pointI<m;pointI++)
    {
        const auto &dists = distancesOf[pointI];
        result += upper_bound(dists.begin(), dists.end(), radius) - dists.begin();
    }

    return result;
}

void solve()
{
    int answer=0, last = 1;
    vector<vector<double>> distancesOf = build_distances();

    for(int query : queries)
    {
        int radius = last%2==1 ? query : query*2;
        int current=solve(radius, distancesOf);
        answer += (last = current);
    }
    printf("%d\n", answer);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}

/**
4 1 3
2 2 1
3 5 2
6 2 3
8 8 1
4 4
4 3 3
**/
