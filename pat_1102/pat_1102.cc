#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> lchid, rchid, pid;
int nn, rootId;
vector<int> ans;

void inverted_bfs()
{
    cout << rootId;
    queue<int> qq;
    qq.push(rchid[rootId]);
    qq.push(lchid[rootId]);
    while(!qq.empty())
    {
        if (qq.front()==-1)
        {
            qq.pop();
            continue;
        }
        cout << " " << qq.front();
        qq.push(rchid[qq.front()]);
        qq.push(lchid[qq.front()]);
        qq.pop();
    }
    cout << endl;
}

void inverted_inorder(int id)
{
    if (id==-1) return;
    inverted_inorder(rchid[id]);
    ans.push_back(id);
    inverted_inorder(lchid[id]);
}

int ip2num(string ss)
{
    if (ss[0]=='-') return -1;
    return stoi(ss);
}

int main(int argc, char const *argv[])
{
    cin >> nn;
    lchid.reserve(nn), lchid.resize(nn, -1);
    rchid.reserve(nn), rchid.resize(nn, -1);
    pid.reserve(nn), pid.resize(nn, -1);
    ans.reserve(nn);
    string ll, rr;
    int lid, rid;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> ll >> rr;
        lid = ip2num(ll);
        rid = ip2num(rr);
        lchid[ii] = lid;
        rchid[ii] = rid;
        if (lid!=-1) pid[lid]=ii;
        if (rid!=-1) pid[rid]=ii;
    }
    rootId = find(pid.begin(), pid.end(), -1) - pid.begin();
    inverted_bfs();
    inverted_inorder(rootId);
    cout << ans.front();
    for(int ii=1;ii<ans.size();ii++) cout << " " << ans[ii];cout << endl;
    return 0;
}
