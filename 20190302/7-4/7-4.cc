//20:50 -> 21:36AC

// 对stringstream的用法不清楚，考场上肯定用不出来。

// 这里buildTree写得还是不错的，但是考场上写的时候，各种错误。
// 这里的真的不错，记一下。

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct treeNode
{
    int val;
    int level;
    treeNode *left;
    treeNode *right;
    treeNode *parent;
    treeNode(int iv, int il, treeNode *pp) : val(iv), left(NULL), right(NULL), parent(pp), level(il) {}
};

int nn;
map<int, treeNode *> id2node;
vector<int> inorder, postorder;
treeNode *root;
bool isFull = true;

treeNode *buildTree(int st_in, int ed_in, int st_post, int ed_post, int level, treeNode *parent)
{
    if (st_in > ed_in || st_post > ed_post)
        return NULL;
    int rootVal = postorder[ed_post];
    treeNode *cur = new treeNode(rootVal, level, parent);
    id2node[rootVal] = cur;
    int mid_in = st_in;
    while (inorder[mid_in] != rootVal)
        mid_in++;
    int llen = mid_in - st_in;
    int rlen = ed_in - mid_in;
    if (llen > 0)
        cur->left = buildTree(st_in, mid_in - 1, st_post, st_post + llen - 1, level + 1, cur);
    if (rlen > 0)
        cur->right = buildTree(mid_in + 1, ed_in, st_post + llen, ed_post - 1, level + 1, cur);
    if ((llen > 0) != (rlen > 0))
        isFull = false;
    return cur;
}

int main()
{
    cin >> nn;
    inorder.resize(nn);
    postorder.resize(nn);
    for (int ii = 0; ii < nn; ii++)
        cin >> postorder[ii];
    for (int ii = 0; ii < nn; ii++)
        cin >> inorder[ii];

    root = buildTree(0, nn - 1, 0, nn - 1, 0, NULL);

    int kk;
    cin >> kk;
    string cmd, tmp;
    int nid1, nid2;
    stringstream ss;
    while (kk--)
    {
        tmp.clear();
        bool ans;
        getline(cin >> ws, cmd);
        ss.str(cmd);
        if (cmd.find("root") != string::npos)
        {
            ss >> nid1;
            ans = root->val == nid1;
        }
        else if (cmd.find("siblings") != string::npos)
        {
            ss >> nid1 >> tmp >> nid2;
            ans = id2node.find(nid1) != id2node.end() && id2node.find(nid2) != id2node.end() && id2node[nid1]->parent == id2node[nid2]->parent;
        }
        else if (cmd.find("parent") != string::npos)
        {
            nid2 = stoi(cmd.substr(cmd.find_last_of(' ') + 1)); //child
            ss >> nid1;                                         // parent
            ans = id2node.find(nid2) != id2node.end() && id2node[nid2]->parent && id2node[nid2]->parent->val == nid1;
        }
        else if (cmd.find("left") != string::npos)
        {
            nid2 = stoi(cmd.substr(cmd.find_last_of(' ') + 1)); //parent
            ss >> nid1;                                         // child
            ans = id2node.find(nid2) != id2node.end() && id2node[nid2]->left && id2node[nid2]->left->val == nid1;
        }
        else if (cmd.find("right") != string::npos)
        {
            nid2 = stoi(cmd.substr(cmd.find_last_of(' ') + 1)); //parent
            ss >> nid1;                                         // child
            ans = id2node.find(nid2) != id2node.end() && id2node[nid2]->right && id2node[nid2]->right->val == nid1;
        }
        else if (cmd.find("level") != string::npos)
        {
            ss >> nid1 >> tmp >> nid2;
            ans = id2node.find(nid1) != id2node.end() && id2node.find(nid2) != id2node.end() && id2node[nid1]->level == id2node[nid2]->level;
        }
        else if (cmd.find("full") != string::npos)
        {
            ans = isFull;
        }
        cout << (ans ? "Yes" : "No") << endl;
    }
}