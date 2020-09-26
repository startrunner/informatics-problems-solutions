#include <bits/stdc++.h>
using namespace std;


class node
{
    int flips=0, addToProp=0;
    int maxLen=1, maxLenToProp=0;
    pair<int, int> range;
    node *left=nullptr, *right=nullptr;

    int size(){return range.second-range.first+1;}


public:

    int max_len(){return maxLen;}

    node(pair<int, int> range)
    {
        this->range=range;
        //maxReaches=range.second;
        if(range.first!=range.second)
        {
            int split=(range.first+range.second)/2;
            left=new node({range.first, split});
            right=new node({split+1, range.second});
        }
    }

    void add_prop()
    {
        if(addToProp!=0)
        {
            left->add_flips(this->range, addToProp);
            right->add_flips(this->range, addToProp);
            addToProp=0;
        }
    }

    int get_flips(pair<int, int> range)
    {
        if(range.second<this->range.first || range.first>this->range.second)return 0;

        else if(size()==1)return flips;
        add_prop();

        return left->get_flips(range)+right->get_flips(range);
    }

    void add_flips(pair<int, int> range, int flipCount)
    {
        if(range.second<this->range.first || range.first>this->range.second)return;

        if(size()==1)flips+=flipCount;
        else if(this->range.first>=range.first && this->range.second<=range.second)
        {
            flips+=size()*flipCount;
            addToProp+=flipCount;
        }
        else
        {
            left->add_flips(range, flipCount);
            right->add_flips(range, flipCount);
            flips=left->flips+right->flips;
        }
    }

    int first_to_reach(pair<int, int> range, int index)
    {
        if(range.second<this->range.first || range.first>this->range.second)return -1;

        max_len_prop();

        if(this->range.first>=range.first && this->range.second<=range.second)
        {
            if(this->range.second+maxLen<=index)return -1;
            else if(size()==1)return this->range.second;
        }

        int l=left->first_to_reach(range, index);
        if(l!=-1)return l;
        return right->first_to_reach(range, index);
    }

    void max_len_prop()
    {
        if(maxLenToProp!=0)
        {
            left->add_len(this->range, maxLenToProp);
            right->add_len(this->range, maxLenToProp);
            maxLen=max(left->maxLen, right->maxLen);
            maxLenToProp=0;
        }
    }

    int get_max_len(int index)
    {
        if(index<range.first || index>range.second)return -1;
        if(size()==1)return maxLen;
        max_len_prop();
        return max(left->get_max_len(index), right->get_max_len(index));
    }

    void add_len(pair<int, int> range, int addLen)
    {
        if(range.second<this->range.first || range.first>this->range.second)return;

        if(this->range.first>=range.first && this->range.second<=range.second)
        {
            maxLen+=addLen;
            if(size()!=1)maxLenToProp+=addLen;
        }
        else
        {
            left->add_len(range, addLen);
            right->add_len(range, addLen);
            maxLen=max(left->maxLen, right->maxLen);
        }
    }

    ~node()
    {
        if(size()>1)
        {
            delete left;
            delete right;
        }
    }
};

node *tree=nullptr;

int n, q;

void read()
{
    cin>>n>>q;
    tree=new node({1, n});
}

void solve()
{
    int lastQ=-1, lastQI=-1;
    for(int i=0;i<q;i++)
    {
        string command;
        cin>>command;
        if(command=="c")
        {
            int a, b;
            cin>>a>>b;
            a++;
            b++;
            tree->add_flips({a, b}, 1);
            int aLen=tree->get_max_len(a);
            if(b<n)
            {
                int rangeEnd=tree->get_flips({b, b})%2;
                int afterRange=tree->get_flips({b+1, b+1})%2;
                if(rangeEnd==afterRange)
                {
                    int ftr=tree->first_to_reach({a, b}, b+1);
                    if(ftr!=-1)
                    {
                        int len=tree->get_max_len(b+1);
                        tree->add_len({ftr, b}, -len);
                    }
                }
                else
                {
                    int ftr=tree->first_to_reach({a, b}, b);
                    if(ftr!=-1)
                    {
                        int len=tree->get_max_len(b+1);
                        tree->add_len({ftr, b}, len);
                    }
                }
            }
            if(a!=0)
            {
                int rangeStart=tree->get_flips({a, a})%2;
                int beforeRange=tree->get_flips({a-1, a-1})%2;
                int len=tree->get_max_len(a);
                if(rangeStart==beforeRange)
                {
                    int ftr=tree->first_to_reach({1, a-1}, a);
                    if(ftr!=-1)
                    {
                        tree->add_len({ftr, a-1}, -aLen);
                    }
                }
                else
                {
                    int ftr=tree->first_to_reach({1, a-1}, a-1);
                    if(ftr!=-1)
                    {
                        tree->add_len({ftr, a-1}, +len);
                    }
                }
            }
        }
        else
        {
            if(lastQI==i-1)
            {
                lastQI=i;
            }
            lastQ=tree->max_len();
            lastQI=i;
            printf("%d\n", lastQ);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}
