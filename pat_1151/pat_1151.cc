#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
};

unordered_map<int, TreeNode*> tree;

int nn, mm;
vector<int> inorder;
vector<int> preorder;
unordered_map<int, int> level;

TreeNode* buildTree(TreeNode* parent, int st_in, int ed_in, int st_pre, int ed_pre)
//[st,ed]
{
    if (ed_in-st_in<0) return NULL;
    int rootVal = preorder[st_pre];
    // cerr << rootVal <<":" <<  st_in << "," << ed_in <<"\t" <<  st_pre << "," << ed_pre << endl;
    int rootIdx_in = find(inorder.begin()+st_in, inorder.begin()+ed_in+1, rootVal)-inorder.begin();
    int leftLen = rootIdx_in-st_in;
    int rightLen =  (ed_in-st_in)-leftLen;
    TreeNode* root = new TreeNode(rootVal);
    root->parent = parent;
    if (leftLen>0) root->left  = buildTree(root, st_in, rootIdx_in-1, st_pre+1, st_pre+leftLen);
    if (rightLen>0) root->right = buildTree(root, rootIdx_in+1, ed_in, st_pre+leftLen+1,ed_pre);
    tree.insert(make_pair(rootVal, root));
    return root;
}

void traverse_preOrder(TreeNode* root)
//这个一定要记牢教训，只能用先序，不能用别的遍历方法
{
    if (root==NULL) return;
    // cerr << root->val << endl;
    if (root->parent==NULL)
    {
        level.insert(make_pair(root->val, 1));
    }
    else
    {
        int ll = level.find(root->parent->val)->second+1;
        level.insert(make_pair(root->val, ll));
    }
    traverse_preOrder(root->left);
    traverse_preOrder(root->right);
}

int main(int argc, char const *argv[])
{
    cin >> mm >> nn;
    inorder.resize(nn, -1);
    preorder.resize(nn, -1);
    // level.resize(nn+1,-1);
    for(int ii=0;ii<nn;ii++)
    {
        cin >> inorder[ii];
    }
    for(int ii=0;ii<nn;ii++)
    {
        cin >> preorder[ii];
    }
    // cerr << "Before build tree\n";
    TreeNode *root = buildTree(NULL, 0, nn-1, 0, nn-1);
    // cerr << "After build tree\n";
    // cerr << root->val << endl;
    traverse_preOrder(root);
    // cerr << "After Level determined\n";
    for(int ii=0;ii<mm;ii++)
    {
        int n1, n2;
        cin >> n1 >> n2;
        TreeNode *tnl=NULL, *tnh=NULL;  //tnl.level>=tnh
        auto tmp1 = tree.find(n1), tmp2 = tree.find(n2);
        int cc = (tmp1==tree.end())*3 + (tmp2==tree.end());
        switch (cc)
        {
            case 0:
            {
                // cerr << "Case 0\n";
                int l1 = level.find(n1)->second, l2 = level.find(n2)->second;
                int ll, lh;
                if (l1>=l2)
                {
                    tnl = tmp1->second;
                    tnh = tmp2->second;
                    ll = l1;
                    lh = l2;
                }
                else{
                    tnl = tmp2->second;
                    tnh = tmp1->second;
                    ll = l2;
                    lh = l1;
                }
                TreeNode *lp=tnl, *hp=tnh;
                while(ll>lh)
                {
                    lp = lp->parent;
                    ll--;
                }
                if (lp==hp)
                {
                    printf("%d is an ancestor of %d.\n", tnh->val, tnl->val);
                    break;
                }
                while(lp!=hp)
                {
                    lp=lp->parent;
                    hp=hp->parent;
                }
                printf("LCA of %d and %d is %d.\n", n1, n2, lp->val);
                break;
            }
            case 1:
            {
                // cerr << "Case 1\n";
                printf("ERROR: %d is not found.\n", n2);
                break;
            }
            case 3:
            {
                // cerr << "Case 3\n";
                printf("ERROR: %d is not found.\n", n1);
                break;
            }
            case 4:
            {
                // cerr << "Case 4\n";
                printf("ERROR: %d and %d are not found.\n", n1, n2);
                break;
            }
        }
    }
    return 0;
}
