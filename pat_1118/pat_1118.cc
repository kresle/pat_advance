#include <iostream>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

#define MAXSIZE 10001

int nn;
int parent[MAXSIZE], ranking[MAXSIZE];
set<int> birdIds, treeBirds;

// parent[set_id] = set_id
// parent[nonSet_id] = par_id
int findParent(int id)
{
    if (id==parent[id]) return id;
    else
    {
        parent[id] = findParent(parent[id]);
        return parent[id];
    }
}

void unionSet(int vv, int uu)
{
    vv = findParent(vv);
    uu = findParent(uu);
    if (vv==uu) return;
    if (ranking[vv]>ranking[uu])
    {
        parent[uu] = vv;
    }
    else
    {
        parent[vv] = uu;
        if (ranking[vv]==ranking[uu]) ranking[uu]++;
    }
    
}

int main()
{
    fill(ranking, ranking+MAXSIZE, 0);
    iota(parent, parent+MAXSIZE, 0);

    cin >> nn;
    int photo[nn];
    for(int ii=0;ii<nn;ii++)
    {
        int kk, uu=0, vv=0;
        cin >> kk;
        while(kk--)
        {
            cin >> uu;
            birdIds.insert(uu);
            if (vv!=0)
            {
                unionSet(uu, vv);
            }
            vv = uu;
        }
        photo[ii] = uu;
    }
    for(int ii=0;ii<nn;ii++)
    {
        treeBirds.insert(findParent(photo[ii]));
    }
    cout << treeBirds.size() << " " << birdIds.size() << endl;
    int kk, uu, vv;
    cin >> kk;
    while(kk--)
    {
        cin >> uu >>vv;
        cout << ((findParent(uu)==findParent(vv))?"Yes":"No") << endl;
    }
    return 0;
}