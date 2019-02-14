#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
using namespace std;

struct dataItem
{
    int order_id;
    int val;
    int addr;
    int next;
};

int nn, kk, st_id;
map<int, int> nextId, curVal;
vector<dataItem *> nodeVals;
vector<int> address_inorder;

int main()
{
    cin >> st_id >> nn >> kk;
    int vv, uu, val;
    for (int ii = 0; ii < nn; ii++)
    {
        cin >> vv >> val >> uu;
        nextId.insert(make_pair(vv, uu));
        curVal.insert(make_pair(vv, val));
    }
    int addr = st_id;
    nn = 0;
    while (addr != -1)
    {
        address_inorder.push_back(addr);
        addr = nextId[addr];
        nn++;
    }
    for (int ii = 0; ii < nn; ii++)
    {
        dataItem *obj = new dataItem();
        obj->addr = address_inorder[ii];
        obj->val = curVal[obj->addr];
        obj->order_id = ii;
        nodeVals.push_back(obj);
    }
    sort(nodeVals.begin(), nodeVals.end(), [](dataItem *ll, dataItem *rr) {
        if ((ll->val < 0 && rr->val < 0) || (ll->val > kk && rr->val > kk) || (ll->val >= 0 && ll->val <= kk && rr->val >= 0 && rr->val <= kk))
            return ll->order_id < rr->order_id;
        return ll->val < rr->val;
    });
    for (int ii = 0; ii < nn; ii++)
    {
        if (ii < nn - 1)
            printf("%05d %d %05d\n", nodeVals[ii]->addr, nodeVals[ii]->val, nodeVals[ii + 1]->addr);
        else
            printf("%05d %d -1\n", nodeVals[ii]->addr, nodeVals[ii]->val);
    }
    return 0;
}