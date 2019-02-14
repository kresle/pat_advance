#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string SS;
    cin >> SS;
    int nn = SS.size();
    int n1=0;
    for(int n2=3;n2<=nn;n2++)
    {
        for(int ii=0;ii<=n2;ii++)
        {
            if(2*ii+n2-2==nn)
            {
                if (ii>n1) n1=ii;
            }
        }
    }
    int n2 = nn+2-2*n1;
    for(int ii=0;ii<n1-1;ii++)
    {
        cout << SS[ii];
        for(int jj=0;jj<n2-2;jj++) cout << " ";
        cout << SS[nn-1-ii] << endl;
    }
    cout << SS.substr(n1-1,n2);
    return 0;
}
