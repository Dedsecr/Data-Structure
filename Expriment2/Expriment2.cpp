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
string OriginalText;
string EncodedText;
struct Text
{
    int Length;
    double Frequency[126];
    Text()
    {
        Length = 0;
        for (int i = 0; i < 126; ++i)
            Frequency[i] = 0;
    }
};
struct HCode
{
    string Code;
    char Text;
};
struct HuffmanCode
{
    vector<HCode> Code;
};

map<char, string>HFCMap;
map<string, char>HFCMap_Reverse;

int Stack[MAXN], StackP;
int ChildNum = 2;
struct TreeNode
{
    char Text;
    double Val;
    vector<TreeNode *> Ch;
    TreeNode()
    {
        Text = 0;
        Val = 0;
        Ch.clear();
    }
};

typedef TreeNode *Tree;
typedef TreeNode *Node;
//小根堆
class Priority_Queue
{
private:
    Tree Heap[MAXN << 2];
    int Last;

public:
    Priority_Queue()
    {
        Last = 0;
    }
    bool empty()
    {
        return !Last;
    }
    int size()
    {
        return Last;
    }
    void push(Tree x)
    {
        Heap[++Last] = x;
        int Pos = Last;
        while(Pos > 1)
        {
            if(Heap[Pos >> 1]->Val > Heap[Pos]->Val)
                swap(Heap[Pos >> 1], Heap[Pos]);
            Pos >>= 1;
        }
    }
    Tree top()
    {
        return Heap[1];
    }
    void pop()
    {
        if(!Last)
        {
            cerr << "Error in" << __LINE__;
            exit(-1);
        }
        swap(Heap[1], Heap[Last]);
        Last--;
        if(Last == 0)
            return;
        int Pos = 1;
        while(Last >= (Pos << 1))
        {
            if((Pos << 1 | 1) <= Last)
            {
                if(Heap[Pos]->Val > min(Heap[Pos << 1]->Val, Heap[Pos << 1 | 1]->Val))
                {
                    if(Heap[Pos << 1]->Val < Heap[Pos << 1 | 1]->Val)
                        swap(Heap[Pos << 1], Heap[Pos]), Pos <<= 1;
                    else swap(Heap[Pos << 1 | 1], Heap[Pos]), Pos = Pos << 1 | 1;
                }
                else
                    break;
            }
            else
            {
                if(Heap[Pos]->Val > Heap[Pos << 1]->Val)
                    swap(Heap[Pos << 1], Heap[Pos]), Pos <<= 1;
                else
                    break;
            }
        }
    }
};
Priority_Queue Q;
//建立哈夫曼树
Tree BuildHuffmanTree(Text &text)
{
    while (!Q.empty())
        Q.pop();
    for (int i = 0; i < 126; ++i)
        if (abs(text.Frequency[i]) > 1e-8)
        {
            Tree T = new TreeNode;
            T->Val = text.Frequency[i];
            T->Text = i;
            Q.push(T);
        }
    while (Q.size() != 1)
    {
        int End = Q.size();
        if (End > ChildNum)
            End = ChildNum;
        Tree T = new TreeNode;
        for (int i = 1; i <= End; ++i)
        {
            Tree now = Q.top();
            Q.pop();
            T->Val += now->Val;
            T->Ch.push_back(now);
        }
        Q.push(T);
    }
    return Q.top();
}
//输入并计算频率
Text GetFrequency()
{
    Text Res;
    char now;
    OriginalText = "";
    while ((now = getchar()) != EOF)
    {
        OriginalText += now;
    }
    int Length = OriginalText.length();
    Res.Length = Length;
    for (int i = 0; i < Length; ++i)
    {
        Res.Frequency[OriginalText[i]] += 1;
    }
    for (int i = 0; i < 126; ++i)
    {
        Res.Frequency[i] /= Length;
    }
    return Res;
}
char HCInt2Char(int x)
{
    if(x < 10)
        return x + '0';
    return x - 10 + 'A';
}
string CharForOutput(char x)
{
    string Res = "";
    if(x == '\n')
        Res = "\'\\n\'";
    else 
    {
        Res = "\'";
        Res += x;
        Res += "\'";
    }
    return Res;
}
//遍历哈夫曼树以计算哈夫曼编码
void GetHC(Tree Root, HuffmanCode *Code)
{
    int Size = Root->Ch.size();
    if (!Size)
    {
        if (!Root->Text)
        {
            cerr << "Error in " << __LINE__;
            exit(-1);
        }
        HCode HC;
        HC.Text = Root->Text;
        HC.Code = "";
        for (int i = 1; i <= StackP; ++i)
            HC.Code += HCInt2Char(Stack[i]);
        Code->Code.push_back(HC);
        return;
    }
    for (int i = 0; i < Size; ++i)
    {
        Stack[++StackP] = i;
        GetHC(Root->Ch[i], Code);
        StackP--;
    }
}
//打印哈夫曼编码
void PrintHC(HuffmanCode *Code)
{
    int Size = Code->Code.size();
    for (int i = 0; i < Size; ++i)
    {
        cout << CharForOutput(Code->Code[i].Text) << " : " << Code->Code[i].Code << endl;
    }
}
//输出频率
void PrintFrequency(Text &text)
{
    for (int i = 0; i < 126; ++i)
    {
        if (abs(text.Frequency[i]) > 1e-8)
        {
            cout << CharForOutput(char(i)) << " : " << text.Frequency[i] << endl;
        }
    }
    puts("");
}

void GetMap(HuffmanCode *Code)
{
    int Size = Code->Code.size();
    for (int i = 0; i < Size; ++i)
    {
        HFCMap[Code->Code[i].Text] = Code->Code[i].Code;
        HFCMap_Reverse[Code->Code[i].Code] = Code->Code[i].Text;
    }
}
//计算哈夫曼编码并输出
void GetHuffmanCode(Tree Root)
{
    HuffmanCode *Code = new HuffmanCode;
    StackP = 0;
    GetHC(Root, Code);
    GetMap(Code);
    PrintHC(Code);
}
//编码
int Encode()
{
    EncodedText = "";
    int Res = 0;
    int Length = OriginalText.length();
    for(int i = 0; i < Length; ++i)
    {
        Res += HFCMap[OriginalText[i]].length();
        EncodedText += HFCMap[OriginalText[i]];
    }
    cout << EncodedText << '\n';
    return Res;
}
//解码
void Decode()
{
    string now = "";
    int Length = EncodedText.length();
    for(int i = 0; i < Length; ++i)
    {
        now += EncodedText[i];
        if(HFCMap_Reverse[now])
        {
            cout << HFCMap_Reverse[now];
            now = "";
        }
    }
    puts("");
}
//求压缩率
void GetCompressionRatio(int Length_After)
{
    int Width_Before = 8, Width_After = ceil(log2(1.0 * ChildNum));
    double Ratio = 1.0 * Width_After * Length_After / Width_Before * 100 / OriginalText.length();
    printf("Compression Ratio:\n%.3lf%%\n", Ratio);
}

int main()
{
    freopen("Expriment2_In.txt", "r", stdin);
    freopen("Expriment2_Out.txt", "w", stdout);

    ChildNum = 2;
    
    Text text = GetFrequency();
    PrintFrequency(text);
    puts("");
    
    Tree T = BuildHuffmanTree(text);
    GetHuffmanCode(T);
    puts("");

    int Length_After = Encode();
    puts("");

    Decode();
    puts("");

    GetCompressionRatio(Length_After);
    return 0;
}