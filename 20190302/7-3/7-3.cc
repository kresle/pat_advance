// 不难，就是条件多，要细心，每个条件都一定要写对
// 比如no more than, more than这种
// 再比如short call的判断依据是total duration of calls，而不是单次call.
// 还有回电的判断要有。
// 一旦所有的都找到了，后面的并查集是很简单的。

#include <iostream>
#include <set>
#include <vector>
#include <numeric>
using namespace std;

int nn, mm, kk;
vector<vector<int>> callDuration;
vector<int> allFrauds;
vector<int> parent;
set<int> gangs;
vector<vector<int>> gangMember;

int findParent(int id)
{
    if (id!=parent[id])
        parent[id] = findParent(parent[id]);
    return parent[id];
}

void unionSet(int vv, int uu)
{
    uu = findParent(uu);
    vv = findParent(vv);
    if (uu==vv) return;
    if (uu<vv)
        parent[vv] = uu;
    else
        parent[uu] = vv;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> kk >> nn >> mm;
    callDuration.resize(nn+1, vector<int>(nn+1, 0));
    int cc, rr, dd;
    for(int ii=0;ii<mm;ii++)
    {
        cin >> cc >> rr >> dd;
        callDuration[cc][rr] += dd;
    }
    for(int ii=1;ii<=nn;ii++)
    {
        int shortCallCnt =0;
        int callBackCnt = 0;
        for(int jj=1;jj<=nn;jj++)
        {
            if (callDuration[ii][jj]>0 && callDuration[ii][jj]<=5) //别忘了第一个条件
            {
                shortCallCnt++;
                if (callDuration[jj][ii]) callBackCnt++;
            }
        }
        if (shortCallCnt>kk && callBackCnt*5<=shortCallCnt) allFrauds.push_back(ii);
    }

    parent.resize(nn+1);
    iota(parent.begin(), parent.end(),0);
    for(int ii=0;ii<allFrauds.size();ii++)
        for(int jj=ii+1;jj<allFrauds.size();jj++)
            if (callDuration[allFrauds[ii]][allFrauds[jj]] && callDuration[allFrauds[jj]][allFrauds[ii]])
                unionSet(allFrauds[ii], allFrauds[jj]);
    for(auto ff: allFrauds)
    {
        findParent(ff);
        if (gangs.find(parent[ff])==gangs.end())
        {
            gangs.insert(parent[ff]);
        }
    }
    gangMember.resize(nn+1);
    for(auto ff: allFrauds)
        gangMember[parent[ff]].push_back(ff);
    for(auto gg: gangs)
    {
        cout << gangMember[gg][0];
        for(int ii=1;ii<gangMember[gg].size();ii++)
            cout << " " << gangMember[gg][ii];
        cout << endl;
    }
    if (gangs.empty()) cout << "None" << endl;
}