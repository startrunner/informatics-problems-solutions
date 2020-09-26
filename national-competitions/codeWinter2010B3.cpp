#include <bits/stdc++.h>
using namespace std;

template<typename T>bool next(vector<T> &v)
{
    if(v.size()==0)return false;
    v.back()++;
    for(int i=v.size()-1;i>0;i--)
    {
        if(v[i]==3){v[i-1]++; v[i]=0;}
        else break;
    }
    if(v.front()==3)
    {
        v=vector<T>(v.size(), 0);
        return false;
    }
    else return true;
}

int n;
vector<vector<short>> combs;
vector<vector<bool>> grMatrix;
vector<vector<int>> gr;

vector<int> finalStack;

int calls=0;
bool used[256];
vector<int> callstack;
void go()
{
    if(callstack.size()>finalStack.size())
    {
        finalStack=callstack;
    }
    for(int i=0;i<n;i++)
    {
        if(used[i])goto next;

        for(int j : callstack)
        {
            if(!grMatrix[i][j])goto next;
        }

        used[i]=true;
        callstack.push_back(i);
        go();
        callstack.pop_back();
        used[i]=false;

        next:;
    }
}

int main()
{
    vector<short> comb(5, 0);
    do{combs.push_back(comb);}while(next(comb));
    n=combs.size();

    grMatrix.resize(n, vector<bool>(n, false));
    gr.resize(n);

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int diff=0;
            for(int k=0;k<5;k++)
            {
                if(combs[i][k]!=combs[j][k])diff++;
            }
            if(diff>=3)
            {
                grMatrix[i][j]=true;
                grMatrix[j][i]=true;
                gr[i].push_back(j);
                gr[j].push_back(i);
            }
        }
    }

    go();
    printf("%d\n", finalStack.size());
    for(int i : finalStack)
    {
        for(int j : combs[i])printf("%d", j);
        puts("");
    }
}
