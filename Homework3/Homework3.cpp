#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
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
//按照先序序列建立二叉树的递归过程
void BuildTree(string &S, Tree &Root, int &P)
{
    if(P == S.length())
        return;
    Root->data = S[P];
    P++;
    
    if(S[P] != '#')
    {
        Root->LCh = new TreeNode;
        BuildTree(S, Root->LCh, P);
    }
    else
        P++;
    if(S[P] != '#')
    {
        Root->RCh = new TreeNode;
        BuildTree(S, Root->RCh, P);
    }
    else
        P++;
}
//按照先序序列建立二叉树
Tree InputTree()
{
    string S;
    int P = 0;
    Tree Root = new TreeNode;
    cin >> S;
    BuildTree(S, Root, P);
    return Root;
}
//用递归实现输出先序遍历序列
void Get_PreOrder_WithRecursion(Tree &Root)
{
    cout << Root->data << " ";
    if(Root->LCh != NULL)
        Get_PreOrder_WithRecursion(Root->LCh);
    if(Root->RCh != NULL)
        Get_PreOrder_WithRecursion(Root->RCh);    
}
//用递归实现输出中序遍历序列
void Get_InOrder_WithRecursion(Tree &Root)
{
    if(Root->LCh != NULL)
        Get_InOrder_WithRecursion(Root->LCh);
    cout << Root->data << " ";
    if(Root->RCh != NULL)
        Get_InOrder_WithRecursion(Root->RCh);    
}
//用递归实现输出后序遍历序列
void Get_PostOrder_WithRecursion(Tree &Root)
{
    if(Root->LCh != NULL)
        Get_PostOrder_WithRecursion(Root->LCh);
    if(Root->RCh != NULL)
        Get_PostOrder_WithRecursion(Root->RCh);
    cout << Root->data << " ";
}
//清除Vis标记
void Ini_vis(Tree &Root)
{
    Root->vis = 0;
    if(Root->LCh != NULL)
        Ini_vis(Root->LCh);
    if(Root->RCh != NULL)
        Ini_vis(Root->RCh);  
}
//用非递归实现输出先序遍历序列
void Get_PreOrder_WithoutRecursion(Tree &Root)
{
    Ini_vis(Root);
    stack<Tree>S;
    S.push(Root);
    cout << Root->data << " ";
    while(!S.empty())
    {
        Node x = S.top();
        x->vis = 1;
        if(x->LCh != NULL && !x->LCh->vis)
        {
            S.push(x->LCh);
            cout << x->LCh->data << " ";
        }
        else
        {
            if((x->LCh == NULL || x->LCh->vis) && x->RCh != NULL)
                cout << x->RCh->data << " ";
            S.pop();
            if(x->RCh != NULL && !x->RCh->vis)
                S.push(x->RCh);
        }
    }
    puts("");
}
//用非递归实现输出中序遍历序列
void Get_InOrder_WithoutRecursion(Tree &Root)
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
//用非递归实现输出后序遍历序列
void Get_PostOrder_WithoutRecursion(Tree &Root)
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
        else if(x->RCh != NULL && !x->RCh->vis)
            S.push(x->RCh);
        else
        {
            cout << x->data << " ";
            S.pop();
        }
    }
    puts("");
}
//输出层序遍历序列
void Get_LeverOrder(Tree &Root)
{
    queue<Tree>Q;
    Q.push(Root);
    while(!Q.empty())
    {
        Tree x = Q.front();
        Q.pop();
        cout << x->data << " ";
        if(x->LCh != NULL)
            Q.push(x->LCh);
        if(x->RCh != NULL)
            Q.push(x->RCh);
    }
    puts("");
}
//判断树是否为完全二叉树的深搜过程
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
//判断树是否为完全二叉树
bool Is_CompleteTree(Tree &Root)
{
    bool Res = 1;
    Ini_vis(Root);
    Is_CompleteTree_DFS(Root, 1, Res);
    return Res;
}
//输出层序遍历序列的深搜过程。
void Get_MaxWidth_DFS(Tree &Root, int * Width, int Depth)
{
    Width[Depth]++;
    if(Root->LCh != NULL)
        Get_MaxWidth_DFS(Root->LCh, Width, Depth + 1);
    if(Root->RCh != NULL)
        Get_MaxWidth_DFS(Root->RCh, Width, Depth + 1);
}
//输出层序遍历序列
int Get_MaxWidth(Tree &Root)
{
    int Width[MAXN] = {0}, Res = 0;
    Get_MaxWidth_DFS(Root, Width, 1);
    for (int i = 1; i < MAXN && Width[i]; ++i)
        Res = max(Res, Width[i]);
    return Res;
}
//打印根为Root的树，共n行，每行输出该节点、该节点左儿子、该节点右儿子，若无儿子则输出#
void PrintTree(Tree &Root)
{
    cout << Root->data;
    if(Root->LCh != NULL)
        cout << Root->LCh->data;
    else
        cout << "#";   
    if(Root->RCh != NULL)
        cout << Root->RCh->data << '\n';
    else
        cout << "#" << '\n';
    if(Root->LCh != NULL)
        PrintTree(Root->LCh);
    if(Root->RCh != NULL)
        PrintTree(Root->RCh);
}
int main()
{
    //输入二叉树
    Tree Root = InputTree();

    //输出二叉树，共n行，每行输出该节点、该节点左儿子、该节点右儿子，若无儿子则输出#
    puts("Your Tree:");
    PrintTree(Root);

    //分别用递归和非递归实现输出先序遍历序列
    puts("PreOrder_WithRecursion:");
    Get_PreOrder_WithRecursion(Root);
    cout << '\n';
    puts("PreOrder_WithoutRecursion:");
    Get_PreOrder_WithoutRecursion(Root);
    cout << '\n';

    //分别用递归和非递归实现输出中序遍历序列
    puts("InOrder_WithRecursion:");
    Get_InOrder_WithRecursion(Root);
    cout << '\n';
    puts("InOrder_WithoutRecursion:");
    Get_InOrder_WithoutRecursion(Root);
    cout << '\n';

    //分别用递归和非递归实现输出后序遍历序列
    puts("PostOrder_WithRecursion:");
    Get_PostOrder_WithRecursion(Root);
    cout << '\n';
    puts("PostOrder_WithoutRecursion:");
    Get_PostOrder_WithoutRecursion(Root);
    cout << '\n';

    //输出层序遍历序列
    puts("LeverOrder:");
    Get_LeverOrder(Root);
    cout << '\n';

    //判断树是否为完全二叉树
    puts("Complete_Tree?");
    cout << (Is_CompleteTree(Root) ? "YES" : "NO") << endl;

    //输出树的宽度
    puts("Max_Width:");
    cout << Get_MaxWidth(Root) << endl;

    return 0;
}
//ABDH##I##E##CF#J##G##