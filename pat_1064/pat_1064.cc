#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int nn;
vector<int> lchid, rchid, lnum, rnum, val;
vector<int> nums;

int getNodenum(int id)
{
    if (id==-1) return 0;
    lnum[id] = getNodenum(lchid[id]);
    rnum[id] = getNodenum(rchid[id]);
    return lnum[id]+rnum[id]+1;
}

void buildTree(int id, int st, int ed)
{
    if (id==-1) return;
    int mid = st+lnum[id];
    val[id] = nums[mid];
    buildTree(lchid[id], st, mid-1);
    buildTree(rchid[id], mid+1, ed);
}

void bfs()
{
    queue<int> qq;
    cout << val[0];
    qq.push(lchid[0]);
    qq.push(rchid[0]);
    while(!qq.empty())
    {
        if (qq.front()==-1)
        {
            qq.pop();
            continue;
        }
        cout << " " << val[qq.front()];
        qq.push(lchid[qq.front()]);
        qq.push(rchid[qq.front()]);
        qq.pop();
    }
    cout << endl;
}

int main()
{
    cin >> nn;
    nums.resize(nn);
    lchid.resize(nn, -1);
    rchid.resize(nn, -1);
    lnum.resize(nn,0);
    rnum.resize(nn,0);
    val.reserve(nn);
    for(int ii=0;ii<nn;ii++) cin >> nums[ii];
    int id=1;
    for(int ii=0;id<nn;ii++)
    {
        lchid[ii] = id++;
        if (id==nn) break;
        rchid[ii] = id++;
    }
    sort(nums.begin(), nums.end());
    getNodenum(0);
    buildTree(0,0,nn-1);
    bfs();
    return 0;
}