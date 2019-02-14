#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

int nn;
int hh, ww;
vector<int> nums;
vector<vector<int>> ans;

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn;
    nums.reserve(nn), nums.resize(nn);
    for (int ii = 0; ii < nn; ii++)
        cin >> nums[ii];
    sort(nums.rbegin(), nums.rend());

    hh = sqrt(nn);
    while (nn % hh != 0)
        hh++;
    ww = nn / hh;
    if (ww > hh)
        swap(ww, hh);

    ans.reserve(hh), ans.resize(hh, vector<int>(ww));

    int ih = hh - 1, iw = ww - 1;
    int ir = 0, ic = 0;
    int idx = 0;
    while (ih > 0 && iw >= 0)
    {
        for (int ii = 0; ii < iw && idx < nn; ii++)
            ans[ir][ic++] = nums[idx++];
        for (int ii = 0; ii < ih && idx < nn; ii++)
            ans[ir++][ic] = nums[idx++];
        for (int ii = 0; ii < iw && idx < nn; ii++)
            ans[ir][ic--] = nums[idx++];
        for (int ii = 0; ii < ih && idx < nn; ii++)
            ans[ir--][ic] = nums[idx++];
        ir++, ic++;
        ih -= 2, iw -= 2;
    }
    if (ih == 0 && iw == 0 && idx < nn)
        ans[ir][ic] = nums[idx];
    for (int ii = 0; ii < hh; ii++)
    {
        cout << ans[ii][0];
        for (int jj = 1; jj < ww; jj++)
            cout << " " << ans[ii][jj];
        cout << endl;
    }
    return 0;
}
