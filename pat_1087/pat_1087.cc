// 15:49 - 16:38(AC)
// 花了差不多50分钟。dijkstra的题，代码量是有点大，不过幸而没什么坑。
// 一开始对题意有点理解不清，不理解输出量。后来写完主体代码以后再看，有点奇怪刚开始为什么能看错或者说理解不了。
// 以及最开始输出城市列表，因为起始的下标写错，多输出一个，这也是太粗心之过。

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

#define INF 0x3f3f3f3f

map<string, int> cityToId;
int nn, kk;
vector<int> happiness;
vector<string> idToCity;
vector<vector<int>> cityDist;
vector<vector<int>> pred;
vector<int> dp;

void dijkstra()
{
    dp.resize(nn, INF);
    dp[0] = 0;
    pred.resize(nn);
    set<int> ccGen;
    for (int ii = 1; ii < nn; ii++)
    {
        if (cityDist[0][ii] < INF)
        {
            dp[ii] = cityDist[0][ii];
            pred[ii].push_back(0);
        }
        ccGen.insert(ii);
    }
    while (!ccGen.empty())
    {
        int minD = INF, vv = -1;
        // 找到最小点
        for (auto uu : ccGen)
        {
            if (dp[uu] < minD)
            {
                minD = dp[uu];
                vv = uu;
            }
        }
        if (vv == -1)
        {
            cerr << "Multiple connected components" << endl;
            break; //有问题
        }
        //更新距离 及 前站
        ccGen.erase(vv);
        for (auto uu : ccGen)
        {
            if (dp[uu] > dp[vv] + cityDist[vv][uu])
            {
                dp[uu] = dp[vv] + cityDist[vv][uu];
                pred[uu].clear(), pred[uu].push_back(vv);
            }
            else if (dp[uu] == dp[vv] + cityDist[vv][uu])
            {
                pred[uu].push_back(vv);
            }
        }
    }
}

void printPath(vector<int>& path)
{
    for(int ii=path.size()-1;ii>0;ii--)
        cerr << idToCity[path[ii]] << "->";
    cerr << "ROM" << endl;
}

int maxHappiness = 0;
vector<int> path, path_ans;
int ans_cnt = 0;
void dfs(int id, int hp)
{
    path.push_back(id);
    if (id==0)
    {
        ans_cnt++;
        if (hp>maxHappiness)
        {
            maxHappiness = hp;
            path_ans = path;
        }
        else if (hp==maxHappiness)
        {
            if (path.size()<path_ans.size()) path_ans = path;
        }
    }
    else
    {
        for(auto vv: pred[id])
            dfs(vv, hp+happiness[id]);
    }
    path.pop_back();
}

int main()
{
    string city;
    int id;
    cin >> nn >> kk >> city;
    idToCity.resize(nn);
    happiness.resize(nn, 0);
    cityDist.resize(nn, vector<int>(nn, INF));

    cityToId[city] = 0;
    idToCity[0] = city;

    for (int ii = 1; ii < nn; ii++)
    {
        cin >> city;
        cityToId[city] = ii;
        idToCity[ii] = city;
        cin >> happiness[ii];
    }
    int uu, vv;
    string cc1, cc2;
    int tmp;
    for (int ii = 0; ii < kk; ii++)
    {
        cin >> cc1 >> cc2 >> tmp;
        uu = cityToId[cc1];
        vv = cityToId[cc2];
        cityDist[uu][vv] = tmp;
        cityDist[vv][uu] = tmp;
    }
    dijkstra();
    dfs(cityToId["ROM"], 0);
    cout << ans_cnt << " " << dp[cityToId["ROM"]] << " " << maxHappiness << " " << maxHappiness/(path_ans.size()-1) << endl;
    for(int ii=path_ans.size()-1;ii>0;ii--)
        cout << idToCity[path_ans[ii]] << "->";
    cout << "ROM";
}