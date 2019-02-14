#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <stdio.h>
using namespace std;

int cap, nn, sp, mm;
vector<int> inventory;
vector<vector<int>> ee;
vector<vector<int>> pre;
vector<int> dist;
vector<int> path, tmppath;
int maxPickup = INT32_MIN;
int minNeed = UINT16_MAX;

void dfs(int vv)
{
    // cout << vv << "<-";
    tmppath.push_back(vv);
    if (vv==0){
        //这里有问题，回程不过再在车站停，所以只能在到sp的途中就把所有的都填到half perfect.
        int pickup = 0, need=0;
        // for(auto uu: tmppath) pickup+=inventory[uu];
        for(int ii=tmppath.size()-1;ii>=0;ii--)
        {
            if (inventory[tmppath[ii]]<0) {
                //从pickup里来填一部分。不足的部分再++need。要判断pickup与inventory的大小关系
                if (pickup+inventory[tmppath[ii]]>=0)//pickup够填
                {
                    pickup+=inventory[tmppath[ii]];
                }
                else{//pickup不够填。
                    need += -(pickup+inventory[tmppath[ii]]);
                    pickup=0;
                }
            }
            if (inventory[tmppath[ii]]>0){
                pickup += inventory[tmppath[ii]];
            }
            // printf("Node %d: inventory=%d, pickup=%d, need=%d\n", tmppath[ii], inventory[tmppath[ii]], pickup, need);
        }
        // if (pickup>maxPickup){
        //     maxPickup = pickup;
        //     path = tmppath;
        // }
        if (need<minNeed)
        {
            minNeed = need;
            path = tmppath;
            maxPickup = pickup;
        }
        else if (need == minNeed && pickup<maxPickup)   //这个情形，自己一直没注意到。
        {
            maxPickup = pickup;
            path = tmppath;
        }
    }
    else
    {
        for(int ii=pre[vv].size()-1;ii>=0;ii--)
        {
            dfs(pre[vv][ii]);
            //不删pre好像也可以
        }
    }
    tmppath.pop_back();
}

void findShortestDist()
{
    dist = vector<int>(nn+1, UINT16_MAX);
    dist[0] = 0;
    vector<bool> visited(nn+1, false);
    pre.resize(nn+1);
    // pre = vector<vector<int>> (nn+1, vector<int>(0));

    for(int ii=0;ii<=nn;ii++) //要选n+1个结点出来，包括0也要。ii不指代哪个结点，仅仅起次数作用。
    {
        //找一个没访问过的，离0距离最近的
        int minDist = UINT16_MAX, minID = -1;
        for(int jj=0;jj<=nn;jj++)
        {
            if (!visited[jj] && dist[jj]<minDist)
            {
                minDist = dist[jj];
                minID = jj;
            }
        }
        if (minID==-1) break;
        visited[minID] = true;
        // printf("The %dth time find %d as the shortest node to 0 unvisited\n", ii, minID);
        //据此结点修改所有其他结点到0点的距离，并修改最优前继
        for(int jj=0;jj<=nn;jj++)
        {
            if (ee[minID][jj]!=0)  //!visited[jj]似乎是不需要这个条件
            {
                if (dist[jj]>dist[minID]+ee[minID][jj])
                {
                    dist[jj] = dist[minID]+ee[minID][jj];
                    pre[jj].clear();
                    pre[jj].push_back(minID);
                    // printf("\tclearing pred for %dth node, and injecting %dth node into that\n", jj, minID);
                }
                else if (dist[jj]==dist[minID]+ee[minID][jj])
                {
                    pre[jj].push_back(minID);
                    // printf("\t\tinjecting %dth node into the pred of the %dth node\n", minID, jj);
                }
            }
        }
    }
    // for(int ii=0;ii<=nn;ii++)
    // {
    //     printf("pred for %d node:", ii);
    //     for(auto jj: pre[ii]) cout << jj << " ";
    //     cout << endl;
    // }
    dfs(sp);
}

int main(int argc, char const *argv[])
{
    int st, ed, tm;
    cin >> cap >> nn >> sp >> mm;

    inventory = vector<int> (nn+1, 0);
    ee = vector<vector<int>> (nn+1, vector<int>(nn+1, 0));
    
    for(int ii=0;ii<nn;ii++) {cin>>inventory[ii+1];inventory[ii+1]-=cap/2;}
    for(int ii=0;ii<mm;ii++)
    {
        cin>> st>> ed >> tm;
        ee[ed][st] = ee[st][ed] = tm;
    }
    findShortestDist();
    cout << minNeed << " ";
    for(int ii=path.size()-1;ii>0;ii--) cout << path[ii] << "->"; cout << path[0]<<" ";//
    cout << maxPickup;
    return 0;
}