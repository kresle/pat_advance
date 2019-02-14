# include<bits/stdc++.h>
#include <iostream>
using namespace std;
vector<bool>prime((int)(1e5));//题目表长最大为10的4次方，可以建立一个10的5次方以内的素数表
int main(){
    int MSize,N,M,sum=0,a;
    scanf("%d%d%d",&MSize,&N,&M);
    prime[0]=prime[1]=true;
    for(int i=2;i<prime.size();++i)//埃氏筛法建立素数表
        if(!prime[i])
            for(int j=i*2;j<prime.size();j+=i)
                prime[j]=true;
    while(prime[MSize])//找到大于或等于给定表长的最小素数
        ++MSize;
    int table[MSize]={0};//哈希表
    for(int i=0;i<N;++i){
        scanf("%d",&a);
        int k=a%MSize;
        for(int j=0;j<=MSize&&table[k]!=0;++j,k=(a+j*j)%MSize);//查找元素能够插入的位置
        if(table[k]==0)//该元素能插入
            table[k]=a;
        else//该元素不能插入
            printf("%d cannot be inserted.\n",a);
    }
    for(int i=0;i<M;++i){//统计要进行查找的元素的总查找长度
        scanf("%d",&a);
        int k=a%MSize,j=0;
        for(;j<=MSize&&table[k]!=0&&table[k]!=a;++j,k=(a+j*j)%MSize);//统计当前查找元素的查找长度
        sum+=j>MSize?j:j+1;//累加到总查找长度
        cout << a << " " << (j>MSize?j:j+1) << endl;
    }
    printf("%.1f\n",sum*1.0/M);//输出
    return 0;
}
