#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct familyProperty
{
    int id;
    int personCnt;
    int ttlEstateCnt;
    int ttlArea;
    familyProperty(int fid) : id(fid), personCnt(0), ttlEstateCnt(0), ttlArea(0) {}
    bool operator<(familyProperty obj)
    {
        if (ttlArea * obj.personCnt != obj.ttlArea * personCnt)
            return ttlArea * obj.personCnt > obj.ttlArea * personCnt;
        else
            return id < obj.id;
    }
};

#define MAXSIZE 10000

int nn;
int parent[MAXSIZE], mEstate[MAXSIZE], area[MAXSIZE];
map<int, familyProperty *> families;
set<int> allPersons;

int findParent(int id)
{
    if (parent[id] == id)
        return id;
    else
    {
        parent[id] = findParent(parent[id]);
        return parent[id];
    }
}

void unionFamily(int vv, int uu)
{
    vv = findParent(vv);
    uu = findParent(uu);
    if (vv == uu)
        return;
    if (vv > uu)
    {
        parent[vv] = uu;
    }
    else
    {
        parent[uu] = vv;
    }
}

int main()
{
    fill(mEstate, mEstate+MAXSIZE, 0);
    fill(area, area+MAXSIZE, 0);
    iota(parent, parent+MAXSIZE, 0);

    cin >> nn;
    int pp[nn];
    int fat, mot, kkid, kid_id;
    for (int ii = 0; ii < nn; ii++)
    {
        cin >> pp[ii] >> fat >> mot >> kkid;
        allPersons.insert(pp[ii]);
        if (fat!=-1) allPersons.insert(fat), unionFamily(pp[ii], fat);
        if (mot!=-1) allPersons.insert(mot), unionFamily(pp[ii], mot);
        while (kkid--)
        {
            cin >> kid_id;
            unionFamily(pp[ii], kid_id);
            allPersons.insert(kid_id);
        }
        cin >> mEstate[pp[ii]] >> area[pp[ii]];
    }

    familyProperty *tmp;
    for (int ii = 0; ii < nn; ii++)
    {
        int pid = findParent(pp[ii]);
        if (families.find(pid) == families.end())
        {
            tmp = new familyProperty(pid);
            families.insert(make_pair(pid, tmp));
        }
        families[pid]->ttlArea += area[pp[ii]];
        families[pid]->ttlEstateCnt += mEstate[pp[ii]];
    }
    for(auto pp: allPersons)
    {
        int pid = findParent(pp);
        families[pid]->personCnt++;
    }

    vector<familyProperty *> fpv;
    for (auto ff : families)
    {
        fpv.push_back(ff.second);
    }
    sort(fpv.begin(), fpv.end(), [](familyProperty *ll, familyProperty *rr) { return *ll < *rr; });

    cout << fpv.size() << endl;
    for (int ii = 0; ii < fpv.size(); ii++)
    {
        printf("%04d %d %.3f %.3f\n", fpv[ii]->id, fpv[ii]->personCnt,
               ((float)fpv[ii]->ttlEstateCnt) / fpv[ii]->personCnt,
               ((float)fpv[ii]->ttlArea) / fpv[ii]->personCnt);
    }

    return 0;
}