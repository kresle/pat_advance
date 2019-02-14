#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    int depth;
    TreeNode(int vv): val(vv), left(NULL), right(NULL), depth(0) {}
};

int nn;
vector<TreeNode*> nodes;
vector<int> values;
TreeNode* root;
int depth=0;

void buildTree()
{
    nodes.resize(nn);
    root = new TreeNode(values[0]);
    nodes[0] = root;
    TreeNode *pp, *tmp;
    for(int ii=1;ii<nn;ii++)
    {
        pp = root;
        tmp = pp;
        while(tmp!=NULL)
        {
            pp = tmp;
            if (values[ii]>tmp->val)
            {
                tmp = tmp->right;
            }
            else
            {
                tmp = tmp->left;
            }
        }
        if (values[ii]>pp->val)
        {
            pp->right = new TreeNode(values[ii]);
            pp->right->depth = pp->depth+1;
            if (pp->right->depth>depth) depth = pp->right->depth;
            nodes[ii] = pp->right;
        }
        else{
            pp->left = new TreeNode(values[ii]);
            pp->left->depth = pp->depth+1;
            if (pp->left->depth>depth) depth = pp->left->depth;
            nodes[ii] = pp->left;
        }
    }
}

int main()
{
    cin >> nn;
    values.resize(nn);
    for(int ii=0;ii<nn;ii++)
    {
        cin >> values[ii];
    }
    buildTree();
    int n1=0, n2=0;
    for(int ii=0;ii<nn;ii++)
    {
        if (nodes[ii]->depth==depth) n1++;
        if (nodes[ii]->depth==depth-1) n2++;
    }
    cout << n1 << " + " << n2 << " = " << n1+n2 << endl;
    return 0;
}

