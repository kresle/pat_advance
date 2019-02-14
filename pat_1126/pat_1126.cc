#include <iostream>
#include <vector>
#include <set>
using namespace std;

int nn, mm;
set<int> visited;
vector<vector<int>> adj;

void dfs(int nid)
{
    visited.insert(nid);
    for (auto vv : adj[nid])
    {
        if (visited.find(vv) == visited.end())
            dfs(vv);
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> mm;

    int degree[nn + 1];
    fill(degree, degree + nn + 1, 0);

    adj.resize(nn + 1);

    int vv, uu;
    for (int ii = 0; ii < mm; ii++)
    {
        cin >> vv >> uu;
        degree[vv]++;
        degree[uu]++;
        adj[vv].push_back(uu);
        adj[uu].push_back(vv);
    }

    int oddCnt = (degree[1] % 2 == 1);
    cout << degree[1];
    for (int ii = 2; ii <= nn; ii++)
    {
        cout << " " << degree[ii];
        oddCnt += (degree[ii] % 2 == 1);
    }
    cout << endl;

    dfs(1);

    if (visited.size()!=nn)
        cout << "Non-Eulerian" << endl;
    else if (oddCnt == 0)
        cout << "Eulerian" << endl;
    else if (oddCnt == 2)
        cout << "Semi-Eulerian" << endl;
    else
        cout << "Non-Eulerian" << endl;

    return 0;
}