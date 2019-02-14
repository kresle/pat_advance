#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct people
{
    string name;
    int age;
    int Net_Worth;
    people(string sn, int ia, int in): name(sn), age(ia), Net_Worth(in) {}
};

int startID[201]; //年龄为xx的是从多少开始
int endID[201];

vector<people*> allPeople;
vector<people*> validPeople;
// vector<vector<people*>> rankingByAge;

int nn, kk;

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> kk;
    // scanf("%d %d", &nn, &kk);
    allPeople.resize(nn, NULL);
    string sn; int ia, in;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> sn >> ia >> in;
        allPeople[ii] = new people(sn, ia, in);
    }
    // cerr << "READ COMPLETE" << endl;

    // sort(allPeople.begin(), allPeople.end(), [] (people* ll, people* rr) {return ll->age<rr->age;});
    sort(allPeople.begin(), allPeople.end(), [] (people* ll, people* rr) {
            if (ll->Net_Worth!=rr->Net_Worth) return ll->Net_Worth>rr->Net_Worth;
            if (ll->age!=rr->age) return ll->age<rr->age;
            return ll->name<rr->name;
        });
    // fill(startID, startID+201, -1);
    // fill(endID, endID+201, -1);
    // int age = 1;
    // while(allPeople.front()->age>age) age++;
    // startID[age]=0;
    // int ii = 0;
    // while(ii<nn)
    // {
    //     cerr << ii << endl;
    //     while(ii<nn && allPeople[ii]->age==age) ii++;
    //     endID[age] = ii-1;
    //     if (ii>=nn) {endID[age]=nn-1;break;}
    //     age = allPeople[ii]->age;
    //     startID[age] = ii;
    // }
    // cerr << "SORT COMPLETE" << endl;
    // for(int ii=1;ii<201;ii++)
    // {
    //     if (startID[ii]!=-1)
    //     {
    //         cerr << ii << " " << startID[ii] << " " << endID[ii] << endl;
    //     }
    // }

    // rankingByAge.resize(201);
    // for(auto pp: allPeople)
    // {
        // rankingByAge[pp->age].push_back(pp);
    // }
    int ageNum[201];
    fill(ageNum,ageNum+201,0);
    for(auto pp: allPeople)
    {
        int age = pp->age;
        if (ageNum[age]<100)
        {
            ageNum[age]++;
            validPeople.push_back(pp);
        }
    }
    
    int maxOpnum, lowerAge, upperAge;
    for(int ik=0;ik<kk;ik++)
    {
        cout << "Case #" << ik+1 << ":" << endl;
        cin >> maxOpnum >> lowerAge >> upperAge;
        int foundNo = 0;
        for(int ii=0;ii<validPeople.size();ii++)
        {
            if (validPeople[ii]->age>=lowerAge&&validPeople[ii]->age<=upperAge)
            {
                foundNo++;
                cout << validPeople[ii]->name << " " << validPeople[ii]->age << " " << validPeople[ii]->Net_Worth<< endl;
                if (foundNo==maxOpnum) break;
            }
        }
        if (foundNo==0) cout << "None" << endl;
        // while(startID[lowerAge]==-1) lowerAge++;
        // while(endID[upperAge]==-1) upperAge--;
        // if (lowerAge>upperAge) {cout <<"None"<<endl; continue;}
        // int st = startID[lowerAge], ed = endID[upperAge];
        // vector<people*> res(ed-st+1, NULL);
        // for(int ii=st;ii<=ed;ii++)
        // res[ii-st] = allPeople[ii];
        // sort(res.begin(), res.end(), [] (people* ll, people* rr) {
        //     if (ll->Net_Worth!=rr->Net_Worth) return ll->Net_Worth>rr->Net_Worth;
        //     if (ll->age!=rr->age) return ll->age<rr->age;
        //     return ll->name<rr->name;
        // });
        // for(int ii=0;ii<maxOpnum&&ii<res.size();ii++)
        // {
        //     cout << res[ii]->name << " " << res[ii]->age << " " << res[ii]->Net_Worth<< endl;
        // }
    }
    return 0;
}
