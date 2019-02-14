#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

int scoreWeight[] = {4,6,9};

struct instRec{
    string name;
    int tws;
    int ns;
    instRec(): name(""), tws(0), ns(0) {}
    instRec(string nm, int it, int ins): name(nm), tws(it), ns(ins) {}
    bool operator<(const instRec& rr)
    {
        if (tws!=rr.tws) return tws>rr.tws;
        if (ns !=rr.ns ) return ns <rr.ns;
        return (name<rr.name);
    }
};

int nn;
// vector<string> instNames;
// vector<instRec*> insts;
unordered_map<string, instRec> insts;

int getType(string ss)
{
    if (ss[0]=='B') return 0;
    if (ss[0]=='A') return 1;
    if (ss[0]=='T') return 2;
}

void lower(string& ss)
{
    for(auto& c: ss) c=tolower(c);
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn;
    string id;
    int score, type;
    string instName;
    instRec* tmpInst;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> id >> score >> instName;

        type = getType(id);
        
        score*=scoreWeight[type];

        lower(instName);

        auto it = insts.find(instName);
        if (it==insts.end())
        {
            instRec tmpInst = instRec(instName, score, 1);
            insts[instName] = tmpInst;
        }
        else{
            it->second.tws+=score;
            it->second.ns++;
        }
    }

    vector<instRec> ans;
    for(auto it: insts)
    {
        ans.push_back(it.second);
        ans.back().tws/=6;
    }

    sort(ans.begin(), ans.end());

    int tws = ans.front().tws;
    int rank = 1;
    cout << insts.size() << endl;
    for(int ii=0;ii<insts.size();ii++)
    {
        if (ans[ii].tws!=tws)
        {
            tws = ans[ii].tws;
            rank = ii+1;
        }
        cout << rank << " " << ans[ii].name << " " << ans[ii].tws << " " << ans[ii].ns << endl;
    }
    return 0;
}
