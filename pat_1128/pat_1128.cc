#include <iostream>
#include <vector>
using namespace std;

int nn;
vector<int> board;

bool validQueen(int rr)
{
    if (rr==nn) return true;
    for(int ii=0;ii<rr;ii++)
    {
        if (board[ii] == board[rr]) return false;
        if (board[ii]-board[rr]==ii-rr||board[rr]-board[ii]==rr-ii) return false;
    }
    return validQueen(rr+1);
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int kk;
    cin >> kk;
    while(kk--)
    {
        cin >> nn;
        board.resize(nn);
        for(int ii=0;ii<nn;ii++) cin >> board[ii];
        cout << ((validQueen(0))?"YES":"NO") << endl;
    }
    return 0;
}