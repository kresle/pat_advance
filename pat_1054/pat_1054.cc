#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<vector<int>> img;
unordered_map<int, int> app;

int main()
{
    int mm,nn;
    cin >> mm >>nn;
    img.resize(nn, vector<int>(mm, -1));
    for(int ii=0;ii<nn;ii++)
    {
        for(int jj=0;jj<mm;jj++) 
        {
            cin >> img[ii][jj];
            auto it = app.find(img[ii][jj]);
            if (it==app.end())
            {
                app.insert(make_pair(img[ii][jj],1));
            }
            else{
                it->second++;
            }
        }
    }
    for(auto it : app)
    {
        if (it.second>mm*nn/2) {cout << it.first;break;}
    }
    return 0;
}