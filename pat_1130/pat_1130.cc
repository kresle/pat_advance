#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int nn, root_id;
vector<int> lchid, rchid;
vector<string> ndata;
string ans;

string findAns(int id)
{
    if (id < 0)
        return "";
    if (lchid[id] <0 && rchid[id] < 0)
        return ndata[id];
    return "(" + findAns(lchid[id]) + ndata[id] + findAns(rchid[id]) + ")";
}

int main()
{
    cin >> nn;
    lchid.reserve(nn), lchid.resize(nn, -1);
    rchid.reserve(nn), rchid.resize(nn, -1);
    ndata.reserve(nn), ndata.resize(nn);
    bool hasParent[nn];
    fill(hasParent, hasParent + nn, false);
    for (int ii = 0; ii < nn; ii++)
    {
        cin >> ndata[ii] >> lchid[ii] >> rchid[ii];
        lchid[ii]--, rchid[ii]--;
        if (lchid[ii] >= 0)
            hasParent[lchid[ii]] = true;
        if (rchid[ii] >= 0)
            hasParent[rchid[ii]] = true;
    }
    root_id = find(hasParent, hasParent + nn, false) - hasParent;
    ans = findAns(root_id);
    cout << (nn>1?ans.substr(1, ans.size()-2):ans) << endl;
    return 0;
}