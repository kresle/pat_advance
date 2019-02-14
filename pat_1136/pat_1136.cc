#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

bool isPalindromic(string num)
{
    int nn = num.size();
    if (nn == 0)
        return false;
    for (int ii = 0; ii < nn / 2; ii++)
    {
        if (num[ii] != num[nn - 1 - ii])
            return false;
    }
    return true;
}

string add(string aa, string bb)
{
    int nn = aa.size();
    vector<int> ans;
    ans.reserve(aa.size()+1);
    bool overflow = false;
    for(int ii=0;ii<aa.size();ii++)
    {
        ans.push_back(aa[nn-1-ii]-'0'+bb[nn-1-ii]-'0'+overflow);
        if (ans.back()>=10)
        {
            overflow = true;
            ans.back() = ans.back()%10;
        }
        else
        {
            overflow = false;
        }
    }
    if (overflow) ans.push_back(1);
    string sans(ans.size(),' ');
    for(int ii=0;ii<ans.size();ii++)
    {
        sans[ii] = '0'+ans[ans.size()-1-ii];
    }
    return sans;
}

int main()
{
    string rr;
    cin >> rr;
    for (int ii = 0; ii < 10; ii++)
    {
        if (isPalindromic(rr))
        {
            cout << rr << " is a palindromic number." << endl;
            return 0;
        }
        string ff = rr;
        reverse(rr.begin(), rr.end());
        cout << ff << " + " << rr << " = ";
        rr = add(ff, rr);
        cout << rr << endl;
    }
    if (isPalindromic(rr))
        cout << rr << " is a palindromic number." << endl;
    else
        cout << "Not found in 10 iterations." << endl;
    return 0;
}