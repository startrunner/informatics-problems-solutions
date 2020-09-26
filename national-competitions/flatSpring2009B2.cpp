extern "C"
{
    int printf(const char*, ...);
    int scanf (const char*, ...);
    void* malloc(int);
    void free(void*);
}

const int INF=1000000+10;

typedef struct{int first, second;}range_t;

//inline int min(int a,  int b){if(a<b)return a; return b;}

struct node
{
    range_t range;
    node *children;
    int minVal=INF;

    node(const range_t& range)
    {
        this->range=range;
        if(range.first!=range.second)
        {
            int split=(range.first+range.second)/2;
            children=new node[2]
            {node({range.first, split}), node({split+1, range.second})};
        }
        else children=nullptr;
    }

    void set(int index, int value)
    {
        if(index<range.first || index>range.second)return;
        if(value<minVal)minVal=value;
        if(children!=nullptr)
        {
            children[0].set(index, value);
            children[1].set(index, value);
        }
    }

    int rmq(const range_t &range)
    {
        if(range.second<this->range.first || range.first>this->range.second)return INF;
        if(this->range.first>=range.first && this->range.second<=range.second)return minVal;
        else
        {
            int a=children[0].rmq(range);
            int b=children[1].rmq(range);
            if(a<b)return a;
            return b;
        }
    }

    ~node(){delete children;}
};

unsigned long long minPrice=-1;
int start;

void main1()
{
    int n, k, i, *beach;
    unsigned long long cSum=0, cPrice;

    scanf("%d%d", &n, &k);
    beach=(int*)malloc(sizeof(int)*(n+1));
    for(i=0;i<n;i++)scanf("%d", &beach[i]);

    node tree({0, n-1});
    for(i=0;i<n;i++)tree.set(i, beach[i]);

    for(i=0;i<k;i++)cSum+=beach[i];

    for(i=k-1;i<n;i++)
    {
        cPrice=cSum-tree.rmq({i-k+1, i})*k;
        if(cPrice<minPrice)
        {
            minPrice=cPrice;
            start=i-k+2;
        }

        cSum-=beach[i-k+1];
        cSum+=beach[i+1];
    }

    free(beach);
}

int main()
{
    main1();
    printf("%llu\n%d\n", minPrice, start);
}
/*
6 4
10 4 5 2 5 7
*/
