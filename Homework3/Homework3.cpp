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
    char data;
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
void BuildTree(string &S, Tree &Root, int &P)
{
    if(P == S.length())
        return;
    if(S[P] != '#')
    {
        Root->data = S[P];
        P++;
        Root->LCh = new TreeNode;
        BuildTree(S, Root->LCh, P);
    }
    else
        P++;
    if(S[P] != '#')
    {
        Root->data = S[P];
        P++;
        Root->RCh = new TreeNode;
        BuildTree(S, Root->RCh, P);
    }
    else
        P++;
}
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
int Is_CompleteTree_DFS(Tree &Root, int Depth, bool &Is)
{
    if(!Root->LCh && Root->RCh)
    {
        Is = 0;
        return Depth + 1;
    }
    if(!Root->LCh && !Root->RCh)
        return Depth + 1;
    int LDepth = Is_CompleteTree_DFS(Root->LCh, Depth + 1, Is);
    if(!Is)return LDepth;
    if(Root->RCh)
    {
        int RDepth = Is_CompleteTree_DFS(Root->RCh, Depth + 1, Is);
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
void Clear_Vis(Tree &Root)
{
    Root->vis = 0;
    if(Root->LCh != NULL)
        Clear_Vis(Root->LCh);
    if(Root->RCh != NULL)
        Clear_Vis(Root->RCh);
}
bool Is_CompleteTree(Tree &Root)
{
    bool Res = 1;
    Clear_Vis(Root);
    Is_CompleteTree_DFS(Root, 1, Res);
    return Res;
}
void Get_MaxWidth_DFS(Tree &Root, int * Width, int Depth)
{
    Width[Depth]++;
    if(Root->LCh != NULL)
        Get_MaxWidth_DFS(Root->LCh, Width, Depth + 1);
    if(Root->RCh != NULL)
        Get_MaxWidth_DFS(Root->RCh, Width, Depth + 1);
}
int Get_MaxWidth(Tree &Root)
{
    int Width[MAXN] = {0}, Res = 0;
    Get_MaxWidth_DFS(Root, Width, 1);
    for (int i = 1; i < MAXN && Width[i]; ++i)
        Res = max(Res, Width[i]);
    return Res;
}
void PrintTree(Tree &Root)
{
    
    if(Root->LCh != NULL)
        cout << Root->LCh->data;
    else
        cout << "#";   
    if(Root->RCh != NULL)
        cout << Root->RCh->data << '\n';
    else
        cout << "#\n";
    if(Root->LCh != NULL)
        PrintTree(Root->LCh);
    if(Root->RCh != NULL)
        PrintTree(Root->RCh);
}
int main()
{
    string S;
    int P = 0;
    Tree Root = new TreeNode;
    cin >> S;
    BuildTree(S, Root, P);
    cout << "&";
    PrintTree(Root);
    return 0;
}
//ABDH##I##E##CF#J##G##