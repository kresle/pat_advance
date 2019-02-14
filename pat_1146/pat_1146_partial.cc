/**
 * 这个方法是错的，最后一个样例过不了，谁让自己没好好掌握数据结构的算法呢？
 * 举个错误样例：入度为0的结点接到最深的结点前，只要在遍历最后一层结点前访问此结点就不会有问题，但自己的算法里，其深度为1,必须在一开始就访问。
 * 似乎没法在此基础上进行修正。
 */
#include <iostream>
#include <vector>
using namespace std;

#define maxNN 1005

int nn, mm;
vector<vector<int>> parents;
vector<vector<int>> children;
vector<int> depth;
// vector<vector<bool>> connected;
vector<int> traverse;

int numBranch = 0;

int getDepth(int id)
{
    if (depth[id]!=-1) return depth[id];
    int maxPD = numBranch*maxNN, pd;
    for(auto pp: parents[id])
    {
        pd = getDepth(pp); 
        if (pd>maxPD) maxPD = pd;
    }
    depth[id] = maxPD+1;
    for(auto cc: children[id])
    {
        if (depth[cc]==-1) getDepth(cc);
    }
    return depth[id];
}

int main()
{
    cin >> nn >> mm;
    parents.resize(nn+1);
    children.resize(nn+1);
    depth.resize(nn+1, -1);
    traverse.resize(nn+1);
    int st, ed;
    for(int ii=0;ii<mm;ii++)
    {
        cin >> st >> ed;
        // connected[st][ed] = true;
        parents[ed].push_back(st);
        children[st].push_back(ed);
    }
    for(int ii=1;ii<=nn;ii++)
    {
        if (parents[ii].empty()&&depth[ii]==-1)
        {
            getDepth(ii);
            numBranch++;
        }
    }
    int kk;
    cin >> kk;
    vector<int> ans;
    for(int ii=0;ii<kk;ii++)
    {
        bool inorder = true;
        vector<int> branchDp(numBranch, 0);
        int branchId;
        for(int jj=0;jj<nn;jj++)
        {
            cin >> traverse[jj];
            if (traverse[jj]<1||traverse[jj]>nn||depth[traverse[jj]]<=0) {inorder=false;continue;}
            branchId = depth[traverse[jj]]/maxNN;
            cerr << depth[traverse[jj]] << " ";
            if (depth[traverse[jj]]>branchDp[branchId])
            {
                branchDp[branchId] = depth[traverse[jj]];
            }
            else if (depth[traverse[jj]]<branchDp[branchId]) inorder = false;
            // if (jj>0&&depth[traverse[jj]]<depth[traverse[jj-1]]) inorder = false;
        }
        cerr << ((inorder)?"Right":"Wrong") <<  endl;
        if (!inorder) ans.push_back(ii);
    }
    if (!ans.empty()) cout << ans[0];
    for(int ii=1;ii<ans.size();ii++) cout << " " << ans[ii];
    return 0;
}
