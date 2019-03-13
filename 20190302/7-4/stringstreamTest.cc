#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    string cmd;
    for(int ii=0;ii<3;ii++)
        getline(cin>> ws, cmd);
    int nn;
    cin >> nn;
    stringstream ss;
    while(nn--)
    {
        getline(cin>> ws, cmd);
        ss.clear();
        ss << cmd;
        string param;
        while(!ss.eof())
        {
            ss >> param;
            cout << param << " ";
        }
        cout << endl;
    }
}