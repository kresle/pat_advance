#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct record
{
    int iid;
    string id;
    string name;
    int grade;
    // record(string s1, string s2, int gg): id(s1), name(s2), grade(gg) {}
};

int nn, cc;
vector<record*> database;

bool lessThan(record* ll, record* rr)
{
    switch (cc)
    {
        case 1:
        {
            return ll->iid < rr->iid;
        }
        case 2:
        {
            return ll->name < rr->name || (ll->name == rr->name && ll->id < rr->id);
        }
        case 3:
        {
            return ll->grade < rr->grade || (ll->grade == rr->grade && ll->id < rr->id);
        }
    }
    return true;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> cc;
    database.resize(nn, NULL);
    for(int ii=0;ii<nn;ii++)
    {
        record *rr = new record();
        cin >> rr->id >> rr->name >> rr->grade;
        rr->iid = stoi(rr->id);
        database[ii] = rr;
    }
    sort(database.begin(), database.end(), lessThan);
    for(int ii=0;ii<nn;ii++)
    {
        cout << database[ii]->id << " " << database[ii]->name << " " << database[ii]->grade << endl;
    }
    return 0;
}
