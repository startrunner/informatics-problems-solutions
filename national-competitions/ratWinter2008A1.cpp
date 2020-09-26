#include <iostream>
#include <cstdio>
using namespace std;

struct ans_t{int64_t num, denum;};

ans_t solve(int64_t n)
{
    if(n==0)return {1, 1};
    if(n%2==0)
    {
        ans_t parent=solve((n-1)/2);
        return {parent.num, parent.num+parent.denum};
    }
    else
    {
        ans_t parent=solve(n/2);
        return {parent.num+parent.denum, parent.denum};
    }
}

int main()
{
    int64_t n;
    cin>>n;
    ans_t answer=solve(n);
    printf("%lld %lld\n", answer.denum, answer.num);
}
