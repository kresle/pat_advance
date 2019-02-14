#include <iostream>
#include <vector>
using namespace std;


int nn, mm, kk;
vector<int> inDegree_bk;
vector<vector<int>> children;
vector<int> traverse;

bool isTopo()
{
    vector<int> ind = inDegree_bk;
    bool ans = true;
    for(int ii=0;ii<nn;ii++)
    {
        int vv = traverse[ii];
        if (ind[vv]!=0)
        {
            ans = false;
            break;
        }
        for(auto uu: children[vv])
        {
            ind[uu]--;
        }
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> mm;
    inDegree_bk.resize(nn+1,0);
    children.resize(nn+1);
    traverse.resize(nn);
    int st, ed;
    for(int ii=0;ii<mm;ii++)
    {
        cin >> st >> ed;
        children[st].push_back(ed);
        inDegree_bk[ed]++;
    }
    cin >> kk;
    vector<int> ans;
    for(int ii=0;ii<kk;ii++)
    {
        for(int jj=0;jj<nn;jj++) cin >> traverse[jj];
        if (!isTopo()) ans.push_back(ii);
    }
    if (!ans.empty()) cout << ans[0];
    for(int ii=1;ii<ans.size();ii++) cout << " " << ans[ii];
    return 0;
}
