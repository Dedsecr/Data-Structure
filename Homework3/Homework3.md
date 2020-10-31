## 作业3

**二叉树存储结构的建立、遍历和应用**

树型结构的遍历是树型结构算法的基础，本实验要求编写程序演示二叉树的存储结构的建立方法、遍历过程以及应用。



### 存储结构

```cpp
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
```



### 函数说明

1. 编写建立二叉树的二叉链表存储结构（左右链表示）的程序，并以适当的形式显示和保存二叉树；

  `Tree InputTree()` 按照**先序序列**建立二叉树。 

  `void PrintTree(Tree &Root)` 打印根为 `Root` 的树，共 $n$ 行，**每行输出该节点、该节点左儿子、该节点右儿子，若无儿子则输出 `#`** 。

2. 采用二叉树的二叉链表存储结构，编写程序实现二叉树的先序、中序和后序遍历的递归和非递归算法以及层序遍历算法，并以适当的形式显示和保存二叉树及其相应的遍历序列；

  `void Get_PreOrder_WithRecursion(Tree &Root)` 用递归实现输出先序遍历序列。

  `void Get_InOrder_WithRecursion(Tree &Root)` 用递归实现输出中序遍历序列。

  `void Get_PostOrder_WithRecursion(Tree &Root)` 用递归实现输出后序遍历序列。

  `void Get_PreOrder_WithoutRecursion(Tree &Root)` 用非递归实现输出先序遍历序列。

  `void Get_InOrder_WithoutRecursion(Tree &Root)` 用非递归实现输出中序遍历序列。

  `void Get_PostOrder_WithoutRecursion(Tree &Root)` 用非递归实现输出后序遍历序列。

  `void Get_LeverOrder(Tree &Root)` 输出层序遍历序列。

3. 设计并实现判断任意一棵二叉树是否为完全二叉树的算法。

  `bool Is_CompleteTree(Tree &Root)` 判断根为 `Root` 的树是否为完全二叉树。

4. 设计并实现计算任意一棵二叉树的宽度的（递归或非递归）算法。二叉树的宽度是指其各层结点数的最大值。

  `int Get_MaxWidth(Tree &Root)` 输出根为 `Root` 的树的宽度。



### 自测

#### 测试说明

***由于本程序未加入`system("pause")`，建议在CMD/Terminal中测试。***

**下述程序均为文件输入输出。**





#### 输入格式说明（均为文件输入）

首先输入 `n,m` ，以表示迷宫有 `n` 行 `m` 列。

若是随机生成迷宫的程序，则不需要另外输入；若是手动生成迷宫的程序，则还需要输入迷宫描述， `0` 表示可走， `1` 表示不可走。




#### 输出格式说明（均为文件输出）

1. 若迷宫是随机生成的，则首先输出迷宫；若是手动输入，则不输出。
2. 输出非递归地找到的一条路径，以 `*****FindWithoutRecursion*****` 开始，以 `******************************` 结尾，并输出 `Successfully Found a Road Without Recursion!` 和 `******************************` 。
3. 输出递归地找到的一条路径，以 `*******FindWithRecursion******` 开始，以 `******************************` 结尾，并输出 `Successfully Found a Road With Recursion!` 和 `******************************` 。
4. 输出找到的步数最少的路径，以 `*******FindTheShortest********` 开始，以 `******************************` 结尾，并输出`You need to walk * steps at least.` ， `Successfully Found a Road With Recursion!` 和 `******************************` 。
5. 输出找到的所有路径，以 `************FindAll***********` 开始，每两个路径之间以 `******************************` 隔开，并以 `******************************` 结尾，最后输出`* Roads in All!` 和 `******************************` 。
6. 上述2~4条中，若无法找到路径，则将会用 `No Road Found!` 代替 `Successfully Found *` 。

形式化地，有

