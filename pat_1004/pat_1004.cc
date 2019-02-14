#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
vector<vector<int>> adj;
int nn, mm;

int main(int argc, char const *argv[])
{
    cin >> nn >> mm;
    adj.resize(nn+1);
    int vv, uu, kk;
    for(int ii=0;ii<mm;ii++)
    {
        cin >> vv >> kk;
        while(kk)
        {
            cin >> uu;
            adj[vv].push_back(uu);
            kk--;
        }
    }
    queue<int> qq;
    qq.push(1);
    vector<int> res(nn+1, 0);
    int lvl = 1;
    while(!qq.empty())
    {
        queue<int> levelQ;
        while(!qq.empty())
        {
            vv = qq.front();
            qq.pop();
            if (adj[vv].size()==0) res[lvl]++;
            else{
                for(auto uu: adj[vv])
                    levelQ.push(uu);
            }
        }
        lvl++;
        qq = levelQ;
    }
    cout << res[1];
    for(int ii=2;ii<lvl;ii++) cout << " " << res[ii];
    return 0;
}
