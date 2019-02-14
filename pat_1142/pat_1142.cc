/**
 * 集合的交并：intersection, union
 */

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int nv, ne, mm, kk;
vector<vector<bool>> edge;
vector<set<int>> adj;
vector<int> query;

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nv >> ne;
    edge.resize(nv+1, vector<bool>(nv+1, false));
    adj.resize(nv+1);
    int st, ed;
    for(int ii=0;ii<ne;ii++)
    {
        cin >> st >> ed;
        edge[st][ed] = true;
        edge[ed][st] = true;
        adj[st].insert(ed);
        adj[ed].insert(st);
    }
    cin >> mm;
    while(mm--)
    {
        cin >> kk;
        query.clear();query.resize(kk);
        for(int ii=0;ii<kk;ii++) cin >> query[ii];
        bool isClique=true;
        for(int ii=0;ii<kk;ii++)
            for(int jj=ii+1;jj<kk;jj++)
            {
                if (!edge[query[ii]][query[jj]]) {
                    isClique = false;
                    break;
                }
            }
        if (isClique)
        {
            set<int> intersect = adj[query[0]];
            for(int ii=1;ii<kk;ii++)
            {
                for(auto vv: intersect)
                {
                    if (adj[query[ii]].find(vv)==adj[query[ii]].end()) intersect.erase(vv);
                }
                if (intersect.empty()) break;
            }
            if (intersect.empty()) cout << "Yes" << endl;
            else cout << "Not Maximal" << endl;
            // for(auto vv: intersect) cerr << vv << " "; cerr << endl;
        }
        else{
            cout << "Not a Clique" << endl;
        }
    }
    return 0;
}
