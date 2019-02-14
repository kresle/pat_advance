#include <iostream>
#include <string>
using namespace std;

int main()
{
    int kk;
    cin >> kk;
    string num;
    while (kk--)
    {
        cin >> num;
        int inum = stoi(num);
        int lnum = stoi(num.substr(0, num.size() / 2));
        int rnum = stoi(num.substr(num.size() / 2, num.size() / 2));
        if (rnum == 0)
            cout << "No" << endl;
        else
            cout << ((inum % (lnum * rnum) == 0) ? "Yes" : "No") << endl;
    }
}