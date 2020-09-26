#include <bits/stdc++.h>
using namespace std;

/*template<typename T1, typename T2=int> struct pair
{
    T1 first;
    T2 second;

    inline pair(T1 first, T2 second)
    {
        this->first=first;
        this->second=second;
    }

    inline pair():pair(T1(), T2()){};
};*/

struct node
{
    long long value=0;
    pair<int, int>range;
    node *left=nullptr, *right=nullptr;

    node(const pair<int, int> &range)
    {
        this->range=range;
        if(range.first!=range.second)
        {
            int split=range.first+(range.second-range.first)/2;
            this->left=new node({range.first, split});
            this->right=new node({split+1, range.second});
        }
    }

    long long query(const pair<int, int> &range)
    {
        if(range.second < this->range.first)return 0;
        if(range.first > this->range.second)return 0;

        if(this->range.first >= range.first && this->range.second <= range.second)return value;

        return left->query(range) + right->query(range);
    }

    void add1(int index)
    {
        if(index<range.first || index>range.second)return;
        else
        {
            this->value++;
            if(left!=nullptr)
            {
                left->add1(index);
                right->add1(index);
            }
        }
    }

    void print(int indent=0)
    {
        for(int i=0;i<indent;i++)printf(" ");
        if(left==nullptr)printf("range: {%d, %d} value: %d\n", range.first, range.second, value);

        else
        {
            printf("{->range: {%d, %d} value: %d\n", range.first, range.second, value);
            left->print(indent+1);
            right->print(indent+1);
            for(int i=0;i<indent;i++)printf(" ");
            printf("}\n");
        }
    }
};

node *tree;

void v1123()
{

}
void v1123(int i)
{

}
void v1123(int i, int j)
{

}

int n;
int main()
{
    scanf("%d", &n);

    tree=new node({1, n});

    long long answer=0;
    for(int i=1, j;i<=n;i++)
    {
        scanf("%d", &j);
        answer+=tree->query({j, n});
        tree->add1(j);
    }

    printf("%lld\n", answer);

}
/*
7
4 2 7 1 5 6 3
*/
