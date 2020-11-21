#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
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
            Size = Height = 0;
        }
    };
public:
    typedef Node * NodeP;
    NodeP Root;
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
    void UpdateHS(NodeP x)
    {
        if(x == NULL)
            return;
        x->Height = max(GetHeight(x->LCh), GetHeight(x->RCh)) + 1;
        x->Size = GetSize(x->LCh) + GetSize(x->RCh) + 1;
    }
    NodeP LL(NodeP x)
    {
        NodeP Tmp = x->LCh->RCh, Res = x->LCh;
        Res->RCh = x;
        x->LCh = Tmp;

        UpdateHS(x->RCh);
        UpdateHS(x);

        return Res;
    }
    NodeP RR(NodeP x)
    {
        NodeP Tmp = x->RCh->LCh, Res = x->RCh;
        Res->LCh = x;
        x->RCh = Tmp;

        UpdateHS(x->LCh);
        UpdateHS(x);

        return Res;
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
        if(GetHeight(x->LCh) == GetHeight(x->RCh) + 2)
        {
            if(GetHeight(x->LCh->LCh) > GetHeight(x->LCh->RCh))
                x = LL(x), cout << "LL\n";
            else
                x = LR(x), cout << "LR\n";
        }
        else if(GetHeight(x->RCh) == GetHeight(x->LCh) + 2)
        {
            if(GetHeight(x->RCh->RCh) > GetHeight(x->RCh->LCh))
                x = RR(x), cout << "RR\n";
            else
                x = RL(x), cout << "RL\n";
        }
        UpdateHS(x);
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
        if(x->Data > Data) Insert(x->LCh, Data);
        else if(x->Data < Data)
            Insert(x->RCh, Data);
        Maintain(x);
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
        Maintain(x);
    }
    int Rank(NodeP x, int Data)
    {
        if(x == NULL)
            return -1e9;
        if(x->Data == Data)
            return 1 + GetSize(x->LCh);
        else if(x->Data < Data)
            return GetSize(x->LCh) + 1 + Rank(x->RCh, Data);
        else
            return Rank(x->LCh, Data);
    }
    void GetSortedDFS(NodeP x, string &Res)
    {
        if(x == NULL)
            return;
        GetSortedDFS(x->LCh, Res);
        Res += to_string(x->Data);
        Res += " ";
        GetSortedDFS(x->RCh, Res);
    }
    string GetSorted()
    {
        string Res;
        GetSortedDFS(Root, Res);
        return Res;
    }
};
AVL Tree;
int main()
{
    //freopen("Homework5_In.txt", "r", stdin);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        Tree.Insert(Tree.Root, x);
    }
    cout << Tree.GetSorted();
    return 0;
}