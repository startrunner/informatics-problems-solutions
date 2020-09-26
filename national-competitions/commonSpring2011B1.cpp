#include <bits/stdc++.h>
using namespace std;

int k;
vector<vector<int>> rows;

void read()
{
   cin>>k;
   rows.assign(k, {});
   for(int i=0, j;i<k;i++)
   {
      cin>>j;
      rows[i].resize(j);
   }

   for(auto &i : rows)for(int &j : i)cin>>j;
}

void solve()
{
   map<int, int> rowCount;
   for(int i=0;i<k;i++)
   {
      auto &row=rows[i];
      sort(row.begin(), row.end());
      for(int j=0;j<row.size();j++)
      {
         int num=row[j];
         if(j!=0&&num==row[j-1])continue;

         int rc=rowCount[num];
         if(rc==i)
         {
            rc++;
            rowCount[num]=rc;
         }
         else rowCount.erase(num);
      }
   }

   for(pair<int, int> i : rowCount)
   {
      if(i.second==k)
      {
         printf("%d\n", i.first);
         return;
      }
   }
   puts("x");
}

int main()
{
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   read();
   solve();
}
/*
3
5 6 7
2 1 3 4 3
4 5 -1 0 0 3
11 4 7 8 9 0 3
*/
