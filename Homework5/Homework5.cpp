#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#include <cmath>
using namespace std;
const int MAXN = 50;
class AVL
{
    struct Node
    {
        int Data, Size, Height;
        Node *LCh, *RCh;
        Node()
        {
            LCh = RCh = NULL;
        }
    };
    Node Root;
    typedef Node * NodeP;
    int GetHeight(NodeP x)
    {
        if(x == NULL)
            return 0;
        else
            return x->Height;
    }
    int GetSize(NodeP x)
    {
        if(x == NULL)
            return 0;
        else
            return x->Size;
    }
    NodeP LL(NodeP x)
    {
        NodeP Tmp = x->LCh->RCh, Res = x->LCh;
        Res->RCh = x;

        x->RCh->Height = max(GetHeight(x->RCh->LCh), GetHeight(x->RCh->RCh)) + 1;
        x->Height = max(GetHeight(x->LCh), GetHeight(x->RCh)) + 1;
        
        x->RCh->Size = max(GetSize(x->RCh->LCh), GetSize(x->RCh->RCh)) + 1;
        x->Size = max(GetSize(x->LCh), GetSize(x->RCh)) + 1;
    }
    NodeP RR(NodeP x)
    {
        NodeP Tmp = x->RCh->LCh, Res = x->RCh;
        Res->LCh = x;

        x->LCh->Height = max(GetHeight(x->LCh->RCh), GetHeight(x->LCh->LCh)) + 1;
        x->Height = max(GetHeight(x->RCh), GetHeight(x->LCh)) + 1;
        
        x->LCh->Size = max(GetSize(x->LCh->RCh), GetSize(x->LCh->LCh)) + 1;
        x->Size = max(GetSize(x->RCh), GetSize(x->LCh)) + 1;
    }
    NodeP LR(NodeP x)
    {
        x->LCh = RR(x->LCh);
        return LL(x);
    }
    NodeP RL(NodeP x)
    {
        x->RCh = LL(x->RCh);
        return RR(x);
    }
    void Maintain(NodeP &x)
    {
        
    }
    void Insert(NodeP &x, int Data)
    {
        if(x == NULL)
        {
            x = new Node;
            x->Data = Data;
            x->Size = 1;
            return;
        }
        x->Size++;
        if(x->Data > Data) return Insert(x->LCh, Data);
        else return Insert(x->RCh, Data);
    }
    int Delete(NodeP &x, int Data)
    {
        x->Data--;
        if(x->Data == Data || (Data < x->Data && x->LCh == NULL) || (Data > x->Data && x->RCh == NULL))
        {
            int Res = x->Data;
            if(x->LCh == NULL) x = x->RCh;
            else if(x->RCh == NULL) x = x->LCh;
            else x->Data = Delete(x->LCh, Data + 1);
            return Res;
        }
        if(x->Data > Data) return Delete(x->LCh, Data);
        else return Delete(x->RCh, Data);
    }
};