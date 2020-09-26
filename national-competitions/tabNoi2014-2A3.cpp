#include <bits/stdc++.h>
using namespace std;

bitset<1000000+1>isPrime;
vector<int> primes;
int n, r, c;

struct num
{
    int value, divisors;
    num(int value, int divisors)
    {
        this->value=value;
        this->divisors=divisors;
    }

    num():num(1, 0){}

    bool operator < (const num &n)
    {
        return divisors<n.divisors || (divisors==n.divisors && value<n.value);
    }
};

void get_primes()
{
    int len=isPrime.size();
    isPrime.set();
    isPrime[0]=isPrime[1]=false;

    for(int i=2;i<len;i++)
    {
        if(isPrime[i])for(int j=i*2;j<len;j+=i)isPrime[j]=false;
    }

    for(int i=2;i<len;i++)if(isPrime[i])primes.push_back(i);
    primes.shrink_to_fit();

    //for(int i=0;i<100;i++)if(isPrime[i])printf("%d\n", i);
}


void solve()
{
    vector<num> nums(1);
    for(int i=1;i<=n*n;i++)nums.emplace_back(i, 0);
    for(int prime : primes)
    {
        for(int i=prime;i<=n*n;i+=prime)nums[i].divisors++;
    }
    sort(nums.begin(), nums.end());

    printf("%d\n", nums[(r-1)*n+c].value);
}

int main()
{
    get_primes();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>r>>c;
    solve();
}
