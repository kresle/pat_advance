#include <iostream>
#include <vector>
#include <stdio.h>
#include <queue>
using namespace std;

int nn;
vector<int> leftID;
vector<int> rightID;
vector<int> parent;
bool isComplete;
int lastID;

void bfs(int root)
{
    queue<int> qq;
    qq.push(root);
    bool nullEncountered = false;
    while(!qq.empty())
    {
        if (qq.front()==-1)
        {
            qq.pop();
            nullEncountered = true;
            continue;
        }
        lastID = qq.front();
        if (nullEncountered) {isComplete = false;}
        qq.push(leftID[qq.front()]);
        qq.push(rightID[qq.front()]);
        qq.pop();
    }
}

int main(int argc, char const *argv[])
{
    cin >> nn;
    leftID.resize(nn, -1);
    rightID.resize(nn, -1);
    parent.resize(nn, -1);
    for(int ii=0;ii<nn;ii++)
    {
        string ll, rr;
        cin >> ll >> rr;
        if (ll[0]!='-') {leftID[ii] = stoi(ll);parent[stoi(ll)]=ii;}
        if (rr[0]!='-') {rightID[ii] = stoi(rr);parent[stoi(rr)]=ii;}
    }
    int rootID = 0;
    for(;rootID<nn;rootID++)
    {
        if (parent[rootID]==-1&&(leftID[rootID]!=-1||rightID[rootID]!=-1)) break;
    }
    isComplete = true;
    lastID = -1;
    bfs(rootID);
    cout << ((isComplete)?"YES ":"NO ") << ((isComplete)?lastID:rootID);
    return 0;
}
