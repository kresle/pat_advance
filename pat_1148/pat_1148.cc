#include <iostream>
#include <vector>
using namespace std;

int nn;
vector<int> claim;
vector<bool> isGood;

int main()
{
    cin >> nn;
    claim.resize(nn+1);
    isGood.resize(nn+1);
    for(int ii=1;ii<=nn;ii++)
    {
        cin >> claim[ii];
    }
    bool foundAns = false;
    for(int ii=1;ii<nn&&!foundAns;ii++)//werewolf 1, liar
    {
        for(int jj=ii+1;jj<=nn&&!foundAns;jj++)//werewolf 2, imposter, telling truth
        {
            fill(isGood.begin(), isGood.end(), 1);
            isGood[ii] = false;
            isGood[jj] = false;
            int liarNo=0, liarNo_ww=0;
            for(int kk=1;kk<=nn;kk++)
            {
                //考察第kk个人说的话是否为真
                int pid = (claim[kk]<0)?-claim[kk]:claim[kk];
                bool id = claim[kk]>0;
                if (isGood[pid]!=id) {
                    if (kk==ii||kk==jj) liarNo_ww++;
                    liarNo++;
                }
            }
            if (liarNo==2&&liarNo_ww==1)
            {
                cout << ii << " " << jj << endl;
                foundAns = true;
            }
        }
    }
    if (!foundAns)
    {
        cout << "No Solution" << endl;
    }
    return 0;
}