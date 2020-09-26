#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <limits>
#include <tuple>
#define this (*this)
#define null nullptr
using namespace std;

using uint64=uint_fast64_t;
#define int int_fast32_t
const uint64 Infinity=numeric_limits<uint64>::max();

int n, k;
uint64* cells;

void read()
{
    scanf("%d %d", &n, &k);
    uint64 f, a, b, m;
    scanf("%lld %lld %lld %lld", &f, &a, &b, &m);
    cells=(uint64*)malloc(sizeof(decltype(cells[0]))*n);
    cells[0]=f;
    for(int i=1;i<n;i++)cells[i]=(cells[i-1]*a+b)%m;
}

inline bool canSplit(pair<int, int> a)
{
    return a.first!=a.second;
}

inline pair<pair<int, int>, pair<int, int>> split(pair<int, int> range)
{
    int middle=range.first+(range.second-range.first)/2;
    return {{range.first, middle}, {middle+1, range.second}};
}

inline int common(pair<int, int> a, pair<int, int> b)
{
    if(a.first>b.first)return common(b, a);

    if(b.first>a.second)return 0;
    if(b.second<=a.second)return b.second-b.first+1;
    if(b.second>a.second)return a.second-b.first+1;
}

struct rmqNode
{
    using node=rmqNode;

    node* children=null;
    uint64 minValue=Infinity;
    pair<int, int> range;

    inline node& left() {return children[0];}
    inline node& right(){return children[1];}

    inline rmqNode(pair<int, int> range)
    {
        this.range=range;
        if(canSplit(range))
        {
            children=(node*)malloc(sizeof(node)*2);
            auto spl=split(range);
            left() =node(spl.first);
            right()=node(spl.second);
        }
    }

    inline void set(int index, uint64 value)
    {
        if(index>=range.first&&index<=range.second)
        {
            if(children!=null)
            {
                left().set(index, value);
                right().set(index, value);
                //minValue=min(left().minValue, right().minValue);
            }
            minValue=min(minValue, value);
        }
    }

    inline uint64 minQ(pair<int, int> range)
    {
        if(this.range.first>=range.first&&this.range.second<=range.second)
        {
            return this.minValue;
        }
        if(range.second<this.range.first || range.first>this.range.second)return Infinity;
        return min(left().minQ(range), right().minQ(range));
    }
};

int main()
{
    read();
    if(k>=n)
    {
        puts("0");
        return 0;
    }
    vector<uint64> dp(n, Infinity);

    rmqNode tree({-1, n});
    tree.set(n, 0);

    for(int i=dp.size()-1;i>=0;i--)
    {
        dp[i]=tree.minQ({i+1, i+k})+cells[i];
        tree.set(i, dp[i]);
    }

    uint64 answer=Infinity;
    for(int i=0;i<k;i++)answer=min(answer, dp[i]);
    printf("%lld\n", answer);
}
#if false==true
20 5
7 3 8 23
#endif
