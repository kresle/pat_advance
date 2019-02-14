#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int vv): val(vv), left(NULL), right(NULL) {}
};

int nn;
vector<int> inorder, postorder, zigzagOrder;
TreeNode* root;

TreeNode* buildTreeInPost(int st_in=0, int ed_in=nn-1, int st_post=0, int ed_post=nn-1)
{
    if (st_in>ed_in) return NULL;
    int rootVal = postorder[ed_post];
    TreeNode* root = new TreeNode(rootVal);
    int root_in = st_in;
    while(inorder[root_in]!=rootVal) root_in++;
    int llen = root_in - st_in;
    root->left = buildTreeInPost(st_in, root_in-1, st_post, st_post+llen-1);
    root->right = buildTreeInPost(root_in+1, ed_in,st_post+llen, ed_post-1);
    return root;
}

void zigzagTraverse(TreeNode* root)
{
    stack<TreeNode*> st;
    zigzagOrder.push_back(root->val);
    st.push(root->right);
    st.push(root->left);
    bool pushLeftFirst = true;
    while(!st.empty())
    {
        stack<TreeNode*> st_lvl;
        while(!st.empty())
        {
            if (st.top()==NULL)
            {
                st.pop();
                continue;
            }
            zigzagOrder.push_back(st.top()->val);
            if (pushLeftFirst) {
                st_lvl.push(st.top()->left);
                st_lvl.push(st.top()->right);
            }
            else {
                st_lvl.push(st.top()->right);
                st_lvl.push(st.top()->left);
            }
            st.pop();
        }
        st = st_lvl;
        pushLeftFirst = !pushLeftFirst;
    }
    cout << zigzagOrder[0];
    for(int ii=1;ii<nn;ii++)
    {
        cout <<" " << zigzagOrder[ii];
    }
    cout << endl;
}

int main()
{
    cin >> nn;
    inorder.resize(nn);
    postorder.resize(nn);
    for(int ii=0;ii<nn;ii++) cin >> inorder[ii];
    for(int ii=0;ii<nn;ii++) cin >> postorder[ii];
    root = buildTreeInPost();
    cerr << "Tree built" << endl;
    zigzagTraverse(root);
    return 0;
}