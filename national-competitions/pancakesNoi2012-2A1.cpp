#include <bits/stdc++.h>
using namespace std;

int n;
uint64_t p;
vector<unsigned> stoves;

void read()
{
    cin>>p>>n;
    stoves.resize(n);
    for(auto &x : stoves)cin>>x;
}

uint64_t bake(int stove, uint64_t cakesAt, uint64_t &time)
{
    uint64_t cakes=0;
    time = cakesAt * stoves[stove];

    for(int i=0;i<n;i++)
    {
        if(i==stove)cakes+=cakesAt;
        else cakes+=time/stoves[i];
    }

    return cakes;
}

uint64_t best_bake(int mainStove, uint64_t from, uint64_t to)//returns time
{
    uint64_t fromTime, fromBaked=bake(mainStove, from, fromTime);
    if(fromBaked>=p)return fromTime;
    else if(from==to)return UINT64_MAX;

    uint64_t mid = (from+to)/2;
    uint64_t midTime, midBaked=bake(mainStove, mid, midTime);
    if(midBaked<p)return best_bake(mainStove, mid+1, to);
    else return best_bake(mainStove, from, mid);
}

uint64_t solve()
{
    uint64_t minTime = UINT64_MAX;

    for(int stove=0;stove<n;stove++)
    {
        minTime=min(minTime, best_bake(stove, 0, p));
    }

    return minTime;
}

uint64_t solve_slow()
{
    uint64_t minTime=UINT64_MAX;

    for(int stove=0;stove<n;stove++)
    {
        for(uint64_t cakes=0;cakes<p;cakes++)
        {
            uint64_t time, total=bake(stove, cakes, time);

            printf(
                "baking %lld cakes at stove %d will yield %lld total cakes for %lld time\n",
                cakes, stove, total, time
            );

            if(total>=p)minTime=min(minTime, time);
        }
    }

    return minTime;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    printf("%lld\n", solve());
}
/**
3 2
50 70
**/
