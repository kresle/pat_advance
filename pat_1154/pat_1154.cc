#include <vector>
#include <iostream>
#include <set>
#include <stdio.h>
using namespace std;

int nn, mm;
vector<vector<int>> edge;
vector<int> color;

int main(int argc, char const *argv[])
{
    /* code */
    cin >> nn >> mm;
    edge.resize(mm, vector<int>(2,-1));
    for(int ii=0;ii<mm;ii++)
    {
        cin >> edge[ii][0] >> edge[ii][1];
    }
    int kk;
    cin >> kk;
    for(;kk>0;kk--)
    {
        set<int> cc;
        color.resize(nn, -1);
        for(int ii=0;ii<nn;ii++)
        {
            cin >> color[ii];
            if (cc.find(color[ii])==cc.end())
            {
                cc.insert(color[ii]);
            }
        }
        bool kc = true;
        for(int ii=0;ii<mm;ii++)
        {
            if (color[edge[ii][0]]==color[edge[ii][1]])
            {
                kc = false;
                break;
            }
        }
        if (kc)
        {
            printf("%lu-coloring\n",cc.size());
        }
        else{
            cout << "No" << endl;
        }
        color.clear();
        cc.clear();
    }
    return 0;
}
