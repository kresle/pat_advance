// 15:21 -> 16:34(21, 2TLE+1SF) -> 16:40(21, 3TLE) -> 16:57(AC)

// 又忘了一个点： auto pp: container， 对pp进行赋值，并不影响container中的原始数据，还是要用引用auto&。这个错误之前犯过的，又一次。
// 在时间轴上对in-out进行匹配，逻辑一开始有问题，对in和out两种情况，选择是不一样的：in要选尽量靠后的，而out要选尽量靠前的。
// 关于query的查询。没有想到太好的办法，这样能过也就算了吧。

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

struct record
{
    int time;
    bool isIn;
    bool operator<(record obj) {return time<obj.time;}
};

int nn, kk;
vector<int> querys;
vector<int> querysAns;

int stimeToSeconds(string ss)
{
    return stoi(ss.substr(0,2))*3600 + stoi(ss.substr(3,2))*60 + stoi(ss.substr(6));
}

map<string, vector<record*>> allPlates;

int maxParkingTime=0;
vector<string> platesParkingLongest;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> kk;
    querys.resize(kk);
    querysAns.resize(kk, 0);
    string plate, stm, status;
    record* tmp;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> plate >> stm >> status;
        tmp = new record;
        tmp->time = stimeToSeconds(stm);
        tmp->isIn = status=="in";
        allPlates[plate].push_back(tmp);
    }

    for(int ii=0;ii<kk;ii++)
    {
        cin >> stm;
        querys[ii] = stimeToSeconds(stm);
    }

    vector<record*> arr;
    for(auto& pp: allPlates)
    {
        sort(pp.second.begin(), pp.second.end(), [] (record* ll, record* rr) {return *ll<*rr;});
        arr.clear();
        int ii=0;
        while(ii<pp.second.size() && !pp.second[ii]->isIn) ii++;
        for(;ii<pp.second.size()-1;ii++)
        {
            if (pp.second[ii]->isIn && pp.second[ii]->isIn!=pp.second[ii+1]->isIn)
                arr.push_back(pp.second[ii]);
            if (!pp.second[ii]->isIn && pp.second[ii]->isIn!=pp.second[ii-1]->isIn)
                arr.push_back(pp.second[ii]);
        }
        if (!arr.empty() && arr.back()->isIn)
        {
            if (!pp.second.back()->isIn) arr.push_back(pp.second.back());
            else arr.pop_back();
        }
        // cerr << arr.size() << " ";
        int pt = 0;
        for(int ii=1;ii<arr.size();ii+=2)
        {
            pt+=arr[ii]->time-arr[ii-1]->time;
            for(int jj=0;jj<kk;jj++)
            {
                if (querys[jj] < arr[ii-1]->time) continue;
                if (querys[jj] > arr[ii]->time) break;
                if (arr[ii-1]->time<=querys[jj] && arr[ii]->time>querys[jj])  {querysAns[jj]++;}
            }
        }
        if (pt>maxParkingTime)
        {
            maxParkingTime = pt;
            platesParkingLongest.clear(), platesParkingLongest.push_back(pp.first);
        } else if (pt==maxParkingTime)
        {
            platesParkingLongest.push_back(pp.first);
        }
        pp.second = arr;
        // cerr << pp.second.size() << endl;
    }

    for(auto pp: querysAns)
        printf("%d\n",pp);

    sort(platesParkingLongest.begin(), platesParkingLongest.end());
    for(auto pp: platesParkingLongest) printf("%s ", pp.c_str());
    printf("%02d:%02d:%02d", maxParkingTime/3600, (maxParkingTime/60)%60, maxParkingTime%60);
}