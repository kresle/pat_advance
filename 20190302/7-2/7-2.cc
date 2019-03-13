
//水题，就最后输出格式自己一开始搞错了。

#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
    int nn;
    cin >> nn;
    string id;
    set<string> alumni;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> id;
        alumni.insert(id);
    }
    cin >> nn;
    int aCnt = 0;
    string oa, og;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> id;
        if (og.empty()|| og.substr(6,8)>id.substr(6,8)) og = id;
        if (alumni.find(id)!=alumni.end())
        {
            aCnt++;
            if (oa.empty()||oa.substr(6,8)>id.substr(6,8))
                oa = id;
        }
    }
    if (aCnt)
    {
        cout << aCnt << endl;
        cout << oa;
    }
    else
    {
        cout << aCnt << endl;
        cout << og;
    }
    
}