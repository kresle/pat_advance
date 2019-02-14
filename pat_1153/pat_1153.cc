#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <unordered_map>
using namespace std;

int nn,mm;
string qDate;
class patcard
{
    public:
    string ID;
    int score;
    patcard(string id, int s)
    {
        ID = id;
        score = s;
    }
    inline bool operator< (const patcard& l) {
        return score<l.score && ID>l.ID;
    }
    inline bool operator> (const patcard& l) {
        return score>l.score;
    }
    inline bool operator<= (const patcard& l) {
        return score<=l.score;
    }
    inline bool operator>= (const patcard& l) {
        return score>=l.score;
    }
    inline bool operator== (const patcard& l) {
        return score==l.score;
    }

};

struct roomNumPair{
    int room;
    int testeeNo;
};
// bool roomNumPairLe(const)

bool t1le(const patcard* l, const patcard* r)
//依分数与ID排card
{
    return l->score>r->score || (l->score==r->score&&l->ID<r->ID);
}

bool dle(const patcard* l, const patcard* r)
//依日期与ID与
{
    string dl=l->ID.substr(4,6), dr= r->ID.substr(4,6);
    return dl<=dr;
}

vector<patcard*> patcards;
vector<int> qtype, qRoom;
vector<vector<patcard*>> types; //需要进行排序
vector<vector<patcard*>> testRooms; //按照日期进行排序
// vector<vector<patcard*>> //应该不可能按日期整理
unordered_map<string,vector<patcard*>> date2Cards;
unordered_map<string,vector<vector<int>>> date2Rooms;

int main(int argc, char const *argv[])
{
    /* code */
    cin >> nn >> mm;
    string id;
    int score;
    patcard* tmp;
    types.resize(3);
    testRooms.resize(1000);
    for(int ii=0;ii<nn;ii++)
    {
        cin >> id >> score;
        tmp = new patcard(id, score);

        patcards.push_back(tmp);

        if (id[0]=='A') types[0].push_back(tmp);
        if (id[0]=='B') types[1].push_back(tmp);
        if (id[0]=='T') types[2].push_back(tmp);

        int room = 0;
        for(int jj=1;jj<=3;jj++)
        {
            room = room*10+id[jj]-'0';
        }
        testRooms[room].push_back(tmp);

        auto it = date2Cards.find(id.substr(4,6));
        if (it==date2Cards.end())
        {
            date2Cards.insert(make_pair(id.substr(4,6), vector<patcard*>(1, tmp)));
        }
        else{
            it->second.push_back(tmp);
        }
    }
    for(int ii=0;ii<3;ii++) {sort(types[ii].begin(), types[ii].end(), t1le);}

    for(int ii=0;ii<mm;ii++)
    {
        int qType, qRoom;
        char qLevel;
        
        cin >> qType;
        // if (qType==1) cin >> qLevel;
        // else cin >> qRoom;
        printf("Case %d: ",ii+1);
        switch (qType)
        {
            case 1:
            {
                cin >> qLevel;
                cout << qType << " " << qLevel << endl;
                int type = -1;
                if (qLevel=='A') type=0;
                if (qLevel=='B') type=1;
                if (qLevel=='T') type=2;
                if (types[type].size()==0) {cout << "NA\n"; break;}
                for(auto pp: types[type])
                    cout << pp->ID << " " << pp->score << endl;
                break;
            }
            case 2:
            {
                cin >> qRoom;
                cout << qType << " " << qRoom << endl;
                int ttl = 0;
                if (testRooms[qRoom].size()==0) cout << "NA\n";
                else{
                    for(auto pp: testRooms[qRoom]) ttl+=pp->score;
                    cout << testRooms[qRoom].size() << " " << ttl << endl;
                }
                
                break;
            }
            case 3:
            {
                cin >> qDate;
                cout << qType << " " << qDate << endl;
                auto it = date2Cards.find(qDate);
                if (it==date2Cards.end()) {
                    cout << "NA\n";break;
                }
                else{
                    auto it = date2Rooms.find(qDate);
                    if (it==date2Rooms.end())
                    {
                        id = qDate;
                        auto dc = *date2Cards.find(id);
                        unordered_map<int,int> room2app;
                        for(auto pc: dc.second)
                        {
                            int room = 0;
                            for(int ii=1;ii<=3;ii++) room =room*10+pc->ID[ii]-'0';
                            auto it = room2app.find(room);
                            if (it==room2app.end())
                            {
                                room2app.insert(make_pair(room,1));
                            }
                            else{
                                it->second++;
                            }
                        }
                        vector<vector<int>> tmp;
                        for(auto ra : room2app)
                        {
                            vector<int> tempV(2);
                            tempV[0] = ra.second;//appearance number
                            tempV[1] = ra.first; //room number
                            tmp.push_back(tempV);
                        }
                        if (tmp.size()>1) sort(tmp.begin(),tmp.end(),[] (vector<int> a, vector<int> b) {return a[0]>b[0]||(a[0]==b[0]&&a[1]<b[1]);});
                        date2Rooms.insert(make_pair(id, tmp));
                    }
                    it = date2Rooms.find(qDate);
                    for(auto ar: it->second)
                    {
                        printf("%03d %d\n",ar[1],ar[0]);
                    }
                }
            }
        }        
    }
    return 0;
}
