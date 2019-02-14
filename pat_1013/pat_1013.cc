#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int nn,mm,kk;
vector<vector<bool>> connectedD, connected;
vector<int> checkCity;

// vector<bool> visited;
int blockCity;
set<int> remain, allCity;

void bfs(int start)
{
    queue<int> qq;
    qq.push(start);
    while(!qq.empty())
    {
        // visited[qq.front()] = true;
        remain.erase(qq.front());
        for(auto jj : remain)
        {
            // if (visited[jj]) continue;
            if (connectedD[qq.front()][jj]) qq.push(jj);
        }
        qq.pop();
    }
}

// int findUnvisited()
// {
//     for(int ii=0;ii<nn;ii++)
//     {
//         if (ii!=blockCity&&!visited[ii]) return ii;
//     }
//     return -1;//如果都访问过
// }

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> nn >> mm >> kk;
    connectedD.resize(nn,vector<bool>(nn, false));
    checkCity.resize(kk,-1);
    int vv, uu;
    for(int ii=0;ii<mm;ii++)
    {
        cin >> vv >> uu;
        vv--;uu--;
        connectedD[vv][uu] = connectedD[uu][vv] = true;
    }
    for(int ii=0;ii<kk;ii++)
    {
        cin >> checkCity[ii];
        checkCity[ii]--;
    }
    for(int ii=0;ii<nn;ii++) allCity.insert(ii);
    for(int ii=0;ii<kk;ii++)
    {
        // visited.clear();
        // visited.resize(nn, false);
        blockCity = checkCity[ii];
        remain.clear();
        remain = allCity;
        remain.erase(blockCity);
        int connectArea = 0;
        // int start = *remain.begin();
        while(!remain.empty())
        {
            // cerr << *remain.begin() << endl;
            bfs(*remain.begin());
            connectArea++;
            // start = findUnvisited();
        }
        cout << connectArea-1 << endl;
    }
    return 0;
}
