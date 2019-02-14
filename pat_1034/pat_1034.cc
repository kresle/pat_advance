/**
 * 连通区域问题
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int nn, kk;
vector<vector<int>> edge;
vector<int> weight;
unordered_map<string, int> name2id;
vector<string> id2name;
// set<int> visited, unvisited;
vector<int> visited;
vector<vector<int>> adj;
int nMember;
int nComponents;
map<string, int> res;

void dfs(int vv)
{
    // cerr << id2name[vv] << " ";
    nMember++;
    visited[vv] = nComponents;
    for(auto uu : adj[vv])
    {
        if (!visited[uu]) dfs(uu);
    }
}

int findHead(int component)
{
    vector<int> members;
    for(int ii=0;ii<visited.size();ii++)
    {
        if (visited[ii]==component) 
        {
            members.push_back(ii);
            cerr << id2name[ii] << " ";
        }
    }
    cerr << endl;
    cerr << members.size() << endl;
    int maxWeight = 0, maxId = -1, totalWeight = 0;
    for(auto ii : members)
    {
        int memWeight = 0;
        for(auto jj:members)
        {
            totalWeight+=edge[ii][jj];
            memWeight+=edge[ii][jj];
            memWeight+=edge[jj][ii];
            if (id2name[ii]=="C")
            {
                cerr << edge[ii][jj] << " " << edge[jj][ii] << endl;
            }
        }cerr << endl;
        if (memWeight>maxWeight)
        {
            maxWeight = memWeight;
            maxId = ii;
        }
        // if (id2name[ii]=="U") cerr << id2name[ii] << " " << memWeight << " " << weight[ii] << endl;
        // if (id2name[ii]=="Q") cerr << id2name[ii] << " " << memWeight << " " << weight[ii] << endl;
        cerr << id2name[ii] << " " << memWeight << " " << weight[ii] << endl;
    }
    if (totalWeight>kk) return maxId;
    return -1;
}

int main()
{
    cin >> nn >> kk;
    edge.resize(2*nn, vector<int>(2*nn, 0));
    weight.resize(2*nn);
    string name1, name2;
    int id1, id2;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> name1 >> name2;
        if (name2id.find(name1)==name2id.end())
        {
            id1 = id2name.size();
            // unvisited.insert(id1);
            name2id.insert(make_pair(name1, id1));
            id2name.push_back(name1);
            adj.push_back(vector<int>());
        }
        else{
            id1 = name2id.find(name1)->second;
        }
        if (name2id.find(name2)==name2id.end())
        {
            id2 = id2name.size();
            // unvisited.insert(id2);
            name2id.insert(make_pair(name2, id2));
            id2name.push_back(name2);
            adj.push_back(vector<int>());
        }
        else{
            id2 = name2id.find(name2)->second;
        }
        int tmp;
        cin >> tmp;
        edge[id1][id2] += tmp;
        // cerr << id1 << " " << id2 << " " << edge[id1][id2] << endl;
        adj[id1].push_back(id2);
        adj[id2].push_back(id1);
        weight[id1]+=tmp;
        weight[id2]+=tmp;
    }
    cerr << "Total:" << id2name.size() << endl;
    int nGang = 0;
    nComponents = 0;
    visited.resize(id2name.size(), 0);
    auto idx = find(visited.begin(), visited.end(), 0);
    while(idx != visited.end())
    {
        nComponents++;
        nMember = 0;
        dfs(idx-visited.begin());
        // cerr << endl;
        if (nMember>2) 
        {
            int head = findHead(nComponents);
            if (head!=-1) 
            {
                nGang++;
                // cout << id2name[head] << " " << nMember << endl;
                res.insert(make_pair(id2name[head], nMember));
            }
        }
        idx = find(visited.begin(), visited.end(), 0);
    }
    cout << res.size() << endl;
    for(auto rr: res)
    {
        cout << rr.first << " " << rr.second << endl;
    }
    return 0;
}