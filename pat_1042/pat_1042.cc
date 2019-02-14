#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

int nn;
int shuffle[54];
vector<int> cards;
vector<int> tmpCards;
char cardType[] = {'S','H','C','D'};

int main()
{
    cin >> nn;
    for(int ii=0;ii<54;ii++) {cin >> shuffle[ii];shuffle[ii]--;}
    cards.resize(54);
    tmpCards.resize(54);
    for(int ii=0;ii<54;ii++) cards[ii]=ii;
    for(int ii=0;ii<nn;ii++)
    {
        for(int jj=0;jj<54;jj++)
            tmpCards[shuffle[jj]] = cards[jj];
        cards = tmpCards;
    }
    for(int ii=0;ii<53;ii++)
    {
        if (cards[ii]>=52)
        {
            printf("J%d ", cards[ii]-51);
        }
        else
        {
            printf("%c%d ", cardType[cards[ii]/13], cards[ii]%13+1);
        }
    }
    int ii=53;
    if (cards[ii]>=52)
    {
        printf("J%d", cards[ii]-51);
    }
    else
    {
        printf("%c%d", cardType[cards[ii]/13], cards[ii]%13+1);
    }
    return 0;
}