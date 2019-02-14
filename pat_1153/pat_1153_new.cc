#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct patCard
{
    string id;
    int type; //B-0,A-1,T-2
    int room;
    int date;
    int no;
    int score;
    patCard(string si, int sc): id(si),score(sc) {
        if (si[0]=='B') type=0;
        if (si[0]=='A') type=1;
        if (si[0]=='T') type=2;
        room = stoi(si.substr(1,3));
        date = stoi(si.substr(4,6));
        no = stoi(si.substr(10,3));
    }
};

struct roomRes
{
    int room;
    int testeeNo;
    roomRes(int id): room(id), testeeNo(0) {}
};

vector<vector<patCard*>> byType(3);
// vector<vector<patCard*>> byDate;
int testeeNoForRoom[1000];
int testeeScoreForRoom[1000];
vector<int> id2date;
// vector<vector<patCard*>> dateId2Cards;
// vector<vector<roomRes*>> dateId2RoomRes;
int date2id[1000000];
// map<int, int> date2id;
vector<map<int, int>> dateResultsMap; // date x room x no
vector<vector<vector<int>>> dateResultVec;

int nn;

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int kk;
    string id;
    int score;
    patCard* tmp;
    cin >> nn >> kk;
    int dateId, date;
    fill(date2id,date2id+1000000, -1);
    for(int ii=0;ii<nn;ii++)
    {
        cin >> id >> score;
        tmp = new patCard(id, score);

        byType[tmp->type].push_back(tmp);

        testeeNoForRoom[tmp->room]++;
        testeeScoreForRoom[tmp->room]+=tmp->score;

        date = tmp->date;
        if (date2id[date]==-1)
        {
            dateId = id2date.size();
            id2date.push_back(date);
            date2id[date] = dateId;
            dateResultsMap.push_back(map<int, int>());
            dateResultsMap.back().insert(make_pair(tmp->room, 1));
        }
        else{
            dateId = date2id[date];
            auto it = dateResultsMap[dateId].find(tmp->room);
            if (it==dateResultsMap[dateId].end())
            {
                dateResultsMap[dateId].insert(make_pair(tmp->room, 1));
            }
            else{
                it->second++;
            }
        }
    }
    // for(int ii=0;ii<1000;ii++)
    // {
    //     roomResults[ii][0] = ii;
    // }

    for(int ii=0;ii<3;ii++)
        sort(byType[ii].begin(), byType[ii].end(), [] (patCard* ll, patCard* rr) 
        {
            if (ll->score!=rr->score) return ll->score>rr->score;
            if (ll->room!=rr->room) return ll->room<rr->room;
            if (ll->date!=rr->date) return ll->date<rr->date;
            return ll->no<rr->no;
        });

    dateResultVec.resize(id2date.size());
    for(int ii=0;ii<id2date.size();ii++)
    {
        // dateResultVec[ii].resize(dateResultsMap[ii].size(), vector<int>(2));
        for(auto pp: dateResultsMap[ii])
        {
            dateResultVec[ii].push_back(vector<int> {pp.first, pp.second});
        }
        sort(dateResultVec[ii].begin(), dateResultVec[ii].end(), [] (vector<int> ll, vector<int> rr) {return ll[1]>rr[1]||(ll[1]==rr[1]&&ll[0]<rr[0]);});
    }

    int qt;
    int qc;
    char qcc;
    string qd;
    for(int ii=1;ii<=kk;ii++)
    {
        cin >> qt;
        switch (qt)
        {
            case 1:
            {
                cin >> qcc;
                // printf("Case %d: %d %c\n", ii, qt, qcc);
                cout << "Case " << ii << ": " << qt << " " << qcc << endl;
                if (qcc == 'B') qc=0;
                if (qcc == 'A') qc=1;
                if (qcc == 'T') qc=2;
                if (byType[qc].size()==0) {cout << "NA" << endl;break;}
                for(auto pp: byType[qc]) cout << pp->id << " " << pp->score << endl;
                break;
            }
            case 2:
            {
                cin >> qd;
                qc = stoi(qd);
                // printf("Case %d: %d %03d\n", ii, qt, qc);
                cout << "Case " << ii << ": " << qt << " " << qd << endl;
                if (qc<0||qc>1000||testeeNoForRoom[qc]==0) {cout << "NA" << endl;break;}
                cout << testeeNoForRoom[qc] << " " << testeeScoreForRoom[qc] << endl;
                break;
            }
            case 3:
            {
                cin >> qd;
                qc = stoi(qd);
                // printf("Case %d: %d %s\n", ii, qt, qd.c_str());
                cout << "Case " << ii << ": " << qt << " " << qd << endl;
                if (date2id[qc]==-1||dateResultVec[date2id[qc]].empty()) {cout << "NA" << endl;break;}
                for(auto vv: dateResultVec[date2id[qc]])
                {
                    cout << vv[0] << " " << vv[1] << endl;
                }
                break;
            }
        }
    }
    return 0;
}
