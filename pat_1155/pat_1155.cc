#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int nn;

vector<int> val;    //
vector<int> lchid;   //lchid[id]: id的左子树结点id
vector<int> rchid;  //
vector<int> path;

bool maxHeap = true;
bool minHeap = true;

void dfs(int id)
{
    if (lchid[id]==-1||id>=nn)//叶结点
    {
        for(auto pp: path)
            cout << pp << " ";
        cout << val[id] << endl;
    }
    if (!path.empty())
    {
        if (val[id]>path.back()) maxHeap = false;
        if (val[id]<path.back()) minHeap = false;
    }
    path.push_back(val[id]);
    if (rchid[id]!=-1) dfs(rchid[id]);
    if (lchid[id]!=-1) dfs(lchid[id]);
    path.pop_back();
}

int main()
{
    cin >> nn;
    val   = vector<int> (nn, -1);
    lchid  = vector<int> (nn, -1);
    rchid = vector<int> (nn, -1);
    for(int ii=0;ii<nn;ii++)
    {
        cin >> val[ii];
    }
    int depth = log(nn)/log(2)+1;
    for(int dd=1;dd<=depth-1;dd++)
    {
        // int noOfNext = pow(2,dd);   //下一层有多少个结点
        // int nid=pow(2,dd+1)-1;        //下一层从多少号开始
        int noOfCur  = pow(2,dd-1); //本层有多少个结点
        int cid=pow(2,dd-1)-1;        //本层从多少号开始
        int nid=cid+noOfCur;        //下层从多少号开始
        // cout << cid << "," << nid<< endl;
        for(int jj=cid;jj<cid+noOfCur&&nid<nn;jj++)
        {
            lchid[jj] = nid++;
            if(nid>=nn) break;
            rchid[jj] = nid++;
            if(nid>=nn) break;
        }
    }
    // if (true)
    // {
    //     int dd = depth;
    //     int noOfCur  = pow(2,dd-1); //本层有多少个结点
    //     int cid=pow(2,dd)-1;        //本层从多少号开始
    //     int noOfPre  = pow(2,dd-2); //上一层有多少个结点
    //     int pid=cid-noOfPre;
    //     for(int ii=cid;ii<nn;ii++)
    //     {
    //         while(val[ii]<)
    //     }
    // }

    // for(auto pp: lchid) cout << pp << " "; cout << endl;
    // for(auto pp: rchid) cout << pp << " "; cout << endl;

    dfs(0);
    if (maxHeap) cout << "Max Heap";
    else if (minHeap) cout << "Min Heap";
    else cout << "Not Heap";

    return 0;
}