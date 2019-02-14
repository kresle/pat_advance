#include <iostream>
#include <vector>
using namespace std;

int nn;
vector<int> inorder, preorder;
int ans=0;

void postorder(int st_in=0, int ed_in=nn-1, int st_pre=0, int ed_pre=nn-1)
{
    if (ans!=0||st_in>ed_in) return;
    int rootVal = preorder[st_pre];
    int rootId_in = st_in;
    while(inorder[rootId_in]!=rootVal) rootId_in++;
    int llen = rootId_in-st_in;
    postorder(st_in, rootId_in-1, st_pre+1, st_pre+llen);
    postorder(rootId_in+1, ed_in, st_pre+llen+1, ed_pre);
    if (ans==0) ans = rootVal;
}

int main()
{
    cin >> nn;
    inorder.resize(nn);
    preorder.resize(nn);
    for(int ii=0;ii<nn;ii++) cin >> preorder[ii];
    for(int ii=0;ii<nn;ii++) cin >> inorder[ii];
    postorder();
    cout << ans;
}