#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>
using namespace std;

#define MAXSIZE 1001

int nn;
vector<int> personInterest;

//下面这些量是针对兴趣的
int parent[MAXSIZE], ranking[MAXSIZE];
bool valid[MAXSIZE];

map<int, int> cluster;

int getParent(int id)
{
    if (parent[id] == id)
        return id;
    else
    {
        parent[id] = getParent(parent[id]);
        return parent[id];
    }
}

void unionSet(int vv, int uu)
{
    vv = getParent(vv);
    uu = getParent(uu);
    if (vv == uu)
        return;
    if (ranking[uu] > ranking[vv])
    {
        parent[vv] = uu;
    }
    else
    {
        parent[uu] = vv;
        if (ranking[vv] == ranking[uu])
        {
            ranking[vv]++;
        }
    }
}

int main()
{
    iota(parent, parent + MAXSIZE, 0);
    fill(ranking, ranking + MAXSIZE, 0);
    fill(valid, valid + MAXSIZE, false);

    cin >> nn;
    personInterest.reserve(nn), personInterest.resize(nn);

    int inst, inst1, inst2, kk;
    char cc;
    for (int ii = 0; ii < nn; ii++)
    {
        cin >> kk >> cc;
        if (kk > 0)
            cin >> inst1;
        personInterest[ii] = inst1;
        valid[inst1] = true;
        for (int jj = 1; jj < kk; jj++)
        {
            cin >> inst2;
            valid[inst2] = true;
            unionSet(inst1, inst2);
        }
    }
    for (int ii = 1; ii < MAXSIZE; ii++)
    {
        int setId;
        if (valid[ii])
        {
            setId = getParent(ii);
            if (cluster.find(setId) == cluster.end())
            {
                cluster.insert(make_pair(setId, 0));
            }
        }
    }
    for(int ii=0;ii<nn;ii++)
    {
        cluster[getParent(personInterest[ii])]++;
    }
    vector<int> ans;
    for (auto pp : cluster)
    {
        ans.push_back(pp.second);
    }
    sort(ans.rbegin(), ans.rend());
    cout << ans.size() << endl;
    cout << ans.front();
    for (int ii = 1; ii < ans.size(); ii++)
        cout << " " << ans[ii];
    cout << endl;
    return 0;
}