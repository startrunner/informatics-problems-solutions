#include <cstdio>
#include <vector>
#include <malloc.h>
#include <map>
#include <unordered_map>
#include <bitset>
using namespace std;
const int P=123456789;

int n;
int maxA=0;
int* a;


int ways(int x, int y, int index)
{
    if(x<0||y<0)return 0;
    //printf("%d %d %d\n", x, y, index);
    if(index==n)return 0;
    if(x+y!=a[index])return 0;
    if(index==n-1)return 1;

    static vector<vector<map<int, int>>> memz(maxA+1, vector<map<int, int>>(maxA+1, map<int, int>()));

    int rt=memz[x][y][index];
    if(rt!=0)return rt;

    for(int x1=x;x1<=a[index+1];x1++)
    {
        int y1=a[index+1]-x1;
        if(y1<=y)rt+=ways(x1, y1, index+1);
    }

    memz[x][y][index]=rt%P;
    return rt;
}

int main()
{
    scanf("%d", &n);
    a=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){scanf("%d", &a[i]); maxA=max(maxA, a[i]);};

    int answer=0;
    for(int i=0;i<=a[0];i++)
    {
        answer+=ways(i, a[0]-i, 0);
    }
    printf("%d\n", answer%P);
}
