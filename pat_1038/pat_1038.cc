#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> nums;

int main()
{
    int nn;
    cin >> nn;
    nums.resize(nn);
    for(int ii=0;ii<nn;ii++) 
        cin >> nums[ii];
    sort(nums.begin(),nums.end(), [] (string ll, string rr){return (ll+rr)<(rr+ll);});
    bool foundNoneZero = false;
    // cout << stoi(nums[0]);
    // for(int ii=1;ii<nn;ii++) cout << nums[ii];
    for(int ii=0;ii<nn-1;ii++)
    {
        if (foundNoneZero) cout << nums[ii];
        else{
            if (stoi(nums[ii])!=0)
            {
                foundNoneZero = true;
                cout << stoi(nums[ii]);
            }
            else continue;
        }
    }
    if (foundNoneZero) cout << nums.back();
    else cout << stoi(nums.back());
    return 0;
}