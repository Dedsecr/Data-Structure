#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
using namespace std;
const int MAXN = 100;
struct TreeNode
{
    int data;
    bool vis;
    TreeNode * LCh;
    TreeNode * RCh;
    TreeNode()
    {
        this->LCh = NULL;
        this->RCh = NULL;
    }
};
typedef TreeNode * Tree;
typedef TreeNode * Node;
void Get_PreOrder_WithRecursion(Tree &Root)
{
    if(Root->LCh != NULL)
        Get_PreOrder_WithRecursion(Root->LCh);
    cout << Root->data << " ";
    if(Root->RCh != NULL)
        Get_PreOrder_WithRecursion(Root->RCh);    
}
void Get_InOrder_WithRecursion(Tree &Root)
{
    cout << Root->data << " ";
    if(Root->LCh != NULL)
        Get_InOrder_WithRecursion(Root->LCh);
    if(Root->RCh != NULL)
        Get_InOrder_WithRecursion(Root->RCh);    
}
void Get_PostOrder_WithRecursion(Tree &Root)
{
    if(Root->RCh != NULL)
        Get_PostOrder_WithRecursion(Root->RCh);
    cout << Root->data << " ";
    if(Root->LCh != NULL)
        Get_PostOrder_WithRecursion(Root->LCh);
}
void Ini_vis(Tree &Root)
{
    Root->vis = 0;
    if(Root->LCh != NULL)
        Get_InOrder_WithRecursion(Root->LCh);
    if(Root->RCh != NULL)
        Get_InOrder_WithRecursion(Root->RCh);  
}
void Get_PreOrder_WithoutRecursion(Tree &Root)
{
    Ini_vis(Root);
    stack<Tree>S;
    S.push(Root);
    while(!S.empty())
    {
        Node x = S.top();
        x->vis = 1;
        if(x->LCh != NULL && !x->LCh->vis)
            S.push(x->LCh);
        else
        {
            cout << x->data <<" ";
            S.pop();
            if(x->RCh != NULL && !x->RCh->vis)
                S.push(x->RCh);
        }
    }
    puts("");
}
void Get_InOrder_WithoutRecursion(Tree &Root)
{
    Ini_vis(Root);
    stack<Tree>S;
    S.push(Root);
    while(!S.empty())
    {
        Node x = S.top();
        x->vis = 1;
        cout << x->data <<" ";
        if(x->LCh != NULL && !x->LCh->vis)
            S.push(x->LCh);
        else
        {
            S.pop();
            if(x->RCh != NULL && !x->RCh->vis)
                S.push(x->RCh);
        }
    }
    puts("");
}
void Get_PostOrder_WithoutRecursion(Tree &Root)
{
    Ini_vis(Root);
    stack<Tree>S;
    S.push(Root);
    while(!S.empty())
    {
        Node x = S.top();
        x->vis = 1;
        if(x->RCh != NULL && !x->RCh->vis)
            S.push(x->RCh);
        else
        {
            cout << x->data <<" ";
            S.pop();
            if(x->LCh != NULL && !x->LCh->vis)
                S.push(x->LCh);
        }
    }
    puts("");
}
int Is_CompleteTree(Tree &Root, int Depth, bool &Is)
{
    if(!Root->LCh && Root->RCh)
    {
        Is = 0;
        return Depth + 1;
    }
    if(!Root->LCh && !Root->RCh)
        return Depth + 1;
    int LDepth = Is_CompleteTree(Root->LCh, Depth + 1, Is);
    if(!Is)return LDepth;
    if(Root->RCh)
    {
        int RDepth = Is_CompleteTree(Root->RCh, Depth + 1, Is);
        if(!Is)return max(LDepth, RDepth);
        if(LDepth < RDepth || LDepth - RDepth > 1)
            Is = 0;
        return max(LDepth, RDepth);
    }
    else
    {
        if(LDepth > 1)
            Is = 0;
        return LDepth;
    }
}
