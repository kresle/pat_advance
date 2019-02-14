#include <iostream>
using namespace std;

int main()
{
    int nn;
    cin >> nn;
    int req[nn+1];
    fill(req, req+nn+1, 0);
    int ttl_time = 0;
    for(int ii=1;ii<=nn;ii++)
    {
        cin >> req[ii];
        if (req[ii]>req[ii-1])
        {
            ttl_time+=(req[ii]-req[ii-1])*6;
        }
        if (req[ii]<req[ii-1])
        {
            ttl_time+=(req[ii-1]-req[ii])*4;
        }
    }
    ttl_time+= 5*nn;
    cout << ttl_time << endl;
}