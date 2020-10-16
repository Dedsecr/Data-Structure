#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;
const int MAXN = 1e2;
const int Move[8][2] = {0, 1, 1, 0, -1, 0, 0, -1, -1, 1, 1, -1, 1, 1, -1, -1};
const int INF = 1e9;
struct MAP
{
    int n, m;
    int map[MAXN][MAXN];
    int Visited[MAXN][MAXN];
};
struct Node
{
    int x, y;
    Node(){}
    Node(int _x, int _y)
    {
        x = _x, y = _y;
    }
    bool operator == (const Node _)const
    {
        return x == _.x && y == _.y;
    }
};
Node Stack[MAXN * MAXN], AnsStack[MAXN * MAXN];
int StackP, AnsStackP;
MAP GenerateNewMapRandomly(int n,int m)
{
    MAP Map;
    Map.n = n, Map.m = m;
    srand(time(0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            Map.map[i][j] = (rand() % 5) > 3 ? 0 : 1, Map.Visited[i][j] = 0;
    Map.map[1][1] = Map.map[n][m] = 0;
    return Map;
}
MAP GenerateNewMapManually(int n,int m)
{
    MAP Map;
    Map.n = n, Map.m = m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &Map.map[i][j]), Map.Visited[i][j] = 0;
    if(Map.map[1][1] || Map.map[n][m])
        puts("Waring! NO Entrance or Exit!");
    return Map;
}
void IniBeforeFind(MAP &Map)
{
    StackP = 0;
    AnsStackP = 0;
    for (int i = 1; i <= Map.n; ++i)
        for (int j = 1; j <= Map.m; ++j)
            Map.Visited[i][j] = 0;
}
void StackInsert(Node x)
{
    Stack[++StackP] = x;
}
void StackPop()
{
    StackP--;
}
bool LeagalPos(Node x, MAP &Map)
{
    if (x.x <= Map.n && x.y <= Map.m && x.x >= 1 && x.y >= 1)
        return 1;
    else
        return 0;
}
Node StackTop()
{
    return Stack[StackP];
}
void PrintAnsStack()
{
    if(AnsStackP)
    {
        puts("*******FindTheShortest********");
        for (int i = 1; i <= AnsStackP; ++i)
        {
            printf("(%d,%d)\n", AnsStack[i].x, AnsStack[i].y);
        }
        printf("You need to walk %d steps at least.\n", AnsStackP);
        puts("******************************");
    }
}
void PrintStack()
{
    for (int i = 1; i <= StackP; ++i)
    {
        printf("(%d,%d)\n", Stack[i].x, Stack[i].y);
    }
    puts("******************************");
}
bool FindWithoutRecursion(MAP &Map)
{
    IniBeforeFind(Map);
    StackInsert(Node(1, 1));
    Map.Visited[1][1] = 1;
    while(StackP)
    {
        Node x = StackTop();
        if(x==Node(Map.n,Map.m))
        {
            puts("*****FindWithoutRecursion*****");
            PrintStack();
            return true;
        }
        StackPop();
        for (int k = 0; k < 8; ++k)
        {
            Node To = Node(x.x + Move[k][0], x.y + Move[k][1]);
            if(!LeagalPos(To, Map) || Map.map[To.x][To.y] || Map.Visited[To.x][To.y])
                continue;
            Map.Visited[To.x][To.y] = 1;
            StackInsert(x), StackInsert(To);
            break;
        }
    }
    return false;
}
void DFS_One(MAP &Map, Node x, bool &Found)
{
    
    if(x.x == Map.n && x.y == Map.m)
    {
        Found = 1;
        puts("*******FindWithRecursion******");
        PrintStack();
        return;
    }
    for (int k = 0; k < 8; ++k)
    {
        Node To = Node(x.x + Move[k][0], x.y + Move[k][1]);
        if(!LeagalPos(To, Map) || Map.map[To.x][To.y] || Map.Visited[To.x][To.y])
                continue;
        Map.Visited[To.x][To.y] = 1;
        StackInsert(To);
        DFS_One(Map, To, Found);
        StackPop();
        if(Found)
            return;
    }
}
bool FindWithRecursion(MAP &Map)
{
    bool Found = 0;
    IniBeforeFind(Map);
    Map.Visited[1][1] = 1;
    StackInsert(Node(1, 1));
    DFS_One(Map, Node(1, 1), Found);
    StackPop();
    return Found;
}
void UpdateAns()
{
    for (int i = 1; i <= StackP; ++i)
    {
        AnsStack[i] = Stack[i];
    }
    AnsStackP = StackP;
}
void DFS_Shortest(MAP &Map, Node x, int &Ans)
{
    if(x.x == Map.n && x.y == Map.m)
    {
        if(StackP <= Ans)
        {
            Ans = StackP;
            UpdateAns();
        }
        return;
    }
    for (int k = 0; k < 8; ++k)
    {
        Node To = Node(x.x + Move[k][0], x.y + Move[k][1]);
        if(!LeagalPos(To, Map) || Map.map[To.x][To.y] || Map.Visited[To.x][To.y])
            continue;
        Map.Visited[To.x][To.y] = 1;
        StackInsert(To);
        DFS_Shortest(Map, To, Ans);
        StackPop();
    }
}
bool FindTheShortest(MAP &Map)
{
    IniBeforeFind(Map);
    int Ans = INF;
    Map.Visited[1][1] = 1;
    StackInsert(Node(1, 1));
    DFS_Shortest(Map, Node(1, 1), Ans);
    StackPop();
    PrintAnsStack();
    return AnsStackP;
}
void DFS_All(MAP &Map, Node x, int &Times)
{
    if(x.x == Map.n && x.y == Map.m)
    {
        if(Times == 0)
            puts("************FindAll***********");
        PrintStack();
        Times++;
        return;
    }
    for (int k = 0; k < 8; ++k)
    {
        Node To = Node(x.x + Move[k][0], x.y + Move[k][1]);
        if(!LeagalPos(To, Map) || Map.map[To.x][To.y] || Map.Visited[To.x][To.y])
            continue;
        Map.Visited[To.x][To.y] = 1;
        StackInsert(To);
        DFS_All(Map, To, Times);
        Map.Visited[To.x][To.y] = 0;
        StackPop();
    }
}
void FindAll(MAP &Map)
{
    int Times = 0;
    IniBeforeFind(Map);
    StackInsert(Node(1, 1));
    Map.Visited[1][1] = 1;
    DFS_All(Map, Node(1, 1), Times);
    StackPop();
    cout << Times << " Roads in All!\n";
}
void PrintMap(MAP &Map)
{
    for(int i = 1; i <= Map.n; ++i)
    {
        for(int j = 1;j <= Map.m; ++j)
            cout<<Map.map[i][j]<<" ";
        cout<<endl;
    }    
}
void Test_GenerateNewMapManually(int n, int m)
{
    MAP Map = GenerateNewMapManually(n, m);
    if(FindWithoutRecursion(Map))
    {
        puts("Successfully Found a Road Without Recursion!");
        puts("******************************");
    }
    else
    {
        puts("No Road Found!");
        puts("******************************");
    }
    if(FindWithRecursion(Map))
    {
        puts("Successfully Found a Road With Recursion!");
        puts("******************************");
    }
    else
    {
        puts("No Road Found!");
        puts("******************************");
    }
    if(FindTheShortest(Map))
    {
        puts("Successfully Found The Shortest!");
        puts("******************************");
    }
    else
    {
        puts("No Road Found!");
        puts("******************************");
    }
    FindAll(Map);
    puts("******************************");
}

void Test_GenerateNewMapRandomly(int n, int m)
{
    MAP Map = GenerateNewMapRandomly(n, m);
    PrintMap(Map);
    if(FindWithoutRecursion(Map))
    {
        puts("Successfully Found a Road Without Recursion!");
        puts("******************************");
    }
    else
    {
        puts("No Road Found!");
        puts("******************************");
    }
    if(FindWithRecursion(Map))
    {
        puts("Successfully Found a Road With Recursion!");
        puts("******************************");
    }
    else
    {
        puts("No Road Found!");
        puts("******************************");
    }
    if(FindTheShortest(Map))
    {
        puts("Successfully Found The Shortest!");
        puts("******************************");
    }
    else
    {
        puts("No Road Found!");
        puts("******************************");
    }
    FindAll(Map);
    puts("******************************");
}
/*
int main()
{
    int n, m;
    freopen("Homework2_In.txt", "r", stdin);
    freopen("Homework2_Out.txt", "w", stdout);
    cin >> n >> m;
    Test_GenerateNewMapManually(n, m);
    Test_GenerateNewMapRandomly(n, m);
    return 0;
}
*/