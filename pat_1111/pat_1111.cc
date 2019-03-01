#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int nn;
int src_id, dst_id;
vector<vector<int>> ileng;
vector<vector<int>> itime;

vector<vector<int>> pred_len;
vector<vector<int>> pred_time;
vector<int> toSrcLen;
vector<int> toSrcTim;
set<int> foundShort;
set<int> foundFast;
set<int> vertex;

void findShortestPath()
{
    //可能有非连通的情形，要考虑下怎么办，主要是下面while循环中止的条件。
    set<int> vt = vertex;
    foundShort.insert(src_id);
    // while (foundShort.size() != nn)
    while (foundShort.find(dst_id)==foundShort.end())
    {
        int minDist = INT16_MAX, minV = -1;
        for (auto vv : vt)
        {
            if (toSrcLen[vv] != INT16_MAX && toSrcLen[vv] < minDist)
            {
                minDist = toSrcLen[vv];
                minV = vv;
            }
        }
        if (minV == -1)
            break;
        foundShort.insert(minV);
        vt.erase(minV);
        for (auto vv : vt)
        {
            if (ileng[minV][vv] != -1 && toSrcLen[vv] > toSrcLen[minV] + ileng[minV][vv])
            {
                toSrcLen[vv] = toSrcLen[minV] + ileng[minV][vv];
                pred_len[vv].clear(), pred_len[vv].push_back(minV);
            }
            else if (ileng[minV][vv] != -1 && toSrcLen[vv] == toSrcLen[minV] + ileng[minV][vv])
            {
                pred_len[vv].push_back(minV);
            }
        }
    }
}

void findFastestPath()
{
    //可能有非连通的情形，要考虑下怎么办，主要是下面while循环中止的条件。
    set<int> vt = vertex;
    foundFast.insert(src_id);
    // while (foundFast.size() != nn)
    while (foundFast.find(dst_id)==foundFast.end())
    {
        int minTime = INT16_MAX, minV = -1;
        for (auto vv : vt)
        {
            if (toSrcTim[vv] < minTime)
            {
                minTime = toSrcTim[vv];
                minV = vv;
            }
        }
        if (minV == -1)
            break;
        foundFast.insert(minV);
        vt.erase(minV);
        for (auto vv : vt)
        {
            if (itime[minV][vv] != -1 && toSrcTim[vv] > toSrcTim[minV] + itime[minV][vv])
            {
                toSrcTim[vv] = toSrcTim[minV] + itime[minV][vv];
                pred_time[vv].clear(), pred_time[vv].push_back(minV);
            }
            else if (itime[minV][vv] != -1 && toSrcTim[vv] == toSrcTim[minV] + itime[minV][vv])
            {
                pred_time[vv].push_back(minV);
            }
        }
    }
}

void printVector(vector<int> &num)
{
    for (int ii = num.size() - 1; ii >= 0; ii--)
        cout << num[ii] << " ";
    cout << endl;
}

vector<int> ans_len, tmp_ans;
int minShortestTime = INT16_MAX;
void dfs(int id)
{
    if (id == src_id)
    {
        tmp_ans.push_back(id);
        int ttl_time = 0;
        int ii = tmp_ans.size() - 1;
        while (ii)
        {
            ttl_time += itime[tmp_ans[ii]][tmp_ans[ii - 1]];
            ii--;
        }
        if (ttl_time < minShortestTime)
        {
            minShortestTime = ttl_time;
            ans_len = tmp_ans;
        }
        tmp_ans.pop_back();
        return;
    }
    else
    {
        tmp_ans.push_back(id);
        for (auto vv : pred_len[id])
            dfs(vv);
        tmp_ans.pop_back();
    }
}

vector<int> post;
void bfs()
{
    int id = dst_id;
    queue<int> qq;
    qq.push(id);
    while (id != src_id)
    {
        queue<int> lvl_qq;
        while (!qq.empty())
        {
            id = qq.front();
            qq.pop();
            for (auto vv : pred_time[id])
            {
                post[vv] = id;
                if (vv == src_id)
                    return;
                else
                    lvl_qq.push(vv);
            }
            qq = lvl_qq;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int kk;
    cin >> nn >> kk;
    int vv, uu, oneway, tlen, ttim;
    ileng.resize(nn, vector<int>(nn, -1));
    itime.resize(nn, vector<int>(nn, -1));
    pred_len.resize(nn);
    pred_time.resize(nn);
    while (kk--)
    {
        cin >> vv >> uu >> oneway >> tlen >> ttim;
        if (oneway == 1)
        {
            ileng[vv][uu] = tlen;
            itime[vv][uu] = ttim;
        }
        else
        {
            ileng[vv][uu] = ileng[uu][vv] = tlen;
            itime[vv][uu] = itime[uu][vv] = ttim;
        }
    }
    cin >> src_id >> dst_id;
    toSrcLen.resize(nn);
    toSrcTim.resize(nn);

    for (int ii = 0; ii < nn; ii++)
    {
        if (ileng[src_id][ii] != -1)
        {
            pred_len[ii].push_back(src_id);
            toSrcLen[ii] = ileng[src_id][ii];
        }
        else
        {
            toSrcLen[ii] = INT16_MAX;
        }
        if (itime[src_id][ii] != -1)
        {
            pred_time[ii].push_back(src_id);
            toSrcTim[ii] = itime[src_id][ii];
        }
        else
        {
            toSrcTim[ii] = INT16_MAX;
        }
        vertex.insert(ii);
    }
    vertex.erase(src_id);

    findShortestPath();
    findFastestPath();
    dfs(dst_id);
    post.resize(nn, -1), bfs();

    reverse(ans_len.begin(), ans_len.end());
    bool isSamePath = true;
    int id = src_id;
    for (int ii = 0; ii < ans_len.size() && isSamePath; ii++)
    {
        if (ans_len[ii] != id)
            isSamePath = false;
        id = post[id];
    }

    if (isSamePath)
    {
        printf("Distance = %d; Time = %d: ", toSrcLen[dst_id], toSrcTim[dst_id]);
        for (int ii = 0; ii < ans_len.size() - 1; ii++)
            printf("%d -> ", ans_len[ii]);
        printf("%d\n", ans_len.back());
    }
    else
    {
        cout << "Distance = " << toSrcLen[dst_id] << ": ";
        for (int ii = 0; ii < ans_len.size() - 1; ii++)
            cout << ans_len[ii] << " -> ";
        cout << ans_len.back() << endl;

        cout << "Time = " << toSrcTim[dst_id] << ": ";
        id = src_id;
        while (id != dst_id)
        {
            cout << id << " -> ";
            id = post[id];
        }
        cout << dst_id << endl;
    }

    return 0;
}