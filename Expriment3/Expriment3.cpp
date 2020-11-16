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
    Result_SingleSource()
    {
        for (int i = 0; i < MAXN; ++i)
            Dis[i] = 1e9;
    }
};
struct Result_AllSource
{
    int Dis[MAXN][MAXN];
    Result_AllSource()
    {
        for (int i = 0; i < MAXN; ++i)
            for (int j = 0; j < MAXN; ++j)
                Dis[i][j] = 1e9;
    }
};
struct Result_Path
{
    string Path[MAXN];
    Result_Path()
    {
        for (int i = 0; i < MAXN; ++i)
            Path[i] = "";
    }
};
struct Graph
{
    int n, m;
    //int Matrix[MAXN][MAXN];
    int Next[MAXM], To[MAXM], V[MAXM], Head[MAXN];
    int Tot;
    Graph()
    {
        Tot = 1;
        memset(Next, 0, sizeof(Next));
        memset(To, 0, sizeof(To));
        memset(V, 0, sizeof(V));
        memset(Head, 0, sizeof(Head));
        //memset(Matrix, -1, sizeof(Matrix));
    }
    void Add(int x, int y, int v)
    {
        Next[++Tot] = Head[x];
        Head[x] = Tot;
        To[Tot] = y;
        V[Tot] = v;
        //Matrix[x][y] = v;
    }
};
struct Node
{
    int x, Dis;
    Node() {}
    Node(int _x, int _D)
    {
        x = _x;
        Dis = _D;
    }
};
class Priority_Queue //小根堆
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
        while (Pos > 1)
        {
            if (Heap[Pos >> 1].Dis > Heap[Pos].Dis)
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
        if (!Length)
        {
            cerr << "Error in" << __LINE__;
            exit(-1);
        }
        swap(Heap[1], Heap[Length]);
        Length--;
        if (Length == 0)
            return;
        int Pos = 1;
        while (Length >= (Pos << 1))
        {
            if ((Pos << 1 | 1) <= Length)
            {
                if (Heap[Pos].Dis > min(Heap[Pos << 1].Dis, Heap[Pos << 1 | 1].Dis))
                {
                    if (Heap[Pos << 1].Dis < Heap[Pos << 1 | 1].Dis)
                        swap(Heap[Pos << 1], Heap[Pos]), Pos <<= 1;
                    else
                        swap(Heap[Pos << 1 | 1], Heap[Pos]), Pos = Pos << 1 | 1;
                }
                else
                    break;
            }
            else
            {
                if (Heap[Pos].Dis > Heap[Pos << 1].Dis)
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
int Stack[MAXN], StackP;
void InputAndBuild()
{
    cin >> G.n >> G.m;
    for (int i = 1; i <= G.m; ++i)
    {
        int x, y, v;
        cin >> x >> y >> v;
        G.Add(x, y, v);
    }
}
Result_SingleSource AllSource2SingleSource(Result_AllSource AS, int S)
{
    Result_SingleSource Res;
    Res.S = S;
    for (int i = 0; i < MAXN; ++i)
        Res.Dis[i] = AS.Dis[S][i];
    return Res;
}
Result_SingleSource Dijkstra(int S)
{
    memset(Vis, 0, sizeof(Vis));
    Result_SingleSource Res;
    while (!Q.empty())
        Q.pop();
    Res.S = S;
    Q.push(Node(S, 0));
    Vis[S] = 1;
    Res.Dis[S] = 0;
    while (!Q.empty())
    {
        Node Now = Q.top();
        Q.pop();
        int x = Now.x;
        for (int i = G.Head[x]; i; i = G.Next[x])
            if (Res.Dis[G.To[i]] > Res.Dis[G.To[i]] + G.V[i])
            {
                Res.Dis[G.To[i]] = Res.Dis[G.To[i]] + G.V[i];
                if (!Vis[G.To[i]])
                    Q.push(Node(G.To[i], Res.Dis[G.To[i]]));
            }
    }
    return Res;
}
Result_AllSource Floyd()
{
    Result_AllSource Res;
    for (int i = 0; i < MAXN; ++i)
        Res.Dis[i][i] = 0;
    for (int x = 0; x < MAXN; ++x)
        for (int i = G.Head[x]; i; i = G.Next[i])
            Res.Dis[x][G.To[i]] = G.V[i],cout<<x<<" "<<G.To[i]<<"***\n";
    for (int k = 0; k < MAXN; ++k)
        for (int i = 0; i < MAXN; ++i)
            for (int j = 0; j < MAXN; ++j)
                Res.Dis[i][j] = min(Res.Dis[i][j], Res.Dis[i][k] + Res.Dis[k][j]);
    return Res;
}
void FindPathDFS(int x, Result_Path &Res, Result_SingleSource &SS, int Sum)
{
    Vis[x] = 1;
    Stack[++StackP] = x;

    for (int i = 1; i <= StackP; ++i)
    {
        Res.Path[x] += to_string(Stack[i]);
        Res.Path[x] += ' ';
    }

    for (int i = G.Head[x]; i; i = G.Next[i])
        if (Sum + G.V[i] == SS.Dis[G.To[i]] && !Vis[G.To[i]])
        {
            FindPathDFS(G.To[i], Res, SS, Sum + G.V[i]);
        }
}
Result_Path FindPath(int x, Result_SingleSource SS)
{
    StackP = 0;
    memset(Vis, 0, sizeof(Vis));
    Result_Path Res;
    FindPathDFS(x, Res, SS, 0);
    return Res;
}
void Print_Every_Result_Path(int S, Result_Path &Res)
{
    for (int i = 1; i <= G.n; ++i)
    {
        if (S == i)
            continue;
        if (Res.Path[i].length() == 0)
            continue;
        cout << S << " TO " << i << " : "  << Res.Path[i] << "\n";
    }
}
void Print_Single_Result_Path(int S, int Target, Result_Path &Res)
{
    if (Res.Path[Target].length() == 0)
        return;
    cout << S << " TO " << Target << " : " << Res.Path[Target] << "\n";
}
void PrintEveryShortestLengthAndPath()
{
    Result_AllSource Res = Floyd();
    for (int i = 1; i <= G.n; ++i, cout << '\n')
        for (int j = 1; j <= G.n; ++j)
            if(Res.Dis[i][j] >= 1e9)
                cout << "-1 ";
            else 
                cout << Res.Dis[i][j] << " ";

    for (int x = 1; x <= G.n; ++x)
    {
        Result_Path RP = FindPath(x, AllSource2SingleSource(Res, x));
        Print_Every_Result_Path(x, RP);
    }
}
void PrintSingleTargetShortestPath(int Target)
{
    Result_AllSource Res = Floyd();
    for (int x = 1; x <= G.n; ++x)
    {
        Result_Path RP = FindPath(x, AllSource2SingleSource(Res, x));
        Print_Single_Result_Path(x, Target, RP);
    }
}
void PirntSingleShortestPath(int S, int T)
{
    Result_SingleSource Res = Dijkstra(S);
    Result_Path RP = FindPath(S, Res);
    Print_Single_Result_Path(S, T, RP);
}
void PrintReachableMatrix()
{
    Result_AllSource Res = Floyd();
    for (int i = 1; i <= G.n; ++i, cout << '\n')
        for (int j = 1; j <= G.n; ++j)
            if (Res.Dis[i][j] >= 1e9)
                cout << "0 ";
            else
                cout << "1 ";
}
int main()
{
    freopen("Expriment3_In.txt", "r", stdin);
    InputAndBuild();
    PrintEveryShortestLengthAndPath();
    return 0;
}