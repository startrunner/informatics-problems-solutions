#include <cstdio>
#include <vector>
#include <deque>
#include <cstdint>
using namespace std;
using uint64=uint_fast64_t;

int p;
deque <int> getDigits(uint64 number)
{
    deque <int> rt;
    do
    {
        rt.push_front(number%p);
        number/=p;
    }while(number!=0);
    return rt;
}

bool isFine(uint64 number)
{
    deque <int> digits=getDigits(number);
    int ones=0, twos=0;
    for(int i : digits)
    {
        if(i==1)ones++;
        else if(i==2)twos++;
        else if(i!=0)return false;
    }
    return (ones==1&&twos>=1)||(ones==2&&twos==0);
}

uint64 n1, n2, n3, n4;
int main()
{
    scanf("%d", &p);
    scanf("%lld %lld %lld %lld", &n1, &n2, &n3, &n4);
    printf("%d %d %d %d\n", isFine(n1), isFine(n2), isFine(n3), isFine(n4));
}
/*
3 6 6 6 1000000000000000000
3 7 28 13 9
*/
