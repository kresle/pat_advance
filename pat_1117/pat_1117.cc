#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct mileage
{
    int val;
    int app;
    mileage(int vv): val(vv), app(1) {};
    bool operator<(mileage obj)
    {
        return val>obj.val;
    }
};

vector<mileage*> records;
map<int, mileage*> recordMap;
int nn;

int main()
{
    int val;
    cin >> nn;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> val;
        if (recordMap.find(val)==recordMap.end())
        {
            mileage* mm = new mileage(val);
            recordMap[val] = mm;
            records.push_back(mm);
        }
        else
        {
            recordMap[val]->app++;
        }
    }
    
    sort(records.begin(), records.end(), [] (mileage* ll, mileage* rr) {return *ll<*rr;});

    int greaterCnt = records[0]->app;
    for(int ii=1;ii<records.size();ii++)
    {
        // for(int jj=0;jj<records[ii]->app;jj++) cout << records[ii]->val << " ";
        // cerr << records[ii]->val << " " << greaterCnt << endl;
        // cerr << greaterCnt << endl;
        if (greaterCnt>=records[ii]->val)
        {
            cout << greaterCnt << endl;
            return 0;
        }
        greaterCnt += records[ii]->app;
    }
    return 0;
}