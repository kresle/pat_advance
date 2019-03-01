// AC.
// 这题之前的问题是，在dfs的时候，压的时间下标前后写反了，而之前是用-1来初始化ddist和dtime，所以在有向图是肯定会出错的。
// 今天改用了INF来初始化，dfs老segmentation fault。虽然错了就出错这样很好，但是想不通为什么这个数值问题会引起sf.
// 另外就是写多了dijkstra后总结出来的经验，pred和dp放在dijkstra里面写。
// 总的来说，写的不错。

#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f

int nn, kk, src_id, dst_id;
vector<vector<int>> ddist, dtime;
vector<vector<int>> pred_dist, pred_time;
vector<int> dp_dist, dp_time;

void dijkstra(vector<vector<int>> &dist, vector<vector<int>> &pred, vector<int> &dp)
{
    // 准备dp及pred数组
    dp.clear(), dp.resize(nn, INF);
    pred.clear(), pred.resize(nn);
    set<int> gen;
    for (int ii = 0; ii < nn; ii++)
    {
        if (ii == src_id)
            continue;
        if (dist[src_id][ii] < INF)
        {
            dp[ii] = dist[src_id][ii];
            pred[ii].push_back(src_id);
        }
        gen.insert(ii);
    }
    while (!gen.empty())
    {
        int mmin = INF, vv = -1;
        for (auto uu : gen)
            if (dp[uu] < mmin)
                mmin = dp[uu], vv = uu;
        if (vv == -1)
            break;
        gen.erase(vv);
        for (auto uu : gen)
        {
            if (dp[uu] > dp[vv] + dist[vv][uu])
            {
                dp[uu] = dp[vv] + dist[vv][uu];
                pred[uu].clear(), pred[uu].push_back(vv);
            }
            else if (dp[uu] == dp[vv] + dist[vv][uu])
                pred[uu].push_back(vv);
        }
    }
}

vector<int> ans_dist, tmpAns;
int btime_dist = INF;
void dfs(int id, int acctime)
{
    //似乎可以利用最优时间来进行剪枝
    if (acctime > btime_dist)
        return;
    tmpAns.push_back(id);
    if (id == src_id)
    {
        if (acctime < btime_dist)
        {
            btime_dist = acctime;
            ans_dist = tmpAns;
        }
    }
    else
        for (auto vv : pred_dist[id])
            dfs(vv, acctime + dtime[vv][id]);
    tmpAns.pop_back();
}

vector<int> ans_time;
void bfs()
{
    vector<int> next_fastest(nn, -1); //在bfs中，记录最快的路径信息
    queue<int> qq;
    qq.push(dst_id);
    while (next_fastest[src_id]==-1 && !qq.empty())
    {
        queue<int> lvl_qq;
        while (!qq.empty() && next_fastest[src_id]==-1)
        {
            int id = qq.front();
            for (auto vv : pred_time[id])
            {
                next_fastest[vv] = id;
                if (vv == src_id)
                    break;
                lvl_qq.push(vv);
            }
            qq.pop();
        }
        qq = lvl_qq;
    }
    int id = src_id;
    while (id != dst_id && id >= 0)
    {
        ans_time.push_back(id);
        id = next_fastest[id];
    }
    ans_time.push_back(id);
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> kk;
    ddist.resize(nn, vector<int>(nn, INF)), dtime.resize(nn, vector<int>(nn, INF));
    int vv, uu, ff, tdist, ttime;
    while (kk--)
    {
        cin >> vv >> uu >> ff >> tdist >> ttime;
        ddist[vv][uu] = tdist;
        dtime[vv][uu] = ttime;
        if (ff == 0)
        {
            ddist[uu][vv] = tdist;
            dtime[uu][vv] = ttime;
        }
    }
    cin >> src_id >> dst_id;

    dijkstra(ddist, pred_dist, dp_dist);
    dijkstra(dtime, pred_time, dp_time);

    dfs(dst_id, 0);
    reverse(ans_dist.begin(), ans_dist.end());
    bfs();

    if (ans_dist == ans_time)
    {
        printf("Distance = %d; Time = %d: ", dp_dist[dst_id], dp_time[dst_id]);
        for (int ii = 0; ii < ans_dist.size() - 1; ii++)
            printf("%d -> ", ans_dist[ii]);
        printf("%d\n", ans_dist.back());
    }
    else
    {
        printf("Distance = %d: ", dp_dist[dst_id]);
        for (int ii = 0; ii < ans_dist.size() - 1; ii++)
            printf("%d -> ", ans_dist[ii]);
        printf("%d\n", ans_dist.back());

        printf("Time = %d: ", dp_time[dst_id]);
        for (int ii = 0; ii < ans_time.size() - 1; ii++)
            printf("%d -> ", ans_time[ii]);
        printf("%d\n", ans_time.back());
    }

    return 0;
}