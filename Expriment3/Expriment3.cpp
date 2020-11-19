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
//单源最短路搜索的结果
struct Result_SingleSource
{
    int S, Dis[MAXN];
    Result_SingleSource()
    {
        for (int i = 0; i < MAXN; ++i)
            Dis[i] = 1e9;
    }
};
//多源最短路搜索的结果
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
//多源最短路搜索的路径结果
struct Result_Path
{
    string Path[MAXN];
    Result_Path()
    {
        for (int i = 0; i < MAXN; ++i)
            Path[i] = "";
    }
};
//图的存储结构
struct Graph
{
    int n, m;
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
    void Add(int x, int y, int v)
    {
        Next[++Tot] = Head[x];
        Head[x] = Tot;
        To[Tot] = y;
        V[Tot] = v;
    }
};
//点
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
//输入图
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
//把AllSource转换成SingleSource
Result_SingleSource AllSource2SingleSource(Result_AllSource AS, int S)
{
    Result_SingleSource Res;
    Res.S = S;
    for (int i = 0; i < MAXN; ++i)
        Res.Dis[i] = AS.Dis[S][i];
    return Res;
}
//Dijkstra算法实现
Result_SingleSource Dijkstra(int S)
{
    memset(Vis, 0, sizeof(Vis));
    Result_SingleSource Res;
    while (!Q.empty())
        Q.pop();
    Res.S = S;
    Q.push(Node(S, 0));
    Res.Dis[S] = 0;
    while (!Q.empty())
    {
        Node Now = Q.top();
        Q.pop();
        int x = Now.x;
        if(Vis[x])
            continue;
        Vis[x] = 1;
        for (int i = G.Head[x]; i; i = G.Next[i])
            if (Res.Dis[G.To[i]] > Res.Dis[x] + G.V[i])
            {
                Res.Dis[G.To[i]] = Res.Dis[x] + G.V[i];
                if (!Vis[G.To[i]])
                    Q.push(Node(G.To[i], Res.Dis[G.To[i]]));
            }
    }
    return Res;
}
//Floyd算法实现
Result_AllSource Floyd()
{
    Result_AllSource Res;
    for (int i = 0; i < MAXN; ++i)
        Res.Dis[i][i] = 0;
    for (int x = 0; x < MAXN; ++x)
        for (int i = G.Head[x]; i; i = G.Next[i])
            Res.Dis[x][G.To[i]] = G.V[i];
    for (int k = 0; k < MAXN; ++k)
        for (int i = 0; i < MAXN; ++i)
            for (int j = 0; j < MAXN; ++j)
                Res.Dis[i][j] = min(Res.Dis[i][j], Res.Dis[i][k] + Res.Dis[k][j]);
    return Res;
}
//找路径的DFS
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
    
    StackP--;
}
//找从x开始的所有最短路径
Result_Path FindPath(int x, Result_SingleSource SS)
{
    StackP = 0;
    memset(Vis, 0, sizeof(Vis));
    Result_Path Res;
    FindPathDFS(x, Res, SS, 0);
    return Res;
}
//输出S到每个顶点的路径
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
//输出S到Target的路径
void Print_Single_Result_Path(int S, int Target, Result_Path &Res)
{
    if (Res.Path[Target].length() == 0)
        return;
    cout << S << " TO " << Target << " : " << Res.Path[Target] << "\n";
}
//输出任意两个顶点间的最短路径长度和最短路径
void GetEveryShortestLengthAndPath()
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
//找出图中每个顶点到某个指定顶点Target的最短路径
void GetSingleTargetShortestPath(int Target)
{
    Result_AllSource Res = Floyd();
    for (int x = 1; x <= G.n; ++x)
    {
        Result_Path RP = FindPath(x, AllSource2SingleSource(Res, x));
        Print_Single_Result_Path(x, Target, RP);
    }
}
//对于某对顶点S和T，找出S到T和T到S的一条最短路径 
void GetSingleShortestPath(int S, int T)
{
    Result_SingleSource Res = Dijkstra(S);
    Result_Path RP = FindPath(S, Res);
    Print_Single_Result_Path(S, T, RP);

    Res = Dijkstra(T);
    RP = FindPath(T, Res);
    Print_Single_Result_Path(T, S, RP);
}
//计算有向图的可达矩阵
void GetReachableMatrix()
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
    //freopen("Expriment3_In.txt", "r", stdin);
    //freopen("Expriment3_Out.txt", "w", stdout);
    while(1)
    {
        int OP;
        printf(
            "*******************************************\n"
            "*                                         *\n"
            "*    0.Exit                               *\n"
            "*    1.Input And Build                    *\n"
            "*    2.Get Every Shortest Length And Path *\n"
            "*    3.Get Single Target Shortest Path    *\n"
            "*    4.Get Single Shortest Path           *\n"
            "*    5.Get Reachable Matrix               *\n"
            "*                                         *\n"
            "*******************************************\n");
        cin >> OP;
        if(OP == 0)
            break;
        else if(OP == 1)
        {
            InputAndBuild();
        }
        else if(OP == 2)
        {
            GetEveryShortestLengthAndPath();
        }
        else if(OP == 3)
        {
            puts("Please input your target:");
            int Target;
            cin >> Target;
            GetSingleTargetShortestPath(Target);
        }
        else if(OP == 4)
        {
            puts("Please input your starting point and target:");
            int S, T;
            cin >> S >> T;
            GetSingleShortestPath(S, T);
        }
        else if(OP == 5)
        {
            GetReachableMatrix();
        }
    }
    return 0;
}