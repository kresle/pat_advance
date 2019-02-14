#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct stud
{
    string name;
    int height;
    stud(string nnm, int hh): name(nnm), height(hh) {}
    bool operator<(stud obj)
    {
        if (height!=obj.height) return height<obj.height;
        return name<obj.name;
    }
};

int nn, rr;
vector<stud*> allRecs;
vector<vector<stud*>> ans;

int main()
{
    cin >> nn >> rr;
    stud* tmp;
    string name;
    int height;
    while(nn--)
    {
        cin >> name >> height;
        tmp = new stud(name, height);
        allRecs.push_back(tmp);
    }
    nn = allRecs.size();
    int cc = nn/rr;
}