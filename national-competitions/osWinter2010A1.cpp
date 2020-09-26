#include <bits/stdc++.h>
using namespace std;

struct hdd
{
    pair<int, int> range;
    hdd *left=nullptr, *right=nullptr;
    int maxVal=0, toProp=-1;

    int size()
    {
        return range.second-range.first+1;
    }

    hdd(pair<int, int> range)
    {
        this->range=range;

        if(size()>1)
        {
            int mid=(range.first+range.second)/2;
            this->left=new hdd({range.first, mid});
            this->right=new hdd({mid+1, range.second});
        }
    }

    void set(const pair<int, int> &inRange, int val)
    {
        if(range.second<inRange.first || range.first>inRange.second)return;

        maxVal=std::max(maxVal, val);
        if(range.first>=inRange.first && range.second<=inRange.second)
        {
            prop();
            toProp=val;
        }
        else
        {
            left->set(inRange, val);
            right->set(inRange, val);
        }
    }

    void prop()
    {
        if(toProp!=-1 && size()>1)
        {
            left->set(range, toProp);
            right->set(range, toProp);
            toProp=-1;
        }
    }

    int max(const pair<int, int> &inRange)
    {
        if(range.second<inRange.first || range.first>inRange.second)return -1;

        if(range.first>=inRange.first && range.second<=inRange.second)return maxVal;
        else
        {
            if(size()==1)return maxVal;
            else
            {
                prop();
                return std::max(left->max(inRange), right->max(inRange));
            }
        }
    }


    ~hdd()
    {
        if(size()>1)
        {
            delete left;
            delete right;
        }
    }
};

int m, n;
vector<pair<int, int>> sectors;

void read()
{
    cin>>m>>n;
    sectors.resize(n);
    for(auto &x : sectors)cin>>x.first>>x.second;
}

void compress()
{
    map<int, int> indexOf;
    for(const auto &x : sectors)indexOf[x.first]=indexOf[x.second]=0;

    m=1;
    for(auto it=indexOf.begin();it!=indexOf.end();it++)
    {
        it->second=m++;
    }
    m--;

    for(auto &x : sectors)
    {
        x.first=indexOf[x.first];
        x.second=indexOf[x.second];
    }
}

void solve()
{
    compress();
    hdd q({1, m});
    int answer=0;

    for(int i=0;i<sectors.size();i++)
    {
        const auto &sector=sectors[i];
        q.set({sector.first, sector.second}, i);
    }

    for(int i=0;i<sectors.size();i++)
    {
        const auto &sector=sectors[i];
        if(q.max({sector.first, sector.second})==i)
        {
            answer++;
        }
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
/*
10
3
1 3
4 7
3 4


10
4
1 3
4 5
7 8
4 6


*/
