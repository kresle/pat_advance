#include <vector>
#include <iostream>
#include <map>
#include <stdio.h>
using namespace std;

struct TreeNode
{
    int val;
    int depth;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int vv): val(vv), parent(NULL), left(NULL), right(NULL), depth(0) {};
};

int mm, nn;
map<int, TreeNode*> id2node;
vector<int> preorder;
TreeNode* root;

TreeNode* buildTree(int st, int ed, int depth=0)
{
    if (st>ed) return NULL;
    TreeNode* node = new TreeNode(preorder[st]);
    id2node.insert(make_pair(preorder[st], node));
    node->depth = depth;
    int id_right=st+1;
    while(preorder[id_right]<preorder[st]&&id_right<=ed) id_right++;
    node->left = buildTree(st+1, id_right-1, depth+1);
    if (node->left) node->left->parent = node;
    node->right = buildTree(id_right, ed, depth+1);
    if (node->right) node->right->parent = node;
    return node;
}

void LCA(int k1, int k2)
{
    auto it1 = id2node.find(k1);
    auto it2 = id2node.find(k2);
    int cc = (it1 == id2node.end())*2 + (it2 == id2node.end());
    if (cc==1) printf("ERROR: %d is not found.\n", k2);
    if (cc==2) printf("ERROR: %d is not found.\n", k1);
    if (cc==3) printf("ERROR: %d and %d are not found.\n", k1, k2);
    if (cc!=0) return;
    TreeNode *tn1 = it1->second, *tn2 = it2->second, *tmp;
    //保证tn1是更靠近根结点的那个
    if (tn1->depth>tn2->depth) {tmp=tn2;tn2=tn1;tn1=tmp;}
    // if (tn1->parent==NULL) printf("%d is an ancestor of %d.\n", tn1->val, tn2->val);
    tmp = tn2;
    while(tmp->depth>tn1->depth)
    {
        tmp = tmp->parent;
    }
    if (tmp==tn1) {printf("%d is an ancestor of %d.\n", tn1->val, tn2->val);return;}
    while(tn1!=tmp)
    {
        tn1 = tn1->parent;
        tmp = tmp->parent;
    }
    printf("LCA of %d and %d is %d.\n", k1, k2, tn1->val);
}

void inorder(TreeNode* root)
{
    if (root==NULL) return;
    inorder(root->left);
    cerr << root->val<< ":" << root->depth << " ";
    inorder(root->right);
}

int main()
{
    int vv, uu;
    cin >> mm >> nn;
    preorder.resize(nn);
    for(int ii=0;ii<nn;ii++)
    {
        cin >> preorder[ii];
    }
    root = buildTree(0, nn-1);
    for(int ii=0;ii<mm;ii++)
    {
        cin >> uu >> vv;
        LCA(uu,vv);
    }
    return 0;
}