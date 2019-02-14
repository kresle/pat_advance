#include <iostream>
#include <vector>
#include <set>
using namespace std;

int nn, mm;
vector<vector<bool>> connected;
int kk;

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> mm;
    connected.resize(nn+1, vector<bool>(nn+1, false));
    int vv, uu;
    for(int ii=0;ii<mm;ii++)
    {
        cin >> vv >> uu;
        connected[vv][uu] = true;
        connected[uu][vv] = true;
    }
    cin >> kk;
    while(kk--)
    {
        int nv;
        cin >> nv;
        vector<int> query(nv, -1);
        set<int> visited;
        for(int ii=0;ii<nv;ii++) cin >> query[ii];
        if (nv!=nn+1||query.front()!=query.back())
        {
            cout << "NO" << endl;
            continue;
        }
        //nv==nn+1 && query.front()==query.end()
        for(int ii=1;ii<query.size();ii++)
        {
            if (connected[query[ii-1]][query[ii]]) visited.insert(query[ii]);
            else break;
        }
        cout << ((visited.size()==nn)?"YES":"NO") << endl;
    }
    return 0;
}
