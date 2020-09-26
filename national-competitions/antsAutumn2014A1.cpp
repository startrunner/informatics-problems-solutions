using namespace std;
#include <cstdint>
#include <vector>
#include <cstdio>
#include <queue>
#include <tuple>
#define this (*this)
#define null nullptr
using uint=uint_fast32_t;
struct range_t{int first, second;};

inline int common(const range_t &a, const range_t &b)
{
    if(a.first>b.first)return common(b, a);
    if(b.first>a.second)return 0;
    else if(b.second<=a.second)return b.second-b.first+1;
    else return a.second-b.first+1;
}

class tree_node
{
    using node=tree_node;
    friend class tree;

    int version, value;
    range_t range;
    node *left=null, *right=null;

    int size()
    {
        return range.second-range.first+1;
    }

    tree_node(const range_t &range, int version)
    {
        this.range=range;
        this.version=version;
        this.value=0;

        if(range.first!=range.second)
        {
            int split=range.first+(range.second-range.first)/2;
            left=new node({range.first, split}, version);
            right=new node({split+1, range.second}, version);
        }
    }

    tree_node(node& that, int version)
    {
        that.prop();
        this.range=that.range;
        this.value=that.value;
        this.version=version;
        this.left=that.left;
        this.right=that.right;
    }

    int toProp=0;
    void prop()
    {
        if(left!=null&&toProp!=0)
        {
            left->add(range, toProp);
            right->add(range, toProp);
        }

        toProp=0;
    }

    void add(const range_t &range, int value)
    {
        int cmn=common(this.range, range);
        this.value+=cmn*value;

        if(cmn!=0&&left!=null)
        {
            if(common(left->range, range)!=0)
            {
                if(left->version!=this.version)left=new node(*left, this.version);
                if(cmn!=size())left->add(range, value);
            }
            if(common(right->range, range)!=0)
            {
                if(right->version!=this.version)right=new node(*right, this.version);
                if(cmn!=size())right->add(range, value);
            }
            if(cmn==size())toProp+=value;
        }

    }

    void print(char c, int indent)
    {
        prop();
        for(int i=0; i<indent; i++)printf(" ");
        printf("{%c {%d %d} ver: %d val: %d", c, range.first, range.second, version, value);
        if(left!=null)
        {
            puts("");
            left->print('l', indent+1);
            right->print('r', indent+1);
        }
        for(int i=0; i<indent; i++)printf(" ");
        printf("}\n");
    }

    int query(const range_t &range)
    {
        prop();
        int cmn=common(range, this.range);
        if(cmn==0)return 0;
        else if(cmn==this.size())return value;
        else return left->query(range)+right->query(range);
    }

};

struct tree
{
    using node=tree_node;
    int latest=1;
    vector<node*> versions {null};
    tree(const range_t &range)
    {
        versions.push_back(new node(range, 1));
    }

    void print(int version=0)
    {
        if(version==0)version=latest;
        versions[version]->print('t', 0);
    }

    void addTo(int version, const range_t &range, int value)
    {
        versions[version]->add(range, value);
    }

    void add(int version, const range_t &range, int value)
    {
        versions.push_back(new node(*versions[version], ++latest));
        versions.back()->add(range, value);
    }

    int query(range_t range, int version=0)
    {
        if(version==0)version=latest;
        return versions[version]->query(range);
    }

};

tree* cities;

int n, m;
int main()
{
    scanf("%d %d", &n, &m);
    cities=new tree({1, n});
    for(static int i=1; i<=m; i++)
    {
        static int j;
        scanf("%d", &j);
        cities->addTo(1, {i, i}, j);
    }
    //cities->print();

    queue<int> answer;
    for(static int number=2, s=0; number<=n; number++)
    {
        static int p, x, y, v, z, t;
        static int l, r, i, j;
        scanf("%d %d %d %d %d %d", &p, &x, &y, &v, &z, &t);
        l=(x+s)%m+1;
        r=(y+s)%m+1;
        i=(z+s)%m+1;
        j=(t+s)%m+1;
        //printf("%d %d %d %d\n", l, r, i, j);
        cities->add(p, {l, r}, v);
        //cities->print();
        int q=cities->query({i, j});
        answer.push(q);
        //printf("%d\n", q);
        s=q;
    }
    while(!answer.empty())printf("%d\n", answer.front()), answer.pop();

    //for(int i=1;i<=cities->latest;i++)cities->print(i), puts("\n");
}
/*
4 4
3 6 7 5
1 2 3 1 0 1
2 1 2 6 2 2
1 0 2 8 0 3
*/
#undef this
#undef null
