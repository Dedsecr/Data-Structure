#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 50;
struct Text
{
    int Length;
    double Frequency[126];
    Text()
    {
        Length = 0;
        for (int i = 0; i < 126; ++i)
            Frequency[i] = 0;
    }
};
struct HCode
{
    vector<int>Code;
    char Text;
};
struct HuffmanCode
{
    vector<HCode>Code;
};
int Stack[MAXN], StackP;
int ChildNum = 2;
struct TreeNode
{
    //int WPL;
    char Text;
    double Val;
    vector<TreeNode *>Ch;
    TreeNode()
    {
        Text = 0;
        //WPL = 0;
        Val = 0;
        Ch.clear();
    }
};

typedef TreeNode * Tree;
typedef TreeNode * Node;
struct Cmp
{
    bool operator() (const Tree a,const Tree b)
    {
        return a->Val < b->Val;
    }
};
priority_queue<Tree, vector<Tree>, Cmp>Q;
/*int CalcWPL(Tree &T1, Tree &T2)
{
    return T1->WPL + T2->WPL + T1->Val + T2->Val;
}
int CalcWPL(Tree &T)
{
    return T->WPL + T->Val;
}*/
/*
int CalcVal(Tree &T1, Tree &T2)
{
    return T1->Val + T2->Val;
}
Tree MergeTrees(Tree &T1,Tree &T2)
{
    Tree T = new TreeNode;
    //T->WPL = CalcWPL(T1, T2);
    T->Val = CalcVal(T1, T2);
}*/
Tree BuildHuffmanTree(Text &text)
{
    while(!Q.empty())
        Q.pop();
    for (int i = 0; i < 126; ++i)
        if(abs(text.Frequency[i]) > 1e-8)
        {
            Tree T = new TreeNode;
            T->Val = text.Frequency[i];
            T->Text = i;
            Q.push(T);
        }
    while(Q.size() != 1)
    {
        int End = Q.size();
        if(End > ChildNum)
            End = ChildNum;
        Tree T = new TreeNode;
        for(int i = 1; i <= End; ++i)
        {
            Tree now = Q.top();
            Q.pop();
            T->Val += now->Val;
            T->Ch.push_back(now);
        }
        Q.push(T);
    }
    return Q.top();
}
Text GetFrequency()
{
    Text Res;
    string S = "", now;
    while(getline(cin, now))
    {
        S += now;
    }
    int Length = S.length();
    Res.Length = Length;
    for (int i = 0; i < Length; ++i)
    {
        Res.Frequency[S[i]] += 1;
    }
    for (int i = 0; i < 126; ++i)
    {
        Res.Frequency[i] /= Length;
    }
    return Res;
}
void GetHC(Tree Root, HuffmanCode *Code)
{
    int Size = Root->Ch.size();
    if(!Size)
    {
        if(!Root->Text)
        {
            cerr << "Error in " << __LINE__;
            exit(-1);
        }
        HCode HC;
        HC.Text = Root->Text;
        for (int i = 1; i <= StackP; ++i)
            HC.Code.push_back(Stack[i]);
        Code->Code.push_back(HC);
        return;
    }
    for (int i = 0; i < Size; ++i)
    {
        Stack[++StackP] = i;
        GetHC(Root->Ch[i], Code);
    }
}
void PrintHC(HuffmanCode *Code)
{
    int Size = Code->Code.size();
    for (int i = 0; i < Size; ++i)
    {
        cout << Code->Code[i].Text << " : ";
        int Siz = Code->Code[i].Code.size();
        for (int j = 0; j < Siz; ++j)
        {
            cout << Code->Code[i].Code[j];
        }
        puts("");
    }
}
void GetHuffmanCode(Tree Root)
{
    HuffmanCode *Code = new HuffmanCode;
    StackP = 0;
    GetHC(Root, Code);
    PrintHC(Code);
}
int main()
{
    freopen("Expriment2_In.txt", "r", stdin);
    freopen("Expriment2_Out.txt", "w", stdout);
    
    Text text = GetFrequency();
    Tree T = BuildHuffmanTree(text);
    GetHuffmanCode(T);
    return 0;
}