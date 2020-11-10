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
const int MAXM = MAXN * MAXN << 1;
struct Result_SingleSource
{
    int S, Dis[MAXN];
};
struct Result_AllSource
{
    int Dis[MAXN][MAXN];
};
struct Graph
{
    int Next[MAXM], To[MAXM], V[MAXM], Head[MAXN];
    int Tot;
    Graph()
    {
        Tot = 1;
        memset(Next, 0, sizeof(Next));
        memset(To, 0, sizeof(To));
        memset(V, 0, sizeof(V));
        memset(Head, 0, sizeof(Head));
    }
    void Add(int x,int y,int v)
    {
        Next[++Tot] = Head[x];
        Head[x] = Tot;
        To[Tot] = y;
        V[Tot] = v;
    }
};
struct Node
{
    int x, Dis;
    Node(){}
    Node(int _x,int _D)
    {
        x = _x;
        Dis = _D;
    }
};
class Priority_Queue//小根堆
{
private:
    Node Heap[MAXN << 2];
    int Length;
public:
    Priority_Queue()
    {
        Length = 0;
    }
    bool empty()
    {
        return !Length;
    }
    int size()
    {
        return Length;
    }
    void push(Node x)
    {
        Heap[++Length] = x;
        int Pos = Length;
        while(Pos > 1)
        {
            if(Heap[Pos >> 1].Dis > Heap[Pos].Dis)
                swap(Heap[Pos >> 1], Heap[Pos]);
            Pos >>= 1;
        }
    }
    Node top()
    {
        return Heap[1];
    }
    void pop()
    {
        if(!Length)
        {
            cerr << "Error in" << __LINE__;
            exit(-1);
        }
        swap(Heap[1], Heap[Length]);
        Length--;
        if(Length == 0)
            return;
        int Pos = 1;
        while(Length >= (Pos << 1))
        {
            if((Pos << 1 | 1) <= Length)
            {
                if(Heap[Pos].Dis > min(Heap[Pos << 1].Dis, Heap[Pos << 1 | 1].Dis))
                {
                    if(Heap[Pos << 1].Dis < Heap[Pos << 1 | 1].Dis)
                        swap(Heap[Pos << 1], Heap[Pos]), Pos <<= 1;
                    else swap(Heap[Pos << 1 | 1], Heap[Pos]), Pos = Pos << 1 | 1;
                }
                else
                    break;
            }
            else
            {
                if(Heap[Pos].Dis > Heap[Pos << 1].Dis)
                    swap(Heap[Pos << 1], Heap[Pos]), Pos <<= 1;
                else
                    break;
            }
        }
    }
};
Priority_Queue Q;
Graph G;
bool Vis[MAXN];
Result_SingleSource Dijkstra(int S)
{
    memset(Vis, 0, sizeof(Vis));
    Result_SingleSource Res;
    while(!Q.empty())
        Q.pop();
    Res.S = S;
    memset(Res.Dis, 123, sizeof(Res.Dis));
    Q.push(Node(S, 0));
    Vis[S] = 1;
    Res.Dis[S] = 0;
    while(!Q.empty())
    {
        Node Now = Q.top();
        Q.pop();
        int x = Now.x;
        for (int i = G.Head[x]; i; i = G.Next[x])
            if(Res.Dis[G.To[i]] > Res.Dis[G.To[i]] + G.V[i])
            {
                Res.Dis[G.To[i]] = Res.Dis[G.To[i]] + G.V[i];
                if(!Vis[G.To[i]])
                    Q.push(Node(G.To[i], Res.Dis[G.To[i]]));
            }
    }
    return Res;
}
Result_AllSource Floyd()
{
    Result_AllSource Res;
    memset(Res.Dis, 123, sizeof(Res.Dis));
    for (int i = 0; i < MAXN; ++i)
        Res.Dis[i][i] = 0;
    for (int x = 0; x < MAXN; ++x)
        for (int i = G.Head[x]; i; i = G.Next[x])
            Res.Dis[x][G.To[i]] = G.V[i];
    for (int k = 0; k < MAXN; ++k)
        for (int i = 0; i < MAXN; ++i)
            for (int j = 0; j < MAXN; ++j)
                Res.Dis[i][j] = min(Res.Dis[i][j], Res.Dis[i][k] + Res.Dis[k][j]);
    return Res;
}