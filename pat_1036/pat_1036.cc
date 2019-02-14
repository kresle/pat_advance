#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct record
{
    string name;
    string id;
    int grade;
};

vector<record*> boys, girls;

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int nn;
    int minM = 101, maxF = -1, minID=-1,maxID=-1;
    cin >> nn;
    for(int ii=0;ii<nn;ii++)
    {
        char gender;
        record* rr = new record();
        cin >> rr->name >> gender >> rr->id >> rr->grade;
        if (gender=='M')
        {
            boys.push_back(rr);
            if (rr->grade<minM) {minM=rr->grade;minID = boys.size()-1;}
        }
        if (gender=='F')
        {
            girls.push_back(rr);
            if (rr->grade>maxF) {maxF=rr->grade;maxID = girls.size()-1;}
        }
    }
    cerr << maxID << " " << minID << endl;
    if (maxID!=-1) cout << girls[maxID]->name << " " << girls[maxID]->id << endl;
    else cout << "Absent\n";
    if (minID!=-1) cout << boys[minID]->name << " " << boys[minID]->id << endl;
    else cout << "Absent\n";
    if (maxID!=-1&&minID!=-1) cout << maxF-minM;
    else cout << "NA";
    return 0;
}
