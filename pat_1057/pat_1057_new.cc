#include <iostream>
#include <vector>
#include <map>
using namespace std;

int nn;
int nums[100000];
int pt = -1;
map<int, int> stk;

int main()
{
    string cmd;
    int key;
    cin >> nn;
    while(nn--)
    {
        cin >> cmd;
        if (cmd=="Pop")
        {
            if (pt>=0)
            {
                cout << nums[pt] << endl;
                stk.erase(nums[pt]);
                pt--;
            }
            else{
                cout << "Invalid" << endl;
            }
        }
        if (cmd=="Push")
        {
            pt++;
            cin >> nums[pt];
            stk.insert(make_pair(nums[pt], 0));
        }
        if (cmd=="PeekMedian")
        {
            if (pt<0)
            {
                cout << "Invalid" << endl;
            }
            else
            {
                int N = pt+1;
                int mid;
                if (N%2==0) mid=N/2;
                else mid=(N+1)/2;
                auto it = stk.begin();
                advance(it, mid-1);
                cout << it->first << endl;
            }
        }
    }
    return 0;
}