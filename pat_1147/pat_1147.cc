#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mm, nn;
int val[1000];
// int parent[1000];
int lchid[1000];
int rchid[1000];

void calcRelationship()
{
    // for(int ii=0;ii*2+1<nn&&(ii+1)*2<nn;ii++)
    // for(int ii=0;(ii+1)*2<nn;ii++)
    int id=1;
    for(int ii=0;id<nn;ii++)
    {
        lchid[ii] = id++;
        if (id>=nn) break;
        rchid[ii] = id++;
    }
}

bool isMaxHeap(int root)
{
    if (lchid[root]==0&&rchid[root]==0) return true;
    if (lchid[root]==0) return val[root] >= val[rchid[root]] && isMaxHeap(rchid[root]);
    if (rchid[root]==0) return val[root] >= val[lchid[root]] && isMaxHeap(lchid[root]);
    return val[root]>=val[lchid[root]] && val[root]>=val[rchid[root]] && isMaxHeap(lchid[root]) && isMaxHeap(rchid[root]);
}

bool isMinHeap(int root)
{
    if (lchid[root]==0&&rchid[root]==0) return true;
    if (lchid[root]==0) return val[root] <= val[rchid[root]] && isMinHeap(rchid[root]);
    if (rchid[root]==0) return val[root] <= val[lchid[root]] && isMinHeap(lchid[root]);
    return val[root]<=val[lchid[root]] && val[root]<=val[rchid[root]] && isMinHeap(lchid[root]) && isMinHeap(rchid[root]);
}

int checkIfHeap()
/**
 * -1:false; 0:minHeap; 1:maxHeap;
 */
{
    if (isMinHeap(0)) {cout << "Min Heap" << endl;return 0;}
    if (isMaxHeap(0)) {cout << "Max Heap" << endl;return 1;}
    cout << "Not Heap" << endl;
    return -1;
}

void postOrder(int id)
{
    if (id==0||id>=nn) return;
    // if (lchid[id]!=0) 
    postOrder(lchid[id]);
    // if (rchid[id]!=0) 
    postOrder(rchid[id]);
    cout << val[id] << " ";
}

int main(int argc, char const *argv[])
{
    cin >> mm >> nn;
    calcRelationship();
    while(mm--)
    {
        for(int ii=0;ii<nn;ii++) cin >> val[ii];
        checkIfHeap();
        postOrder(lchid[0]);
        postOrder(rchid[0]);
        cout << val[0] << endl;
        // postOrder(0);cout<<endl;
    }
    return 0;
}
