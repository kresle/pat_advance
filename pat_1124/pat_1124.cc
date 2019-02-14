#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int mm, nn, ss;
vector<string> forwards;
set<string> ans;

int main()
{
    cin >> mm >> nn >> ss;
    if (ss > mm)
    {
        cout << "Keep going..." << endl;
        return 0;
    }
    forwards.reserve(mm), forwards.resize(mm);
    for (int ii = 0; ii < mm; ii++)
    {
        cin >> forwards[ii];
    }
    int id = ss - 1;
    while (id < mm)
    {
        while(id<mm&&ans.find(forwards[id])!=ans.end()) id++;
        if (id==mm) break;
        ans.insert(forwards[id]);
        cout << forwards[id] << endl;
        id += nn;
    }
    return 0;
}