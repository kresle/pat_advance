#include <iostream>
#include <vector>
#include <map>
using namespace std;

int nn, N;
vector<vector<int>> lines;//stop

vector<vector<int>> adj;
// vector<vector<int>> edge;
map<int, int> edge;

vector<int> id2stop;
int stop2id[10000];

// vector<vector<int>> dist;
// vector<vector<int>> prec;

/*void floyd()
{
    int ii,jj,kk;
    dist.resize(N, vector<int>(N, UINT16_MAX));
    prec.resize(N, vector<int>(N, -1));
    for(ii=0;ii<N;ii++)
    {
        for(auto kk: adj[ii])
        {
            dist[ii][kk] = 1;
            prec[ii][kk] = kk;
        }
        dist[ii][ii] = 0;
    }
    for(kk=0;kk<N;kk++)
    {
        for(ii=0;ii<N;ii++)
        {
            // if (ii==jj) continue;
            // if (edge[ii][jj]) continue;
            // for(auto kk: adj[ii])
            // {
            //     if (dist[ii][jj]>dist[kk][jj]+1)
            //     {
            //         dist[ii][jj] = dist[kk][jj]+1;
            //         prec[ii][jj] = kk;
            //     }
            // }
            for(jj=0;jj<N;jj++)
            {
                if (dist[ii][jj]>dist[ii][kk]+dist[kk][jj])
                {
                    dist[ii][jj] = dist[ii][kk]+dist[kk][jj];
                    prec[ii][jj] = kk;
                }
            }
        }
    }
}*/

int getLineTransfer(vector<int>& path)
{
    int res=1; //line = edge[path[0]][path[1]], 
    int line = edge.find(path[0]*N+path[1])->second, tmp;
    for(int ii=2;ii<path.size();ii++)
    {
        int tmp = edge.find(path[ii-1]*N+path[ii])->second;
        if (tmp !=line)
        {
            line = tmp;
            res++;
        }
    }
    return res;
}

int id_st, id_ed;
vector<int> path, optPath;
int lineTransfer;
vector<bool> visited;
void dfs(int id)
{
    path.push_back(id);
    visited[id] = true;
    if (id == id_ed)
    {
        if (optPath.empty()||path.size()<optPath.size())
        {
            optPath = path;
            lineTransfer = getLineTransfer(path);
        }
        if (!optPath.empty()&&path.size()==optPath.size())
        {
            int tmp = getLineTransfer(path);
            if (tmp<lineTransfer)
            {
                optPath = path;
                lineTransfer = tmp;
            }
        }
        path.pop_back();
        visited[id]=false;
        return;
    }
    if (!optPath.empty() && path.size()>optPath.size())
    {
        path.pop_back();
        visited[id]=false;
        return;
    }
    for(auto kk: adj[id])
    {
        if (!visited[kk])
        {
            dfs(kk);
        }
    }
    path.pop_back();
    visited[id]=false;
}

/*void present(int id_st, int id_ed)
{
    cout << dist[id_st][id_ed] << endl;
    int mid = id_st;
    while(mid!=id_ed)
    {
        cout << id2stop[mid] << " ";
        mid = prec[mid][id_ed];
    }
    cout << id2stop[mid] << endl;
}*/

void presentPath(vector<int>& path)
{
    cout << path.size()-1 << endl;
    int id_st = path[0];
    int line = edge.find(path[0]*N+path[1])->second, tmp;
    for(int ii=2;ii<path.size();ii++)
    {
        tmp = edge.find(path[ii-1]*N+path[ii])->second;
        if (tmp!=line)
        {
            printf("Take Line#%d from %04d to %04d.\n", line, id2stop[id_st], id2stop[path[ii-1]]);
            line = tmp;
            id_st = path[ii-1];
        }
    }
    printf("Take Line#%d from %04d to %04d.\n", line, id2stop[id_st], id2stop[path.back()]);
}

int main(int argc, char const *argv[])
{
    int mm, kk;
    int st, ed;
    cin >> nn;
    lines.resize(nn+1);
    fill(stop2id, stop2id+10000, -1);
    for(int ii=1;ii<=nn;ii++)
    {
        cin >> mm;
        lines[ii].resize(mm);
        for(int jj=0;jj<mm;jj++)
        {
            cin >> lines[ii][jj];
            if (stop2id[lines[ii][jj]]==-1) {
                stop2id[lines[ii][jj]] = id2stop.size();
                id2stop.push_back(lines[ii][jj]);
            }
        }
    }
    N = id2stop.size();
    // edge.resize(N, vector<int>(N));
    adj.resize(N);
    visited.resize(N, false);
    for(int ii=1;ii<=nn;ii++)
    {
        for(int jj=1;jj<lines[ii].size();jj++)
        {
            int id1 = stop2id[lines[ii][jj-1]];
            int id2 = stop2id[lines[ii][jj]];
            // edge[id1][id2] = ii;
            // edge[id2][id1] = ii;
            edge.insert(make_pair(id1*N+id2, ii));
            edge.insert(make_pair(id2*N+id1, ii));
            adj[id1].push_back(id2);
            adj[id2].push_back(id1);
        }
    }

    // floyd();
    lines.clear();
    cin >> kk;
    int stop_st, stop_ed;
    while(kk--)
    {
        cin >> stop_st >> stop_ed;
        id_st = stop2id[stop_st];
        id_ed = stop2id[stop_ed];
        path.clear();
        optPath.clear();
        dfs(id_st);
        presentPath(optPath);
        // present(stop2id[stop_st], stop2id[stop_ed]);
    }
    return 0;
}
