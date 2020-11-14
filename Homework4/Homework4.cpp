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
//遍历结果的结构体
struct Result
{
    vector<int>Sequence;
    int ID[MAXN];
    vector<int>TreeMatrix[MAXN];
    Result()
    {
        Sequence.clear();
        for (int i = 0; i < MAXN; ++i)
            TreeMatrix[i].clear();
        memset(ID, 0, sizeof(ID));
    }
    //输出遍历结果
    void Print() 
    {
        puts("Sequence:");
        int Size = Sequence.size();
        for (int i = 0; i < Size; ++i)
            cout << Sequence[i] << " ";
        puts("");

        puts("Node  ID");
        for (int i = 0; i < MAXN; ++i)
            if(ID[i])
                cout << "  " << i << " : " << ID[i] << "\n";
        puts("");
    }
};
//邻接矩阵的存储结构
class AdjacencyMatrix
{
private:
    int Matrix[MAXN][MAXN];//邻接矩阵
    bool Visited[MAXN], Appeared[MAXN];//该节点是否访问过；该节点是否出现过
    int n, m;//节点的数量和边的数量 

public:
    AdjacencyMatrix()
    {
        memset(Matrix, 0, sizeof(Matrix));
        memset(Appeared, 0, sizeof(Appeared));
    }
    /*AdjacencyMatrix(int _n, int _m)
    {
        n = _n;
        m = _m;
        
    }*/
    //清空邻接矩阵
    void Clear()
    {
        memset(Matrix, 0, sizeof(Matrix));
        memset(Appeared, 0, sizeof(Appeared));
    }
    //遍历前初始化
    void Initialization()
    {
        for(int i = 0; i < MAXN; ++i)
            Visited[i] = 0;
    }
    //获取x到y是否有边
    int GetMatrixEle(int x, int y)
    {
        return Matrix[x][y];
    }
    //邻接矩阵插入
    void Insert(int x, int y)
    {
        Matrix[x][y] = 1;
        Appeared[x] = 1;
        Appeared[y] = 1;
    }
    //建立邻接矩阵
    void InputandBuild()
    {
        Clear();
        cin >> n >> m;
        for (int i = 1; i <= m; ++i)
        {
            int x, y;
            cin >> x >> y;
            Insert(x, y);
        }
    }
    //深度优先搜索的遍历过程
    void DFS(int x,int &Count, Result &Res)
    {
        Visited[x] = 1;
        Res.ID[x] = ++Count;
        Res.Sequence.push_back(x);
        for (int i = 0; i < MAXN; ++i)
        {
            if(!GetMatrixEle(x, i))
                continue;
            int To = i;
            if(!Visited[To])
            {
                Res.TreeMatrix[x].push_back(To);
                DFS(To, Count, Res);
            }
        }
    }
    //用递归实现深度优先搜索
    Result DFSWithRecursion()
    {
        Result Res;
        int Count = 0;
        Initialization();
        for(int i = 0; i < MAXN; ++i)
            if(!Visited[i] && Appeared[i])
                DFS(i, Count, Res);
        return Res;
    }
    //用非递归实现深度优先搜索
    Result DFSWithoutRecursion()
    {
        Result Res;
        stack<int>S;
        Initialization();
        int Count = 0;
        for(int Now = 0; Now < MAXN; ++Now)
            if(!Visited[Now] && Appeared[Now])
            {
                S.push(Now);
                Visited[Now] = 1;
                while(!S.empty())
                {
                    int x = S.top();
                    S.pop();
                    Res.ID[x] = ++Count;
                    Res.Sequence.push_back(x);
                    for (int i = 0; i < MAXN; ++i)
                    {
                        if(!Matrix[x][i])
                            continue;
                        int To = i;
                        if(!Visited[To])
                        {
                            Res.TreeMatrix[x].push_back(To);
                            Visited[To] = 1;
                            S.push(To);
                        }
                    }
                }
            }
        return Res;
    }
    //用非递归实现广度优先搜索
    Result BFSWithoutRecursion()
    {
        Result Res;
        queue<int>Q;
        Initialization();
        int Count = 0;
        for(int Now = 0; Now < MAXN; ++Now)
            if(!Visited[Now] && Appeared[Now])
            {
                Q.push(Now);
                Visited[Now] = 1;
                while(!Q.empty())
                {
                    int x = Q.front();
                    Q.pop();
                    Res.ID[x] = ++Count;
                    Res.Sequence.push_back(x);
                    for (int i = 0; i < MAXN; ++i)
                    {
                        if(!Matrix[x][i])
                            continue;
                        int To = i;
                        if(!Visited[To])
                        {
                            Res.TreeMatrix[x].push_back(To);
                            Visited[To] = 1;
                            Q.push(To);
                        }
                    }
                }
            }
        return Res;
    }
    void Print()
    {
        int Max = 0;
        for (int i = 0; i < MAXN; ++i)
            if(Appeared[i])
                Max = max(Max, i);
        for (int i = 0; i < Max; ++i, cout << '\n')
            for (int j = 0; j < Max; ++j)
                cout << Matrix[i][j] << " ";
    }
};
//邻接表的存储结构
class AdjacencyList
{
private:
    struct Node
    {
        int To;
        Node *Next;
        Node()
        {
            Next = NULL;
        }
    };
    Node *List[MAXN];//点集
    bool Visited[MAXN], Appeared[MAXN];//该节点是否访问过；该节点是否出现过
    int n, m;//节点的数量和边的数量

public:
    AdjacencyList()
    {
        for (int i = 0; i < MAXN; ++i)
            List[i] = new Node, Appeared[i] = 0;
    }
    //清空邻接表
    void Clear()
    {
        for (int i = 0; i < MAXN; ++i)
            List[i] = new Node, Appeared[i] = 0;
    }
    //遍历前初始化
    void Initialization()
    {
        for(int i = 0; i < MAXN; ++i)
            Visited[i] = 0;
    }
    //获取x的出度
    int GetListSize(int x)
    {
        int Res = 0;
        Node* now = List[x]->Next;
        while(now != NULL)
        {
            Res++;
            now = now->Next;
        }
        return Res;
    }
    //获取x到y是否有边
    int GetListEle(int x, int y)
    {
        int Cnt = -1;
        Node* now = List[x]->Next;
        while(now != NULL)
        {
            Cnt++;
            if(Cnt == y)
                return now->To;
            now = now->Next;
        }
        return -1;
    }
    //邻接表插入
    void Insert(int x, int y)
    {
        Node *now = List[x];
        Node *New = new Node;
        New->To = y;
        New->Next = now->Next;
        now->Next = New;
        Appeared[x] = 1;
        Appeared[y] = 1;
    }
    //建立邻接表
    void InputandBuild()
    {
        Clear();
        cin >> n >> m;
        for (int i = 1; i <= m; ++i)
        {
            int x, y;
            cin >> x >> y;
            Insert(x, y);
        }
    }
    //深度优先搜索的遍历过程
    void DFS(int x,int &Count, Result &Res)
    {
        Visited[x] = 1;
        Res.ID[x] = ++Count;
        Res.Sequence.push_back(x);
        int Size = GetListSize(x);
        for (int i = 0; i < Size; ++i)
        {
            int To = GetListEle(x, i);
            if(!Visited[To])
            {
                Res.TreeMatrix[x].push_back(To);
                DFS(To, Count, Res);
            }
        }
    }
    //用递归实现深度优先搜索
    Result DFSWithRecursion()
    {
        Result Res;
        int Count = 0;
        Initialization();
        for(int i = 0; i < MAXN; ++i)
            if(!Visited[i] && Appeared[i])
                DFS(i, Count, Res);
        return Res;
    }
    //用非递归实现深度优先搜索
    Result DFSWithoutRecursion()
    {
        Result Res;
        stack<int>S;
        Initialization();
        int Count = 0;
        for(int Now = 0; Now < MAXN; ++Now)
            if(!Visited[Now] && Appeared[Now])
            {
                S.push(Now);
                Visited[Now] = 1;
                while(!S.empty())
                {
                    int x = S.top();
                    S.pop();
                    Res.ID[x] = ++Count;
                    Res.Sequence.push_back(x);
                    int Size = GetListSize(x);
                    for (int i = 0; i < Size; ++i)
                    {
                        int To = GetListEle(x, i);
                        if(!Visited[To])
                        {
                            Res.TreeMatrix[x].push_back(To);
                            Visited[To] = 1;
                            S.push(To);
                        }
                    }
                }
            }
        return Res;
    }
    //用非递归实现广度优先搜索
    Result BFSWithoutRecursion()
    {
        Result Res;
        queue<int>Q;
        Initialization();
        int Count = 0;
        for(int Now = 0; Now < MAXN; ++Now)
            if(!Visited[Now] && Appeared[Now])
            {
                Q.push(Now);
                Visited[Now] = 1;
                while(!Q.empty())
                {
                    int x = Q.front();
                    Q.pop();
                    Res.ID[x] = ++Count;
                    Res.Sequence.push_back(x);
                    int Size = GetListSize(x);
                    for (int i = 0; i < Size; ++i)
                    {
                        int To = GetListEle(x, i);
                        if(!Visited[To])
                        {
                            Res.TreeMatrix[x].push_back(To);
                            Visited[To] = 1;
                            Q.push(To);
                        }
                    }
                }
            }
        return Res;
    }
    void Print()
    {
        for (int i = 0; i < MAXN; ++i)
        {
            int Size = GetListSize(i);
            if(Size)
                cout << i << " : ";
            else
                continue;
            for (int j = 0; j < Size; ++j)
                cout << GetListEle(i, j) << " ";
            cout << "\n";
        }
    }
};
//将邻接表转换为邻接矩阵
AdjacencyMatrix Transformer_List2Matrix(AdjacencyList &AL)
{
    AdjacencyMatrix Res;
    for(int i = 0; i < MAXN; ++i)
    {
        int Size = AL.GetListSize(i);
        for(int j = 0; j < Size; ++j)
        {
            Res.Insert(i, AL.GetListEle(i, j));
        }
    }
    return Res;
}
//将邻接矩阵转换为邻接表
AdjacencyList Transformer_Matrix2List(AdjacencyMatrix &AM)
{
    AdjacencyList Res;
    for(int i = 0; i < MAXN; ++i)
        for(int j = 0; j < MAXN; ++j)
            if(AM.GetMatrixEle(i, j))
                Res.Insert(i, j);
    return Res;
}
int main()
{
    freopen("Homework4_In.txt","r",stdin);
    //freopen("Homework4_Out.txt","w",stdout);
    AdjacencyMatrix AM;
    AdjacencyList AL;
    Result R;
    while(1)
    {
        int OP;
        printf("--------------------------------\n"
                "0.Quit\n"
                "1.Input Graph using Adjacency List\n"
                "2.Input Graph using Adjacency Matrix\n"
                "3.Transform List to Matrix\n"
                "4.Transform Matrix to List\n"
                "5.DFS List With Recursion\n"
                "6.DFS Matrix With Recursion\n"
                "7.DFS List Without Recursion\n"
                "8.DFS Matrix Without Recursion\n"
                "9.BFS List\n"
                "10.BFS Matrix\n"
                "--------------------------------\n"
                "Input an Integer to Choose:\n");
        cin >> OP;
        if(OP < 0 || OP > 10)
        {
            puts("Input Error!");
            continue;
        }
        if(OP == 0)
            break;
        else if(OP == 1)
        {
            AL.InputandBuild();
            AL.Print();
        }
        else if(OP == 2)
        {
            AM.InputandBuild();
            AM.Print();
        }
        else if(OP == 3)
        {
            AM = Transformer_List2Matrix(AL);
            AM.Print();
        }
        else if(OP == 4)
        {
            AL = Transformer_Matrix2List(AM);
            AL.Print();
        }
        else if(OP == 5)
        {
            puts("DFSWithRecursion");
            R = AL.DFSWithRecursion();
            R.Print();
        }
        else if(OP == 6)
        {
            puts("DFSWithRecursion");
            R = AM.DFSWithRecursion();
            R.Print();
        }
        else if(OP == 7)
        {
            puts("DFSWithoutRecursion");
            R = AL.DFSWithoutRecursion();
            R.Print();
        }
        else if(OP == 8)
        {
            puts("DFSWithoutRecursion");
            R = AM.DFSWithoutRecursion();
            R.Print();
        }
        else if(OP == 9)
        {
            puts("BFSWithoutRecursion");
            R = AL.BFSWithoutRecursion();
            R.Print();
        }
        else if(OP == 10)
        {
            puts("BFSWithoutRecursion");
            R = AM.BFSWithoutRecursion();
            R.Print();
        }
    }
    
    return 0;
}
/*
5 5
1 2
1 3
2 4
3 4
4 5
*/