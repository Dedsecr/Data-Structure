## 作业5.1

**AVL 树的设计与实现**

本次作业要求设计 AVL 树存储结构，并实现 AVL 树建立（插入）、删除和查找算法，并反映插入和删除操作算法的各种旋转变化。



### 存储结构

```cpp
class AVL
{
private:
    //AVL树节点的存储结构
    struct Node
    {
        int Data, Size, Height;
        Node *LCh, *RCh;
        Node()
        {
            LCh = RCh = NULL;
            Size = Height = 0;
        }
    };
public:
    typedef Node * NodeP;
    NodeP Root;
};
```



### 函数说明

1. 设计 AVL 的左右链存储结构；

```cpp
struct Node
    {
        int Data, Size, Height;
        Node *LCh, *RCh;
        Node()
        {
            LCh = RCh = NULL;
            Size = Height = 0;
        }
    };
```

2. 实现 AVL 左右链存储结构上的插入（建立）、删除、查找和排序算法。

插入：`void Insert(NodeP &x, int Data)` 插入值为 `Data` 的节点；

删除：`int Delete(NodeP &x, int Data)` 删除值为 `Data` 的节点；

查找：`int Rank(NodeP x, int Data)` 查找 `Data` 在树中的次序；

排序：`string GetSorted()` 输出排好序的序列。

3. 测试数据以文件形式保存，能反映插入和删除操作的四种旋转，并输出相应结果。

`freopen("Homework5_In.txt", "r", stdin)` `freopen("Homework5_Out.txt", "w", srdout)`

当AVL树旋转时，会输出相应的旋转类型。



### 自测

#### 测试说明

***由于本程序未加入`system("pause")`，建议在CMD/Terminal中测试。***

**本程序采用文件输入输出。**

为方便测试，源程序 `Homework5.cpp` 中**将测试内容写入主函数** 。

另提供样例测试数据输入 `Homework5_In.txt` ，和期望输出 `Homework5_Out.txt` 。



#### 操作说明

> 0.Quit
> 1.Input Graph using Adjacency List
> 2.Input Graph using Adjacency Matrix
> 3.Transform List to Matrix
> 4.Transform Matrix to List
> 5.DFS List With Recursion
> 6.DFS Matrix With Recursion
> 7.DFS List Without Recursion
> 8.DFS Matrix Without Recursion
> 9.BFS List
> 10.BFS Matrix



#### 数据说明

**Homework4_In.txt**

<img src="https://gitee.com/Dedsecr/pic/raw/master/pic/DataStructure-Homwork4.png" alt="DataStructure-Homwork4" style="zoom:50%;" />

```CPP
1                输入图到邻接表中
12 17			 12个点17个边的图
0 4				 图的边的描述
4 9
9 6
6 3
3 0
2 5
5 1
1 2
10 7
7 11
11 10
2 3
8 4
8 11
6 7
3 7
0 1
3				邻接表转邻接矩阵
4				邻接矩阵转邻接表
5				在邻接表上递归地DFS
6				在邻接矩阵上递归地DFS
7				在邻接表上非递归地DFS
8				在邻接矩阵上非递归地DFS
9				在邻接矩阵上BFS
10				在邻接表上BFS
0				退出
```

**Homework4_Out.txt**

```CPP
--------------------------------
0.Quit
1.Input Graph using Adjacency List
2.Input Graph using Adjacency Matrix
3.Transform List to Matrix
4.Transform Matrix to List
5.DFS List With Recursion
6.DFS Matrix With Recursion
7.DFS List Without Recursion
8.DFS Matrix Without Recursion
9.BFS List
10.BFS Matrix
--------------------------------
Input an Integer to Choose:				输入图到邻接表中，邻接表的描述
0 : 1 4 
1 : 2 
2 : 3 5 
3 : 7 0 
4 : 9 
5 : 1 
6 : 7 3 
7 : 11 
8 : 11 4 
9 : 6 
10 : 7 
11 : 10 
**提示（略去）**
Input an Integer to Choose:				邻接表转邻接矩阵，邻接矩阵的描述
0 1 0 0 1 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 
0 0 0 1 0 1 0 0 0 0 0 
1 0 0 0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 0 0 1 0 
0 1 0 0 0 0 0 0 0 0 0 
0 0 0 1 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 0 0 0 
0 0 0 0 0 0 1 0 0 0 0 
0 0 0 0 0 0 0 1 0 0 0 
**提示（略去）**
Input an Integer to Choose:				邻接矩阵转回邻接表，邻接表的描述
0 : 4 1 
1 : 2 
2 : 5 3 
3 : 7 0 
4 : 9 
5 : 1 
6 : 7 3 
7 : 11 
8 : 11 4 
9 : 6 
10 : 7 
11 : 10 
**提示（略去）**
Input an Integer to Choose:				在邻接表上递归地DFS
DFSWithRecursion
Sequence:
0 4 9 6 7 11 10 3 1 2 5 8 				DFS序
Node  ID								编号
  0 : 1
  1 : 9
  2 : 10
  3 : 8
  4 : 2
  5 : 11
  6 : 4
  7 : 5
  8 : 12
  9 : 3
  10 : 7
  11 : 6

**提示（略去）**
Input an Integer to Choose:				在邻接矩阵上递归地DFS
DFSWithRecursion
Sequence:
0 1 2 3 7 11 10 5 4 9 6 8 				DFS序
Node  ID								编号
  0 : 1
  1 : 2
  2 : 3
  3 : 4
  4 : 9
  5 : 8
  6 : 11
  7 : 5
  8 : 12
  9 : 10
  10 : 7
  11 : 6

**提示（略去）**
Input an Integer to Choose:				在邻接表上非递归地DFS
DFSWithoutRecursion
Sequence:
0 1 2 3 7 11 10 5 4 9 6 8 				DFS序
Node  ID								编号
  0 : 1
  1 : 2
  2 : 3
  3 : 4
  4 : 9
  5 : 8
  6 : 11
  7 : 5
  8 : 12
  9 : 10
  10 : 7
  11 : 6

**提示（略去）**
Input an Integer to Choose:				在邻接矩阵上非递归地DFS
DFSWithoutRecursion
Sequence:
0 4 9 6 7 11 10 3 1 2 5 8 				DFS序
Node  ID								编号
  0 : 1
  1 : 9
  2 : 10
  3 : 8
  4 : 2
  5 : 11
  6 : 4
  7 : 5
  8 : 12
  9 : 3
  10 : 7
  11 : 6

**提示（略去）**
Input an Integer to Choose:				在邻接矩阵上BFS
BFSWithoutRecursion	
Sequence:
0 4 1 9 2 6 5 3 7 11 10 8 				BFS序
Node  ID								编号
  0 : 1
  1 : 3
  2 : 5
  3 : 8
  4 : 2
  5 : 7
  6 : 6
  7 : 9
  8 : 12
  9 : 4
  10 : 11
  11 : 10

**提示（略去）**
Input an Integer to Choose:				在邻接表上BFS
BFSWithoutRecursion
Sequence:
0 1 4 2 9 3 5 6 7 11 10 8 				BFS序
Node  ID								编号
  0 : 1
  1 : 2
  2 : 4
  3 : 6
  4 : 3
  5 : 7
  6 : 8
  7 : 9
  8 : 12
  9 : 5
  10 : 11
  11 : 10

**提示（略去）**
Input an Integer to Choose:				退出

```
