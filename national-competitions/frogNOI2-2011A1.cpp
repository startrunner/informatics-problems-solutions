#include <iostream>
#include <vector>
#include <tuple>
#include <cstdio>
#include <cmath>
using namespace std;

struct point
{
    int x, y;

    point(int x, int y):
        x(x), y(y){};

    point():
        point(0, 0){}
};

int n, n2;
vector<point> points;

void read()
{
    cin>>n;
    n2=n*2;
    points.resize(n2);
    for(point &p : points)cin>>p.x>>p.y;
}

uint64_t jumps_between(point a, point b)
{
    const int Impossible = 100000000;
    int a2 = b.x + b.y - a.x - a.y;
    int valA=a2/2;
    int valB=a.y + valA - b.y;
    if(a2%2!=0)return Impossible;
    int result =  abs(valA) + abs(valB);
    //printf("(%d %d) -> (%d %d): |%d| + |%d| = %d\n", a, b, valA, valB, result);
    return result;
}

int jumps_between(int i, int j)
{
    return jumps_between(points[i], points[j]);
}

uint64_t currentLen = 0;
uint64_t minLen = INT64_MAX;
int8_t currentCount = 1;
bool used[12];

void go(int8_t current)
{
    //printf("c: %d   cl: %d   cc: %d   ml: %d\n", (int)current, currentLen, currentCount, minLen);

    if(currentCount == n)
    {
        minLen = min(minLen, currentLen);
        return;
    }

    for(uint8_t next=0;next<n2;next++)
    {
        if(used[next])continue;

        used[next]=true;
        currentCount++;
        currentLen += jumps_between(current, next);

        go(next);

        used[next]=false;
        currentCount--;
        currentLen -= jumps_between(current, next);
    }
}


void solve()
{
    for(int8_t i=0;i<n2;i++)
    {
        used[i]=true;
        currentLen = jumps_between(points[i], {0, 0});
        go(i);
        used[i]=false;
    }

    printf("%llu\n", minLen);
}

int main()
{
    read();
    solve();
}
/**
2
1 1
3 5
4 6
8 2
**/
