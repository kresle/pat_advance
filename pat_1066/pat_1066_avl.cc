#include <iostream>
#include <vector>
#include <stdio.h>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    // TreeNode(int x, int dp) : val(x), left(NULL), right(NULL), parent(NULL), height(dp) {}
    TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL), height(1) {}
};

int nn;
vector<int> nums;

TreeNode *root;

int height(TreeNode* node){ return (node==NULL)?0:node->height;}
int getBalance(TreeNode* node) { return (node==NULL)?0:height(node->left)-height(node->right);}

TreeNode* leftRotate(TreeNode* y)
/**
 * 真的很奇妙，更新x,y高度的时候，顺序非常重要！！！！！！！
 */
{
    TreeNode *x = y->right;
    TreeNode *B = x->left;
    x->left = y;
    y->right = B;
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    return x;
}
TreeNode* rightRotate(TreeNode* x)
/**
 * 真的很奇妙，更新x,y高度的时候，顺序非常重要！！！！！！！
 */
{
    TreeNode *y = x->left;
    TreeNode *B = y->right;
    x->left = B;
    y->right = x;
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    return y;
}

TreeNode* insertNode(TreeNode *root, int val)
/**
 * 插入一个值，返回操作之后的根结点，并且保证此树是平衡的。
 * root就是树的根结点，这样才能保证每一步都是平衡的
*/
{
    if (root==NULL)
    {
        return new TreeNode(val);
    }
    if (root->val>val)
    {
        root->left = insertNode(root->left, val);
    }
    else{
        root->right = insertNode(root->right, val);
    }
    root->height = 1+ max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if (balance>1)
    {
        if (getBalance(root->left)<0) {root->left = leftRotate(root->left);}
        root = rightRotate(root);
    }
    if (balance<-1)
    {
        if (getBalance(root->right)>0) {root->right = rightRotate(root->right);}
        root = leftRotate(root);
    }
    return root;
}

void preOrder(TreeNode* root, int depth=1)
{
    if (root!=NULL)
    {
        printf("[%d]: %d\n", depth, root->val);
        preOrder(root->left, depth+1);
        preOrder(root->right, depth+1);
    }
}

void inOrder(TreeNode* root, int depth=1)
{
    if (root!=NULL)
    {
        inOrder(root->left, depth+1);
        printf("[%d]: %d\n", depth, root->val);
        inOrder(root->right, depth+1);
    }
}

void bfs(TreeNode* root)
{
    if (root==NULL) return;
    cout << root->val;
    queue<TreeNode*> qq;
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
    cout << endl;
}

int main(int argc, char const *argv[])
{
    cin >> nn;
    nums.resize(nn);
    for(int ii=0;ii<nn;ii++) cin >> nums[ii];
    root = new TreeNode(nums[0]);

    TreeNode *tmp, *tmproot;
    for(int ii=1;ii<nn;ii++)
    {
        // tmp = new TreeNode(nums[ii]);
        // tmproot = root;
        // while
        root = insertNode(root, nums[ii]);
    }
    // bfs(root);
    // cout << ((checkIfComplete(root))?"YES":"NO");
    cout << root->val;
    return 0;
}
