// 16:47 - 17:09(AC)
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int nn, maxDep;
vector<vector<int>> followers;
vector<bool> visited;

int bfs(int id)
{
    fill(visited.begin(), visited.end(), false);
    queue<int> qq;
    qq.push(id), visited[id] = true; //注意一下这里
    int dep = 0, ans = 0;
    while(!qq.empty()&&dep<maxDep+1)
    {
        queue<int> lvl_qq;
        while(!qq.empty())
        {
            for(auto ff: followers[qq.front()])
            {
                if (!visited[ff])
                {
                    lvl_qq.push(ff), visited[ff] = true; //注意一下这里
                }
            }
            ans++;
            qq.pop();
        }
        dep++;
        qq = lvl_qq;
    }
    return ans;
}

int main()
{
    cin >> nn >> maxDep;
    followers.resize(nn);
    visited.resize(nn);
    int kk, id;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> kk;
        for(int jj=0;jj<kk;jj++)
        {
            cin >> id;
            id--;
            followers[id].push_back(ii);
        }
    }
    cin >> kk;
    while(kk--)
    {
        cin >> id;
        id--;   //刚开始这个忘了
        cout << bfs(id)-1 << endl; //因为自己不能转发
    }
}