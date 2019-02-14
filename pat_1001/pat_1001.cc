#include <iostream>
using namespace std;

int main()
{
  int a,b,c;
  string ss="";
  string rpr;
  cin >>a >>b;
  c = a+b;
  if (c>-999 && c <999) 
  {
      cout << c;
      return 0;
  }
  if (c<0) {c=-c;ss="-";}
  int ii=0;
  while(c!=0)
  {
      ii++;
      rpr.push_back(c%10+'0');
      c/=10;
      if (c!=0&&ii%3==0) rpr.push_back(',');
  }
  cout << ss;
  for(int ii=rpr.size()-1;ii>=0;ii--) cout<<rpr[ii];
  return 0;
}