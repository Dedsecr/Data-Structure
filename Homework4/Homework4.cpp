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
    void Print() 
    {
        puts("Sequence:");
        int Size = Sequence.size();
        for (int i = 0; i < Size; ++i)
            cout << Sequence[i] << " ";
        puts("");

        puts("ID:");
        puts("Node  ID");
        for (int i = 0; i < MAXN; ++i)
            if(ID[i])
                cout << i << " : " << ID[i] << "\n";
        puts("");
    }
};

class AdjacencyMatrix
{
private:
    int Matrix[MAXN][MAXN];
    bool Visited[MAXN], Appeared[MAXN];
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
    void Initialization()
    {
        for(int i = 0; i < MAXN; ++i)
            Visited[i] = 0;
    }
    int GetMatrixEle(int x, int y)
    {
        return Matrix[x][y];
    }
    void Insert(int x, int y)
    {
        Matrix[x][y] = 1;
    }
    void InputandBuild()
    {
        cin >> n >> m;
        for (int i = 1; i <= m; ++i)
        {
            int x, y;
            cin >> x >> y;
            Insert(x, y);
            Insert(y, x);
        }
    }
    void DFS(int x,int &Count, Result &Res)
    {
        Visited[x] = 1;
        Res.ID[x] = ++Count;
        Res.Sequence.push_back(x);
        for (int i = 0; i < MAXN; ++i)
        {
            if(!Matrix[x][i])
                continue;
            int To = GetMatrixEle(x, i);
            if(!Visited[To])
            {
                Res.TreeMatrix[x].push_back(To);
                DFS(To, Count, Res);
            }
        }
    }
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
    Result DFSWithoutRecursion()
    {
        Result Res;
        stack<int>S;
        Initialization();
        int Count = 0;
        for(int Now = 0; Now < MAXN; ++Now)
            if(!Visited[Now])
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
                        int To = GetMatrixEle(x, i);
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
    Result BFSWithoutRecursion()
    {
        Result Res;
        queue<int>Q;
        Initialization();
        int Count = 0;
        for(int Now = 0; Now < MAXN; ++Now)
            if(!Visited[Now])
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
                        int To = GetMatrixEle(x, i);
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
};
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
    Node *List[MAXN];
    bool Visited[MAXN], Appeared[MAXN];
    int n, m;//节点的数量和边的数量

public:
    AdjacencyList()
    {
        for (int i = 0; i < MAXN; ++i)
            List[i] = NULL, Appeared[i] = 0;
    }
    /*AdjacencyList(int _n, int _m)
    {
        n = _n;
        m = _m;
        for (int i = 0; i < MAXN; ++i)
            List[i] = NULL;
    }*/
    void Initialization()
    {
        for(int i = 0; i < MAXN; ++i)
            Visited[i] = 0;
    }
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
    int GetListEle(int x, int y)
    {
        int Cnt = 0;
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
    void Insert(int x, int y)
    {
        Appeared[x] = 1;
        Appeared[y] = 1;
        Node* now = List[x];
        while(now->Next != NULL)
            now = now->Next;
        now->Next = new Node;
        now->Next->Next = NULL;
        now->Next->To = y;
    }
    void InputandBuild()
    {
        cin >> n >> m;
        for (int i = 1; i <= m; ++i)
        {
            int x, y;
            cin >> x >> y;
            Insert(x, y);
            Insert(y, x);
        }
    }
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
    Result DFSWithoutRecursion()
    {
        Result Res;
        stack<int>S;
        Initialization();
        int Count = 0;
        for(int Now = 0; Now < MAXN; ++Now)
            if(!Visited[Now])
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
    Result BFSWithoutRecursion()
    {
        Result Res;
        queue<int>Q;
        Initialization();
        int Count = 0;
        for(int Now = 0; Now < MAXN; ++Now)
            if(!Visited[Now])
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
};

AdjacencyMatrix Transformer_List2Matrix(AdjacencyList AL)
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
AdjacencyList Transformer_Matrix2List(AdjacencyMatrix AM)
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
    AdjacencyMatrix AM;
    AM.InputandBuild();
    Result R = AM.DFSWithRecursion();
    R.Print();
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