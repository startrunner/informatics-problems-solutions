#include <bits/stdc++.h>
using namespace std;

char f(char a, char b)
{
    return '0'+(int)(a=='0' || b=='0');
}

string expr;
vector<string> queries;

void read()
{
    cin>>expr;
    for(string q;;)
    {
        cin>>q;
        if(q=="2")break;
        queries.push_back(q);
    }
}

stack<char> st;
char solve(const string &terminals)
{
    while(!st.empty())st.pop();

    for(char c : expr)
    {
        if(c=='(')st.push(c);
        else
        {
            char add;
            if(c==')')
            {
                add=st.top();
                st.pop();//val
                st.pop();//(
            }
            else add=terminals[c-'a'];

            if(st.empty() || st.top()=='(')st.push(add);
            else
            {
                char top=st.top();
                st.pop();
                st.push(f(top, add));
            }
        }
    }
    return st.top();
}

void solve()
{
    for(string &q : queries)putchar(solve(q));
    puts("");
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}



/**

a(a)(ab(ca)bb)c
011
100
010
111
001
2

*/




/*#include <bits/stdc++.h>
using namespace std;

bool f(bool a, bool b)
{
    return !(a&&b);
}

int n;
vector<int> opensAt;
string exprStr;
vector<bool> terminals;
stringstream out;

struct expression
{
    char terminal='_';
    expression *left, *right;

    expression(char c)
    {
        terminal=c;
    }


    expression(expression *l, expression *r)
    {
        left=l;
        right=r;
    }

    bool solve()
    {
        if(terminal!='_')return terminals[terminal];
        else return f(left->solve(), right->solve());
    }
};

void read()
{
    cin>>exprStr;
    //shrink();
    n=exprStr.size();
}

expression* parse(int from, int to)
{
    expression *rt;

    if(opensAt[to]==from)
    {
        rt= parse(from+1, to-1);
    }
    else if(from==to)
    {
        char c=exprStr[from];
        if(c=='(' || c==')')
        {
            puts("error!");
            throw;
        }
        rt= new expression(c-'a');
    }
    else
    {

        int aFrom, aTo, bFrom, bTo;
        aFrom=from;
        bTo=to;

        if(opensAt[bTo]!=-1)bFrom=opensAt[bTo];
        else bFrom=bTo;
        aTo=bFrom-1;

        //rt=f(solve(aFrom, aTo), solve(bFrom, bTo));
        rt=new expression(parse(aFrom, aTo), parse(bFrom, bTo));
    }


    //printf("%d %d -> %d\n ", from, to, (int)rt);
    return rt;
}

void solve()
{
    //closesAt.resize(n, -1);
    opensAt.resize(n, -1);
    stack<pair<char, int>> brackStack;
    for(int i=0;i<n;i++)
    {
        char c=exprStr[i];
        if(c!='(' && c!=')')continue;

        if(!brackStack.empty() && brackStack.top().first=='(' && c==')')
        {
            //closesAt[brackStack.top().second]=i;
            opensAt[i]=brackStack.top().second;
            brackStack.pop();
        }
        else brackStack.emplace(c, i);
    }

    //for(int i=0;i<n;i++)printf("%d %d\n", i, closesAt[i]);
    //puts("");

    expression *expr=parse(0, n-1);
    for(string s;;)
    {
        cin>>s;
        if(s=="2")break;

        terminals.resize(s.size());
        for(int i=0;i<s.size();i++)terminals[i]=(s[i]=='1');
        out<<((int)(expr->solve()));
        //for(bool b : terminals)printf("%d ", (int)b);
        //puts("");

        //printf("answer: %d\n", (int) solve(0, n-1));
    }

    puts(out.str().c_str());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read();
    solve();
}*/
/**

a(a)(ab(ca)bb)c
011
100
010
111
001
2

*/
