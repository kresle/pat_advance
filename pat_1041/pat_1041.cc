#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    int nn;
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn;
    vector<int> nums(nn, -1);
    // set<int> visited;
    vector<int> visited;
    int app[10001] {0};
    for(int ii=0;ii<nn;ii++) cin >> nums[ii];
    int res = -1;
    for(int ii=0;ii<nn;ii++)
    {
        if (app[nums[ii]]!=0) continue;
        // if (find(visited.begin(),visited.end(),nums[ii])!=visited.end()) continue;
        //find(nums.begin(),nums.begin()+ii,nums[ii])==nums.begin()+ii && 
        // if (find(nums.begin()+ii+1,nums.end(),nums[ii])==nums.end())
        // {
        //     res = nums[ii];
        //     break;
        // }
        bool noEq = true;
        for(int jj=ii+1;jj<nn;jj++)
        {
            if (nums[jj]==nums[ii])
            {
                noEq = false;
                break;
            }
        }
        if (noEq)
        {
            res = nums[ii];
            break;
        }
        else{
            // visited.insert(nums[ii]);
            // visited.push_back(nums[ii]);
            app[nums[ii]]++;
        }
    }
    if (res==-1) cout << "None";
    else cout << res;
    return 0;
}