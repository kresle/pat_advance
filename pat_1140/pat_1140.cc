#include <iostream>
#include <string>
using namespace std;

int main()
{
    int dd, kk;
    cin >> dd >> kk;
    string ans = to_string(dd);
    kk--;
    while(kk--)
    {
        string tmp_ans;
        int ii=0;
        while(ii<ans.size())
        {
            tmp_ans += ans[ii];
            int nn = 1;
            while(ii+1<ans.size() && ans[ii+1]==ans[ii])
            {
                ii++;
                nn++;
            }
            tmp_ans+= to_string(nn);
            ii++;
        }
        ans = tmp_ans;
    }
    cout << ans << endl;
}