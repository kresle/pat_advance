#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct playPair
{
    int arvTime;
    int playTime;
    bool isVip;
    playPair(int at, int ptm, int vp): arvTime(at), isVip(vp) {
        if (ptm<=120) playTime = ptm;
        else playTime = 120;
    }

};

vector<playPair*> players;

int nn, kk , mm ;

int main()
{
    cin >> nn;
    int hour, minute, second, playMinute, vip;
    char cc;
    playPair* tmpPair;
    while(nn--)
    {
        cin >> hour >> cc >> minute >> cc >> second >> playMinute >> vip;
        tmpPair = new playPair( (hour-8)*3600+minute*60+second, playMinute, vip);
        players.push_back(tmpPair);
    }
}