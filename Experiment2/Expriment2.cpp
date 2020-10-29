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
struct HuffmanCode
{
    
};
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
void BuildHuffmanTree(Text &text)
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
