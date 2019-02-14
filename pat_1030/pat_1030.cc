#include <iostream>
#include <set>
#include <vector>
using namespace std;

// int edge[500][500]={500};//这种写法是错的
// int cost[500][500]={500};
vector<vector<int>> edge(500, vector<int>(500, 500));
vector<vector<int>> cost(500, vector<int>(500, 500));

// int dist[500]={501*501};
vector<int> dist(500, 501*501);
// int path[500]={-1};
vector<vector<int>> path(500);
vector<int> optPath, tmpPath;

vector<vector<int>> adj;

int nn, mm , id_st, id_ed;
int minCost = 501*501;

set<int> optimized;
set<int> unknown;

void dfs(int vv, int cc)
{
    tmpPath.push_back(vv);
    if (vv==id_st)
    {
        if (cc<minCost)
        {
            minCost = cc;
            optPath = tmpPath;
        }
    }
    else{
        for(auto uu : path[vv])
        {
            // tmpPath.push_back(uu);
            dfs(uu, cc+cost[vv][uu]);
            // tmpPath.pop_back();
        }
    }
    tmpPath.pop_back();
}

int main()
{
    cin >> nn >> mm >> id_st >> id_ed;
    int st, ed;
    adj.resize(nn);
    for(int ii=0;ii<mm;ii++)
    {
        cin >> st >> ed;
        cin >> edge[st][ed] >> cost[st][ed];
        edge[ed][st] = edge[st][ed];
        cost[ed][st] = cost[st][ed];
        adj[st].push_back(ed);
        adj[ed].push_back(st);
        if (st==id_st) {dist[ed] = edge[st][ed];path[ed].push_back(id_st);}
        if (ed==id_st) {dist[st] = edge[st][ed];path[st].push_back(id_st);}
    }
    optimized.insert(id_st);
    for(int ii=0;ii<nn;ii++) if (ii!=id_st) {unknown.insert(ii);}
    while(optimized.find(id_ed)==optimized.end())
    {
        int minDist = 501*501, minId = -1;
        for(auto vv: unknown)
        {
            if (dist[vv]<minDist)
            {
                minDist = dist[vv];
                minId = vv;
            }
        }
        optimized.insert(minId);
        unknown.erase(minId);
        for(auto vv:unknown)
        {
            if (edge[minId][vv]!=500&&minDist+edge[minId][vv]<dist[vv])
            {
                dist[vv] = minDist+edge[minId][vv];
                // path[vv] = minId;
                path[vv].clear();
                path[vv].push_back(minId);
            }
            else{
                if (edge[minId][vv]!=500&&minDist+edge[minId][vv]==dist[vv]) path[vv].push_back(minId);
            }
        }
    }
    // int uu = id_ed;
    // cout << uu;
    // while(uu!=id_st)
    // {
    //     uu = path[uu];
    //     cout << "<-" << uu;
    // }
    // cout << endl;
    // cout << dist[id_ed] ;
    dfs(id_ed, 0);
    for(int ii=optPath.size()-1;ii>=0;ii--) cout << optPath[ii] << " ";
    cout << dist[id_ed] << " " << minCost;
    return 0;
}