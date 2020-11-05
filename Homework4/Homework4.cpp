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
};

class AdjacencyMatrix
{
private:
    int Matrix[MAXN][MAXN];
    int n, m;//节点的数量和边的数量 

public:
    AdjacencyMatrix(){}
    AdjacencyMatrix(int _n, int _m)
    {
        n = _n;
        m = _m;
        memset(Matrix, 0, sizeof(Matrix));
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
};
class AdjacencyList
{
private:
    vector<int>List[MAXN];
    bool Visited[MAXN];
    int n, m;//节点的数量和边的数量 

public:
    AdjacencyList(){}
    AdjacencyList(int _n, int _m)
    {
        n = _n;
        m = _m;
        for (int i = 0; i < MAXN; ++i)
            List[i].clear();
    }
    int GetListSize(int x)
    {
        return List[x].size();
    }
    int GetListEle(int x, int y)
    {
        return List[x][y];
    }
    void Insert(int x, int y)
    {
        List[x].push_back(y);
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
        for(int i = 0; i < MAXN; ++i)
            Visited[i] = 0;
        for(int i = 0; i < MAXN; ++i)
            if(!Visited[i])
                DFS(i, Count, Res);
        
    }
    Result DFSWithoutRecursion()
    {
        Result Res;
        stack<int>S;
        for(int i = 0; i < MAXN; ++i)
            Visited[i] = 0;
        for(int i = 0; i < MAXN; ++i)
            if(!Visited[i])
            {
                S.push(i);
                while(!S.empty())
                {
                    
                }
            }
        
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
