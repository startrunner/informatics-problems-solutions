#include <cstdio>
#include <vector>
#include <ctime>
#include <iostream>
#include <bitset>
//#define GEN

using namespace std;

#ifdef GEN
unsigned long long ways[29];
void go(int x, int y, int moves)
{
    static bitset<32> used[32];
    used[0][0]=true;

    if(x<0 || y<0)return;
    if(used[x][y])return;
    if(moves==29)return;

    ways[moves]++;

    used[x][y]=true;
    go(x+1, y, moves+1);
    go(x-1, y, moves+1);
    go(x, y+1, moves+1);
    go(x, y-1, moves+1);
    used[x][y]=false;
}

int main()
{
    go(0, 1, 1);
    for(int i=1; i<29; i++)printf("%d %lld\n", i, ways[i]);
}
#endif // GEN

#ifndef GEN
int main()
{
    unsigned long long a[29];
    a[1]=  1;
    a[2]=  2;
    a[3]=  5;
    a[4]=  12;
    a[5]=  30;
    a[6]=  73;
    a[7]=  183;
    a[8]=  456;
    a[9]=  1151;
    a[10]= 2900;
    a[11]= 7361;
    a[12]= 18684;
    a[13]= 47652;
    a[14]= 121584;
    a[15]= 311259;
    a[16]= 797311;
    a[17]= 2047384;
    a[18]= 5260692ull;
    a[19]= 13542718ull;
    a[20]= 34884239ull;
    a[21]= 89991344ull;
    a[22]= 232282110ull;
    a[23]= 600281932ull;
    a[24]= 1552096361ull;
    a[25]= 4017128206ull;
    a[26]= 10401997092ull;
    a[27]= 26957667445ull;
    a[28]= 69892976538ull;

    int x, y;
    unsigned long long answer=0;
    cin>>x>>y;
    for(int i=x; i<=y; i++)answer+=a[i];
    cout<<answer<<endl;

}
#endif // GEN
