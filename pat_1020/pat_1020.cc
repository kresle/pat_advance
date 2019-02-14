#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int nn;
vector<int> postorderT;
vector<int> inorderT;
// vector<int> leftID;
// vector<int> rightID;
/**
 * 这道题很贱，看给的样例会让你觉得结点的编号就是[1..n],但实际上却不是，是任意的。
 */ 

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

TreeNode* buildTree(int preP, int surP, int preI, int surI)
{
    if (preP>surP || preI>surI || surP>=nn || surI>=nn) return NULL;
    TreeNode* root = new TreeNode(postorderT[surP]);
    // int root = postorderT[surP];
    int ridI = preI;
    for(;ridI<=surI;ridI++)
    {
        if (inorderT[ridI]==root->val) break;
    }
    if (ridI>surI) {cerr << "wrongInput";return NULL;}
    int leftLen=ridI-preI, rightLen=surI-ridI;
    if (leftLen>0) {root->left = buildTree(preP, preP+leftLen-1, preI, ridI-1);}
    if (rightLen>0) {root->right = buildTree(preP+leftLen, surP-1, ridI+1, surI);}
    return root;
}

void bfs(TreeNode* root)
{
    if (!root) return;
    queue<TreeNode*> qq;
    cout << root->val;
    qq.push(root->left);
    qq.push(root->right);
    while(!qq.empty())
    {
        if (qq.front()==NULL)
        {
            qq.pop();
            continue;
        }
        cout << " " << qq.front()->val;
        qq.push(qq.front()->left);
        qq.push(qq.front()->right);
        qq.pop();
    }
}

int main(int argc, char const *argv[])
{
    cin >> nn;

    postorderT.resize(nn,-1);
    inorderT.resize(nn,-1);
    // leftID.resize(nn+1, -1);
    // rightID.resize(nn+1, -1);

    for(int ii=0;ii<nn;ii++) cin >> postorderT[ii];
    for(int ii=0;ii<nn;ii++) cin >> inorderT[ii];

    TreeNode* root = buildTree(0,nn-1,0,nn-1);

    bfs(root);

    return 0;
}
