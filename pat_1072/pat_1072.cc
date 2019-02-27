// 14:23 - 16:03(22, WA) - 16:14(AC)
// 做mm次dijkstra?

// 这道题花了接近两个小时时间，太惭愧了。
// 做完了想，其实也没什么难的。
// 做mm次dijkstra(),每次的结果与最优的进行比较。
// 花了这么久的原因所在：
// 1.没有看给的样例，自己臆测，不考虑的gasStation没有用，但实际上是可以当中继点用的
// 2.没有理解题意。解的要求是在所有城市与加油站的距离都在范围内的情况下，最小距离要最大。在满足前者的条件下，才选总距离最小的。在满足前两者的条件下，取编号最小的。而自己又是臆测，挑的总距离最小的。
// 在2的理解失误的情况下，花费了大量时间来排查到底哪里出错了。
// 3.dijkstra用了两个集合，虽然是挺巧妙的，但是容易写错。像自己就在更新时用了ccGen而不是全体的集合allGen.
// 其实这道题又不算难，没有像其他dijkstra那样要求最优路径信息。

#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <string>
using namespace std;

#define INF 0x3f3f3f3f

int nn, mm, kk, ds;

vector<vector<int>> dist; // (nn+mm)*(nn+mm)

int sidToid(string ss)
{
    if (ss[0] == 'G')
        return nn + stoi(ss.substr(1)) - 1;
    return stoi(ss) - 1;
}

int minCityStnDist = 0;   //越大越好
int minOverallDist = INF; //越小越好
int ans = -1;             //最优解加油站的编号
void dijkstra(int ss)
{
    vector<int> dp(nn + mm, INF);
    set<int> ccGen, allGen;
    for (int ii = 0; ii < nn + mm; ii++)
    {
        if (dist[ii][ss] < INF)
            dp[ii] = dist[ii][ss];
        if (ii<nn) ccGen.insert(ii);
        allGen.insert(ii);
    }
    allGen.erase(ss);
    int allCityDistSum = 0;
    int local_minCityStnDist = INF;
    while (!ccGen.empty())
    {
        //找最近结点
        int minD = INF, vv = -1;
        for (auto cc : allGen)
            if (dp[cc] < minD)
                minD = dp[cc], vv = cc;
        if (vv == -1)
            return; //"no all connected to gas station"
        if (minD > ds)
            return; //"city station dist exceed limit"
        //如果找到的最近结点是城市
        if (ccGen.find(vv) != ccGen.end())
        {
            ccGen.erase(vv);
            allCityDistSum += minD;
            if (minD < local_minCityStnDist)
            {
                local_minCityStnDist = minD; // 其实只会更新一次
                if (minD < minCityStnDist)
                    return; //"min city - gasStation dist not optimized, skip"
            }
            if (local_minCityStnDist == minCityStnDist && allCityDistSum >= minOverallDist) //前面的条件已保证到达此处时，最小城市-油站距离大于等于历史最小.而如果前者是等于的情形，那只要现在的部分和大于等于历史的全部和，就可以判定不是最优了。
                return; // while equal minCityStation dist, overall dist sum not optimal, give up
        }
        allGen.erase(vv);

        //更新距离
        for (auto cc : allGen)
        {
            if (dp[cc] > dist[cc][vv] + dp[vv])
                dp[cc] = dist[cc][vv] + dp[vv];
        }
    }
    if (local_minCityStnDist > minCityStnDist)
    {
        minOverallDist = allCityDistSum;
        minCityStnDist = local_minCityStnDist;
        ans = ss;
    }
    else if (local_minCityStnDist == minCityStnDist && allCityDistSum < minOverallDist)
    {
        minOverallDist = allCityDistSum;
        ans = ss;
    }
}

int main()
{
    cin >> nn >> mm >> kk >> ds;
    dist.resize(nn + mm, vector<int>(nn + mm, INF));
    string ss;
    int vv, uu;
    for (int ii = 0; ii < kk; ii++)
    {
        cin >> ss;
        vv = sidToid(ss);
        cin >> ss;
        uu = sidToid(ss);
        cin >> dist[vv][uu];
        dist[uu][vv] = dist[vv][uu];
    }
    for (int ii = nn; ii < nn + mm; ii++)
        dijkstra(ii);
    if (ans != -1)
    {
        printf("G%d\n", ans - nn + 1);
        printf("%.1f %.1f", (float)minCityStnDist, (float)minOverallDist / nn);
    }
    else
        printf("No Solution");
}