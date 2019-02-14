#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    int nn;
    cin >> nn;
    vector<string> sents;
    sents.resize(nn);
    int upperBound = 256;
    for(int ii=0;ii<nn;ii++) {
        // cin >> sents[ii];
        getline(cin >> ws, sents[ii]);
        if (sents[ii].size()<upperBound) upperBound = sents[ii].size();
    }
    int ii=1;
    bool eq = true;
    for(;ii<=upperBound;ii++)//ii：长度
    {
        eq = true;
        for(int jj=1;jj<nn;jj++)
        {
            if (sents[jj][sents[jj].size()-ii]!=sents[jj-1][sents[jj-1].size()-ii])
            {
                eq = false;
                break;
            }
        }
        if (!eq) break;
    }
    if (ii==1&&!eq) cout << "nai";
    else{
        cout << sents[0].substr(sents[0].size()-ii+1,ii-1);
    }
    return 0;
}
