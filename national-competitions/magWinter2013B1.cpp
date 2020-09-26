#include <bits/stdc++.h>
using namespace std;

struct factory
{
    int wait, one, done;

    int64_t total_t()const
    {
        return int64_t(one)*done+wait;
    }

    bool operator < (const factory &that)const
    {
        return total_t()+one>that.total_t()+that.one;
    }

    factory(int64_t wait, int64_t one)
    {
        this->wait=wait;
        this->one=one;
        this->done=0;
    }
};

int n, p;
vector<factory> factories;

void read()
{
    cin>>n>>p;
    for(int i=0;i<n;i++)
    {
        int wait, one;
        cin>>one>>wait;
        factories.emplace_back(wait, one);
    }
}

void solve()
{
    int64_t answer=0;
    priority_queue<factory> q;

    for(const factory &i : factories)q.push(i);

    for(int i=0;i<p;i++)
    {
        factory best=q.top();
        q.pop();

        best.done++;
        answer=max(answer, best.total_t());
        q.push(best);
    }

    printf("%lld\n", answer);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}

/*
3 10
5 10
7 5
8 1
*/
