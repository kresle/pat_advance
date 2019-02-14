#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

void findShortestDist_bfs(vector<vector<int>>& dist, int cap, vector<int>& ration, int sp)
{
    int nn = ration.size()-1;
    vector<bool> visited(nn+1, false);
    visited[0]=true;
    queue<int> qq;
    qq.push(0);
    while(!qq.empty())
    {
        int vv = qq.front();
        qq.pop();
        visited[vv] = true;
        for(int ii=1;ii<=nn;ii++)
        {
            if (!visited[ii] && dist[vv][ii]!=0) qq.push(ii);
        }

    }
}

void findShortestDist_wrong(vector<vector<int>>& dist, int cap, vector<int>& ration, int sp)
{
    // 写错了，这是最小生成树算法。
    // cout << "in method" << endl;
    int nn = ration.size()-1;
    set<int> found;
    found.insert(0);
    vector<int> pred(nn+1, -1);
    vector<int> bikesToHP(nn+1, 0);
    while(found.find(sp)==found.end())
    {
        int minDist = INT32_MAX, minID=0, tmpPred=0, maxBikes;
        for(int ii=1;ii<=nn;ii++)
        {
            if (found.find(ii)!=found.end()) continue; //如果已经在最小集里
            for(auto vv: found)
            {
                // cout << vv << endl;
                if (dist[ii][vv]!=0 && dist[ii][vv]<=minDist)
                {
                    if (dist[ii][vv]<minDist)
                    {
                        minDist = dist[ii][vv];
                        minID = ii;
                        tmpPred = vv;
                        maxBikes = bikesToHP[vv];
                    }
                    if (dist[ii][vv]==minDist)
                    {
                        if (bikesToHP[vv]>maxBikes)
                        {
                            minID = ii;
                            maxBikes = bikesToHP[vv];
                            tmpPred = vv;
                        }
                    }
                }
            }
        }
        cout << minID << endl;
        dist[0][minID] = dist[minID][0] = dist[minID][tmpPred]+dist[0][tmpPred];
        pred[minID] = tmpPred;
        bikesToHP[minID] = bikesToHP[tmpPred]+ration[minID]-cap/2;
        found.insert(minID);
    }
    // int minTime=INT32_MAX;
    // for(auto vv: found)
    // {
    //     if ()
    // }
    int tmp = sp;
    cout << tmp << "<-";
    while((tmp=pred[tmp])!=0) cout << tmp << "<-";
    cout << tmp;
}

void findShortestDist(vector<vector<int>>& dist, int cap, vector<int>& ration, int sp)
{
    // cout << "in method" << endl;
    int nn = ration.size()-1;
    set<int> found;
    found.insert(0);
    vector<int> pred(nn+1, -1);
    vector<int> bikesToHP(nn+1, 0);
    while(found.find(sp)==found.end())
    {
        int minDist = INT32_MAX, minID=0, tmpPred=0, maxBikes;
        for(int ii=1;ii<=nn;ii++)
        {
            if (found.find(ii)!=found.end()) continue; //如果已经在最小集里
            for(auto vv: found)
            {
                // cout << vv << endl;
                if (dist[ii][vv]!=0 && dist[ii][vv]<=minDist)
                {
                    if (dist[ii][vv]<minDist)
                    {
                        minDist = dist[ii][vv];
                        minID = ii;
                        tmpPred = vv;
                        maxBikes = bikesToHP[vv];
                    }
                    if (dist[ii][vv]==minDist)
                    {
                        if (bikesToHP[vv]>maxBikes)
                        {
                            minID = ii;
                            maxBikes = bikesToHP[vv];
                            tmpPred = vv;
                        }
                    }
                }
            }
        }
        cout << minID << endl;
        dist[0][minID] = dist[minID][0] = dist[minID][tmpPred]+dist[0][tmpPred];
        pred[minID] = tmpPred;
        bikesToHP[minID] = bikesToHP[tmpPred]+ration[minID]-cap/2;
        found.insert(minID);
    }
    // int minTime=INT32_MAX;
    // for(auto vv: found)
    // {
    //     if ()
    // }
    int tmp = sp;
    cout << tmp << "<-";
    while((tmp=pred[tmp])!=0) cout << tmp << "<-";
    cout << tmp;
}

int main(int argc, char const *argv[])
{
    int cap, nn, sp, mm;
    int st, ed, tm;
    cin >> cap >> nn >> sp >> mm;
    vector<int> ration(nn+1);
    vector<vector<int>> dist(nn+1, vector<int>(nn+1, 0));
    for(int ii=0;ii<nn;ii++) cin>>ration[ii+1];
    for(int ii=0;ii<mm;ii++)
    {
        cin>> st>> ed >> tm;
        dist[st][ed] = tm;
        dist[ed][st] = tm;
    }
    findShortestDist(dist, cap, ration, sp);
    return 0;
}