```CPP
[地图描述]/无
*****FindWithoutRecursion*****
[路径]
******************************
Successfully Found a Road Without Recursion!/No Road Found!
******************************
*******FindWithRecursion******
[路径]
******************************
Successfully Found a Road With Recursion!/No Road Found!
******************************
*******FindTheShortest********
[路径]
You need to walk x steps at least.
******************************
Successfully Found The Shortest!/No Road Found!
******************************
************FindAll***********
[路径1]
******************************
[路径2]
******************************
[路径3]
******************************
...
******************************
[路径n]
******************************
n Roads in All!
******************************
```



#### 数据说明

##### Homework2_GenerateNewMapManually

```cpp
/*Homework2_GenerateNewMapManually_In.txt*/
5 5              5行5列的迷宫
0 0 1 1 1		 迷宫描述
1 1 0 1 1
1 0 1 0 1
0 1 1 1 0
1 0 0 0 0
```

```cpp
/*Homework2_GenerateNewMapManually_Out.txt*/
*****FindWithoutRecursion*****					非递归地在迷宫中找到了一条路径
(1,1)
(1,2)
(2,3)
(3,2)
(4,1)
(5,2)
(5,3)
(5,4)
(5,5)
******************************
Successfully Found a Road Without Recursion!
******************************
*******FindWithRecursion******					递归地在迷宫中找到了一条路径
(1,1)
(1,2)
(2,3)
(3,2)
(4,1)
(5,2)
(5,3)
(5,4)
(5,5)
******************************
Successfully Found a Road With Recursion!
******************************
*******FindTheShortest********					找到了迷宫中的最短路径
(1,1)
(1,2)
(2,3)
(3,2)
(4,1)
(5,2)
(5,3)
(5,4)
(5,5)
You need to walk 9 steps at least.
******************************
Successfully Found The Shortest!
******************************
************FindAll***********					找到了迷宫中的所有4条路径
(1,1)
(1,2)
(2,3)
(3,2)
(4,1)
(5,2)
(5,3)
(5,4)
(5,5)
******************************
(1,1)
(1,2)
(2,3)
(3,2)
(4,1)
(5,2)
(5,3)
(5,4)
(4,5)
(5,5)
******************************
(1,1)
(1,2)
(2,3)
(3,4)
(4,5)
(5,5)
******************************
(1,1)
(1,2)
(2,3)
(3,4)
(4,5)
(5,4)
(5,5)
******************************
4 Roads in All!
******************************

```



##### Homework2_GenerateNewMapRandomly（具有随机性，每次运行结果不同）

```CPP
/*Homework2_GenerateNewMapRandomly_In.txt*/
4 4           随机生成一个4行4列的迷宫
```

```CPP
/*Homework2_GenerateNewMapRandomly_Out.txt*/
0 1 1 0 											随机生成的迷宫描述
1 0 0 0 
1 1 0 1 
1 1 1 0 
*****FindWithoutRecursion*****						非递归地在迷宫中找到了一条路径
(1,1)
(2,2)
(2,3)
(2,4)
(3,3)
(4,4)
******************************
Successfully Found a Road Without Recursion!
******************************
*******FindWithRecursion******						递归地在迷宫中找到了一条路径
(1,1)
(2,2)
(2,3)
(2,4)
(3,3)
(4,4)
******************************
Successfully Found a Road With Recursion!
******************************
*******FindTheShortest********						找到了迷宫中的最短路径
(1,1)
(2,2)
(2,3)
(2,4)
(3,3)
(4,4)
You need to walk 6 steps at least.
******************************
Successfully Found The Shortest!
******************************
************FindAll***********						找到了迷宫中的所有4条路径
(1,1)
(2,2)
(2,3)
(2,4)
(3,3)
(4,4)
******************************
(1,1)
(2,2)
(2,3)
(3,3)
(4,4)
******************************
(1,1)
(2,2)
(2,3)
(1,4)
(2,4)
(3,3)
(4,4)
******************************
(1,1)
(2,2)
(3,3)
(4,4)
******************************
4 Roads in All!
******************************

```