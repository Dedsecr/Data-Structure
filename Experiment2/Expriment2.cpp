#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
using namespace std;
const int MAXN = 300;
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
struct TreeNode
{
    int WPL;
    double Val;
    TreeNode * LCh;
    TreeNode * RCh;
    TreeNode()
    {
        WPL = 0;
        Val = 0;
        this->LCh = NULL;
        this->RCh = NULL;
    }
};
typedef TreeNode * Tree;
typedef TreeNode * Node;
int CalcWPL(Tree &T1, Tree &T2)
{
    return T1->WPL + T2->WPL + T1->Val + T2->Val;
}
int CalcWPL(Tree &T)
{
    return T->WPL + T->Val;
}
int CalcVal(Tree &T1, Tree &T2)
{
    return T1->Val + T2->Val;
}
Tree MergeTrees(Tree &T1,Tree &T2)
{
    Tree T = new TreeNode;
    T->WPL = CalcWPL(T1, T2);
    T->Val = CalcVal(T1, T2);
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
