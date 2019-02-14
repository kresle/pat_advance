#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

int nn;
int mm;
vector<int> nums;
vector<bool> isRed;
bool noAdjacentRed, eqRootBlackHeight;
int blackHeight;

struct TreeNode {
    int val;
    bool isRed;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL), isRed(false) {}
};

TreeNode* buildTree(int st_idx, int ed_idx)
{
    if (st_idx>ed_idx)
    {
        return NULL;
    }
    TreeNode *root = new TreeNode(nums[st_idx]);
    root->isRed = isRed[st_idx];
    // if (isRed[st_idx]) cerr << nums[st_idx] << "is red" << endl;
    int right_stIdx = st_idx+1;
    while(right_stIdx<=ed_idx && nums[right_stIdx]<nums[st_idx]) right_stIdx++;
    root->left = buildTree(st_idx+1, right_stIdx-1);
    root->right = buildTree(right_stIdx, ed_idx);
    return root;
}

void dfs(TreeNode* root, int height)
{
    if (root==NULL)
    {
        // cerr << "Leaf black depth=" << height << endl;
        if (blackHeight==0)
            blackHeight = height;
        else
        {
            if (blackHeight!=height)
                eqRootBlackHeight = false;
        }
        return;
    }
    // cerr << root->val << endl;
    if (root->isRed)
    {
        if ((root->left&&root->left->isRed)||(root->right&&root->right->isRed)) {
            // cerr << root->val << " and its child has same red color" << endl;
            noAdjacentRed=false;
            return;
        }
        dfs(root->left, height);
        dfs(root->right, height);
    }
    else
    {
        dfs(root->left, height+1);
        dfs(root->right, height+1);
    }
    free(root);
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

int main(int argc, char const *argv[])
{
    /* code */
    cin >> nn;
    for(int ii=0;ii<nn;ii++)
    {
        nums.clear();isRed.clear();
        cin >> mm;
        nums.resize(mm, 0);
        isRed.resize(mm, false);
        for(int jj=0;jj<mm;jj++)
        {
            cin >> nums[jj];
            if (nums[jj]<0)
            {
                nums[jj] = -nums[jj];
                isRed[jj] = true;
            }
        }
        TreeNode *root = buildTree(0,mm-1);
        if (!root) {
            cerr << "built error\n";
            continue;
        }
        if (root->isRed) {cout << "No\n";continue;}
        noAdjacentRed = true;
        eqRootBlackHeight = true;
        blackHeight = 0;
        dfs(root, 0);
        // cerr << noAdjacentRed << " " << eqRootBlackHeight << endl;
        if (noAdjacentRed&&eqRootBlackHeight) cout << "Yes\n"; else cout << "No\n";
    }
    return 0;
}
