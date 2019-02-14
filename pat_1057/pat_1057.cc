#include <stack>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 *没做出来，但看了别人的代码。暂时不写，等以后别人方法忘差不多以后再写。 
 */

int nn;
vector<int> stk;
// int tail = -1;

int main()
{
    cin >> nn;

    for(int ii=0;ii<nn;ii++)
    {
        string cmd;
        cin >> cmd;
        if (cmd=="Pop")
        {
            if (stk.size()>0) {
                cout << stk.back() << endl;
                stk.pop_back();
            }
            else cout << "Invalid" << endl;
        }
        if (cmd=="Push")
        {
            int tmp;
            cin >> tmp;
            stk.push_back(tmp);
        }
        if (cmd=="PeekMedian")
        {
            if (stk.size()>0)
            {
                int mid;
                if (stk.size()%2==0)
                {

                }

            }
            else cout << "Invalid" << endl;
        }
    }
}