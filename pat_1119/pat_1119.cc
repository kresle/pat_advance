#include <vector>
#include <iostream>
using namespace std;

int nn;
vector<int> preorder;
vector<int> postorder;
vector<int> inorder;

bool uniqueTree(int st_pre=0, int ed_pre=nn-1, int st_post=0, int ed_post=nn-1)
{
    // cout << st_pre << " " << ed_pre << " " << st_post << " " << ed_post << endl;
    // if (preorder[st_pre]!=postorder[ed_post]) return false;//不可建树
    if (st_pre>ed_pre)
    {
        return true;
    }
    if (st_pre == ed_pre)
    {
        inorder.push_back(preorder[st_pre]);
        return true;
    }
    if (st_pre+1 == ed_pre)
    {
        //这种情况没法唯一
        inorder.push_back(preorder[st_pre]);
        inorder.push_back(preorder[ed_pre]);
        return false;
    }
    int lst_pre = st_pre+1;
    int led_post = st_post;
    while(postorder[led_post]!=preorder[lst_pre]) led_post++;
    int llen = led_post-st_post+1;
    int rlen = ed_pre-st_pre-llen;
    bool r1, r2;
    r1 = uniqueTree(lst_pre, lst_pre+llen-1, st_post, led_post);
    inorder.push_back(preorder[st_pre]);
    r2 = uniqueTree(lst_pre+llen, ed_pre, led_post+1, ed_post-1);
    return  r1 && r2;
}

int main(int argc, char const *argv[])
{
    cin >> nn;
    preorder.resize(nn);
    postorder.resize(nn);
    for(int ii=0;ii<nn;ii++) cin >> preorder[ii];
    for(int ii=0;ii<nn;ii++) cin >> postorder[ii];
    if (uniqueTree()) cout << "Yes" << endl;
    else cout << "No" << endl;
    cout << inorder[0];
    for(int ii=1;ii<nn;ii++) cout << " " << inorder[ii];
    cout << endl;
    return 0;
}
