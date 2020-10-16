## 作业2-2

**迷宫问题求解** 

一个迷宫可以看成是由 $n×m$ 个房间组成的矩形，迷宫内部的每个房间有 $8$ 个方向，每个方向或者有障碍（如墙）而不能通过，或者无障碍（如有门）而能 通过。入口为左上角房间，出口为右下角房间，问是否有简单路径从入口到出口， 若有则输出一条这样的路径；否则，提示“迷宫无入口到出口的路经”。 



### 存储结构

```cpp
const int MAXN = 1e2 + 10;
struct MAP
{
    int n, m;
    int map[MAXN][MAXN];
    int Visited[MAXN][MAXN];
};
```



### 函数说明

1. 设计一个迷宫及其障碍的表示方式，并能随机或手动生成迷宫。
`GenerateNewMapRandomly(int n, int m)` 随机生成一个 $n\times m$ 的迷宫, `0` 与 `1` 比例为 $4:1$ 。
`GenerateNewMapManually(int n, int m)` 手动生成一个 $n\times m$ 的迷宫。
2. 设计并实现一个非递归的算法，输出从入口到出口的一条路径（如存在）。
`bool FindWithoutRecursion(MAP &Map)` 非递归地在迷宫 `Map` 中找到一条路径，若有则返回 `1` ，否则返回 `0` 。
3. 设计并实现一个递归的算法，找出从入口到出口的一条路径（如存在）。
`bool FindWithRecursion(Map &Map)` 递归地在迷宫 `Map` 中找到一条路径，若有则返回 `1` ，否则返回 `0` 。
4. 如果有多条路径，设计并实现一个算法找到步数最少的路径（捷径）。
`bool FindTheShortest(MAP &Map)` 在迷宫 `Map` 中找到一条最短的路径，若有则返回 `1` ，否则返回 `0` 。
5. 如果有多条路径，设计并实现一个算法找到所有路径。
`void FindAll(MAP &Map)` 递归地在迷宫 `Map` 中找到所有简单路径。
6. 以文件方式保存、并显示原始数据和结果。
`freopen("Homework2_Out.txt", "w", stdout)`



### 自测

#### 测试说明

***由于本程序未加入`system("pause")`，建议在CMD/Terminal中测试。***

**下述程序均为文件输入输出。**

源程序 `Homework2.cpp` 中提供测试函数`void Test_GenerateNewMapRandomly(int n, int m)`，`void Test_GenerateNewMapManually(int n, int m)` ，`n` 和 `m` 需要根据输入的地图长宽而变化。

为方便测试，另提供两个源程序 `Homework2_GenerateNewMapRandomly.cpp` 和 `Homework2_GenerateNewMapManually.cpp` ，分别含有测试函数`void Test_GenerateNewMapRandomly(int n, int m)` 和 `void Test_GenerateNewMapManually(int n, int m)` ，前者是随机生成迷宫，后者是手动生成迷宫。

另提供由 `Homework2_GenerateNewMapRandomly.cpp` 产生的运行结果（由于随机性，每次运行产生的结果不同） `Homework2_GenerateNewMapRandomly_Out.txt`。

另提供 `Homework2_GenerateNewMapManually.cpp` 的输入数据 `Homework2_GenerateNewMapManually_In.txt` 和产生的运行结果`Homework2_GenerateNewMapManually_Out.txt` 。



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