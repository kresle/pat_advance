#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int nn, mm;
vector<vector<int>> adj_homo, adj_hetero;
// vector<int>[10000] adj_homo;

vector<vector<bool>> connected;
vector<int> id2name;    //id to xxxx
// map<int, int> name2id;  //xxxx to id
vector<int> name2id(10000, -1);


int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    /* code */
    cin >> nn >> mm;
    adj_homo.resize(nn);
    adj_hetero.resize(nn);
    connected.resize(nn, vector<bool> (nn, false));
    for(int ii=0;ii<mm;ii++)
    {
        int name1, name2;
        cin >> name1 >> name2;
        int id1, id2;
        bool g1=name1>0, g2=name2>0;
        if (name1<0) name1=-name1;
        if (name2<0) name2=-name2;
        if (name2id[name1]!=-1)
        {
            id1 = name2id[name1];
        }
        else
        {
            id1 = id2name.size();
            name2id[name1] = id1;
            id2name.push_back(name1);
        }
        if (name2id[name2]!=-1)
        {
            id2 = name2id[name2];
        }
        else
        {
            id2 = id2name.size();
            name2id[name2] = id2;
            id2name.push_back(name2);
        }
        connected[id1][id2]=true;
        connected[id2][id1]=true;
        if (g1==g2)
        {
            adj_homo[id1].push_back(id2);
            adj_homo[id2].push_back(id1);
        }
        else{
            adj_hetero[id1].push_back(id2);
            adj_hetero[id2].push_back(id1);
        }
    }
    int kk;
    cin >> kk;
    for(int ii=0;ii<kk;ii++)
    {
        // vector<string> res;
        vector<vector<int>> res;
        int name1, name2;
        cin >> name1 >> name2;
        bool g1=name1>0, g2=name2>0;
        if (name1<0) name1=-name1;
        if (name2<0) name2=-name2;
        int id1 = name2id[name1], id2 = name2id[name2];
        if (id1==-1||id2==-1) { cout << 0 << endl; continue;}
        for(auto ff1: adj_homo[id1])
            for(auto ff2: adj_homo[id2])
            {
                // if (connected[ff1][ff2]) res.push_back(to_string(id2name[ff1])+" "+to_string(id2name[ff2]));
                if (connected[ff1][ff2]) res.push_back(vector<int>{id2name[ff1], id2name[ff2]});
            }
        sort(res.begin(), res.end(), [](vector<int> vv, vector<int> uu) {return vv[0]<uu[0]||(vv[0]==uu[0]&&vv[1]<uu[1]);});
        // [](vector<int> vv, vector<int> uu) {return vv[0]<uu[0]||(vv[0]==uu[0]&&vv[1]<uu[1]);};
        cout << res.size() << endl;
        for(auto rr: res) cout << rr[0] << " " << rr[1] << endl;
    }
    return 0;
}
