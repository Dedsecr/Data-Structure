#include<iostream>
using namespace std;
#define Datatype int
#define Position int
const int MAXN = 1e5;
namespace SeqLis
{
    struct List
    {
        Datatype data[MAXN];
        int Length;
        List()
        {
            Length = 0;
        }
    };
    List Tmp;
    void Del(int P, List &L)//对于线性表 L ，删除位置为 P 的元素。
    {
        if(P <= 0 || P > L.Length)
        {
            puts("Wrong Position!");
            return;
        }
        for (int i = P; i <= L.Length; ++i)
            L.data[i] = L.data[i + 1];
        L.Length--;
    }
    void Insert(Datatype x, int P, List &L)//对于线性表 L ，在位置 P 后插入元素 x 。
    {
        if(L.Length == MAXN-1)
        {
            puts("List is Full!");
            return;
        }
        if(P < 0 || P > L.Length)
        {
            puts("Wrong Position!");
            return;
        }
        for(int i = L.Length; i >= P + 1; --i)
            L.data[i + 1]=L.data[i];
        L.Length++;
        L.data[P + 1] = x;
    }
    int IsSorted(List &L)//判断线性表 L 的顺序，0:乱序 1:小到大 2:大到小 3:无法确定。
    {
        int IsUpper = -1;
        if(L.Length <= 2)
            return L.data[1] < L.data[2] ? 1 : 2;
        for(int i = 2; i <= L.Length; ++i)
        {
            if(L.data[i] > L.data[i - 1])
            {
                if(IsUpper == 0) return 0;
                IsUpper = 1;
            }
            else if(L.data[i] < L.data[i - 1])
            {
                if(IsUpper == 1) return 0;
                IsUpper = 0;
            }
        }
        return IsUpper ? 1 : 2;
    }
    void DelRepeatedEleSorted(List &L)//对于已排好序的线性表 L ，删除所有重复元素。
    {
        if(!IsSorted(L))
        {
            puts("List is Not Sorted");
            return;
        }
        int p = 1;
        for(int i = 2; i <= L.Length; ++i)
        {
            if(L.data[i] != L.data[p])
                L.data[++p] = L.data[i];
        }
        L.Length = p;
    }
    void Reverse(List &L)//逆置线性表 L 。
    {
        int Half = L.Length >> 1;
        for(int i = 1; i <= Half; ++i)
            swap(L.data[i], L.data[L.Length - i + 1]);
    }
    void Move2Left(int k, List &L)//线性表 L 循环左移 k 位。
    {
        k %= L.Length;
        for(int i = k + 1; i <= L.Length; ++i)
            Tmp.data[i - k] = L.data[i];
        for(int i = 1; i <= k ; ++i)
            Tmp.data[i + L.Length - k] = L.data[i];
        for(int i = 1; i <= L.Length; ++i)
            L.data[i] = Tmp.data[i];
    }
    void Move2Right(int k, List &L)//线性表 L 循环右移 k 位。
    {
        k %= L.Length;
        Move2Left(L.Length - k, L);
    }
    List MergeListSorted(List &L1, List &L2)//合并两个已排好序的线性表 L1 和 L2 。
    {
        int L1Upper = IsSorted(L1), L2Upper = IsSorted(L2);
        if(!L1Upper || !L2Upper)
        {
            puts("List is Not Sorted");
            Tmp.Length = 0;
            return Tmp;
        }
        if(L1Upper != L2Upper && L1Upper !=3 && L2Upper != 3)
        {
            puts("Two List are Not In The Same Order!");
            Tmp.Length = 0;
            return Tmp;
        }
        int p = 0, L1p = 0, L2p = 0;
        while(true)
        {
            if(L1p == L1.Length || L2p == L2.Length)
            {
                while(L1p != L1.Length)
                    Tmp.data[++p] = L1.data[++L1p];
                while(L2p != L2.Length)
                    Tmp.data[++p] = L2.data[++L2p];
                break;
            }
            if(L1Upper == 1)
            {
                if(L1.data[L1p + 1] >= L2.data[L2p + 1])
                    Tmp.data[++p] = L2.data[++L2p];
                else Tmp.data[++p] = L1.data[++L1p];
            }
            else 
            {
                if(L1.data[L1p + 1] <= L2.data[L2p + 1])
                    Tmp.data[++p] = L2.data[++L2p];
                else Tmp.data[++p] = L1.data[++L1p];
            }
        }
        Tmp.Length = p;
        return Tmp;
    }
    List InputNewList(int Length)//输入一个长为 Length 新的线性表，并返回它。
    {
        List Res;
        Res.Length = Length;
        for (int i = 1; i <= Length; ++i)
        {
            cin >> Res.data[i];
        }
        return Res;
    }
    void print(List L)//输出线性表 L 。
    {
        for(int i = 1;i <= L.Length; ++i)
        {
            cout << L.data[i] << " ";
        }
        cout<<" SeqListEnd!\n";
    }
}
namespace LinkLis
{
    struct List
    {
        Datatype data;
        List *Next;
        List()
        {
            this->Next = NULL;
        }
    };
    typedef List * Ele;
    Ele NewEle()//新建线性表元素。
    {
        Ele x = new List;
        x->Next = NULL;
        return x;
    }
    int GetLength(Ele Head)//返回以 Head 为头的线性表的长度。
    {
        int cnt = 0;
        while(Head->Next != NULL)cnt++, Head = Head->Next;
        
        return cnt;
    }
    Ele InputNewList(int Length)//输入一个长为 Length 新的线性表，并返回它。
    {
        Ele Head = new List, now = Head;
        for (int i = 1; i <= Length; ++i)
        {
            now->Next = NewEle();
            cin >> now->Next->data;
            now = now->Next;
        }
        return Head;
    }
    void Insert(Datatype x, int P, Ele &Head)//对于以 Head 为头的线性表，在位置 P 后插入元素 x 。
    {
        if(GetLength(Head) == MAXN-1)
        {
            puts("List is Full!");
            return;
        }
        if(P < 0 || P > GetLength(Head))
        {
            puts("Wrong Position!");
            return;
        }
        int cnt = 0;
        Ele now = Head;
        while(cnt < P)
        {
            now = now -> Next;
            cnt++;
        }
        Ele Tmp;
        Tmp = now->Next;
        now->Next = NewEle();
        now->Next->data = x;
        now->Next->Next = Tmp;
    }
    void Del(int P, Ele &Head)//对于以 Head 为头的线性表，删除位置为 P 的元素。
    {
        if(P <= 0 || P > GetLength(Head))
        {
            puts("Wrong Position!");
            return;
        }
        int cnt = 0;
        Ele now = Head, Tmp;
        while(cnt < P - 1)
        {
            now = now->Next;
            cnt++;
        }
        Tmp = now->Next;
        now->Next = now->Next->Next;
        delete Tmp;

    }
    int IsSorted(Ele &Head)//判断以 Head 为头的线性表的顺序，0:乱序 1:小到大 2:大到小 3:无法确定。
    {
        int IsUpper = -1;
        if(Head->Next->Next == NULL)
            return 3;
        for(Ele i = Head->Next->Next, j = Head->Next; i != NULL; i = i->Next, j = j->Next)
        {
            if(i->data > j->data)
            {
                if(IsUpper == 0) return 0;
                IsUpper = 1;
            }
            else if(i->data < j->data)
            {
                if(IsUpper == 1) return 0;
                IsUpper = 0;
            }
        }
        return IsUpper ? 1 : 2;
    }
    void DelRepeatedEleSorted(Ele &Head)//对于已排好序的以 Head 为头的线性表，删除所有重复元素。
    {
        if(!IsSorted(Head))
        {
            puts("List is Not Sorted");
            return;
        }
        Ele p = Head->Next;
        for(Ele i = Head->Next->Next; i != NULL; i = i->Next)
        {
            if(i->data != p->data)
                p->Next->data = i->data, p = p->Next;
        }
        p->Next = NULL;
    }
    void Reverse(Ele &Head)//逆置以 Head 为头的线性表。
    {
        if(Head->Next->Next == NULL)return;
        bool First = 1;
        Ele p = Head->Next, q = p->Next, tmp;
        while(q != NULL)
        {
            Head->Next = q;
            tmp = q->Next;
            q->Next = p;
            if(First)
            {
                p->Next = NULL;
                First = 0;
            }
            p = q;
            q = tmp;
        }
    }
    void Move2Left(int k, Ele &Head)//以 Head 为头的线性表循环左移 k 位。
    {
        k %= GetLength(Head);
        Ele Tail = Head;
        while(Tail->Next != NULL)
            Tail=Tail->Next;
        while(k--)
        {
            Tail->Next = Head->Next;
            Head->Next = Head->Next->Next;
            Tail = Tail->Next;
            Tail->Next = NULL;
        }
    }
    void Move2Right(int k, Ele &Head)//以 Head 为头的线性表循环右移 k 位。
    {
        int Length = GetLength(Head); 
        k %= Length;
        Move2Left(Length - k, Head);
    }
    
    Ele MergeListSorted(Ele &H1, Ele &H2)//合并两个已排好序的以 Head1 Head2 为头的线性表。
    {
        Ele Tmp = NewEle();
        Ele TmpHead = Tmp;
        int H1Upper = IsSorted(H1), H2Upper = IsSorted(H2);
        if(!H1Upper || !H2Upper)
        {
            puts("List is Not Sorted");
            return Tmp;
        }
        if(H1Upper != H2Upper && H1Upper !=3 && H2Upper != 3)
        {
            puts("Two List are Not In The Same Order!");
            return Tmp;
        }
        while(true)
        {
            if(H1->Next == NULL || H2->Next == NULL)
            {
                while(H1->Next != NULL)
                    Tmp->Next = NewEle(), Tmp->Next->data = H1->Next->data, Tmp = Tmp->Next, H1 = H1->Next;
                while(H2->Next != NULL)
                    Tmp->Next = NewEle(), Tmp->Next->data = H2->Next->data, Tmp = Tmp->Next, H2 = H2->Next;
                break;
            }
            Tmp->Next = NewEle();
            if(H1Upper == 1)
            {
                if(H1->Next->data >= H2->Next->data)
                    Tmp->Next->data = H2->Next->data, Tmp = Tmp->Next, H2 = H2->Next;
                else Tmp->Next->data = H1->Next->data, Tmp = Tmp->Next, H1 = H1->Next;
            }
            else 
            {
                if(H1->Next->data <= H2->Next->data)
                    Tmp->Next->data = H2->Next->data, Tmp = Tmp->Next, H2 = H2->Next;
                else Tmp->Next->data = H1->Next->data, Tmp = Tmp->Next, H1 = H1->Next;
            }
        }
        return TmpHead;

    }
    void print(Ele Head)//输出以 Head 为头的线性表。
    {
        while(Head->Next != NULL)cout<<Head->Next->data<<" ", Head=Head->Next;
        cout<<" LinkListEnd!\n";
    }
}

void Test_SeqLis()
{
    SeqLis::List Test_List;
    int Option_Num;
    cin >> Option_Num;
    while(Option_Num--)
    {
        /*
        Option_Type Option
        0    Insert
        1    Del
        2    DelRepeatedEleSorted
        3    Reverse
        4    Move2Left
        5    Move2Right
        6    MergeListSorted
        7    InputNewList
        */
        int Option_Type;
        cin >> Option_Type;
        if (Option_Type == 0)
        {
            Datatype x;
            int P;
            cin >> x >> P;
            SeqLis::Insert(x, P, Test_List);
            SeqLis::print(Test_List);
        }
        else if(Option_Type == 1)
        {
            int P;
            cin >> P;
            SeqLis::Del(P, Test_List);
            SeqLis::print(Test_List);
        }
        else if(Option_Type == 2)
        {
            SeqLis::DelRepeatedEleSorted(Test_List);
            SeqLis::print(Test_List);
        }
        else if(Option_Type == 3)
        {
            SeqLis::Reverse(Test_List);
            SeqLis::print(Test_List);
        }
        else if(Option_Type == 4)
        {
            int k;
            cin >> k;
            SeqLis::Move2Left(k, Test_List);
            SeqLis::print(Test_List);
        }
        else if(Option_Type == 5)
        {
            int k;
            cin >> k;
            SeqLis::Move2Right(k, Test_List);
            SeqLis::print(Test_List);
        }
        else if(Option_Type == 6)
        {
            int x;
            SeqLis::List L1, L2;
            puts("Pleae input 2 sorted list as the following form \"Length Data1 Data2 ...\":");
            cin >> x;
            L1 = SeqLis::InputNewList(x);
            cin >> x;
            L2 = SeqLis::InputNewList(x);
            SeqLis::print(SeqLis::MergeListSorted(L1, L2));
        }
        else 
        {
            int x;
            cin >> x;
            Test_List = SeqLis::InputNewList(x);
            SeqLis::print(Test_List);
        }
    }
}
void Test_LinkLis()
{
    LinkLis::Ele Test_List = new LinkLis::List;
    int Option_Num;
    cin >> Option_Num;
    while(Option_Num--)
    {
        /*
        Option_Type Option
        0    Insert
        1    Del
        2    DelRepeatedEleSorted
        3    Reverse
        4    Move2Left
        5    Move2Right
        6    MergeListSorted
        7    InputNewList
        */
        int Option_Type;
        cin >> Option_Type;
        if (Option_Type == 0)
        {
            Datatype x;
            int P;
            cin >> x >> P;
            LinkLis::Insert(x, P, Test_List);
            LinkLis::print(Test_List);
        }
        else if(Option_Type == 1)
        {
            int P;
            cin >> P;
            LinkLis::Del(P, Test_List);
            LinkLis::print(Test_List);
        }
        else if(Option_Type == 2)
        {
            LinkLis::DelRepeatedEleSorted(Test_List);
            LinkLis::print(Test_List);
        }
        else if(Option_Type == 3)
        {
            LinkLis::Reverse(Test_List);
            LinkLis::print(Test_List);
        }
        else if(Option_Type == 4)
        {
            int k;
            cin >> k;
            LinkLis::Move2Left(k, Test_List);
            LinkLis::print(Test_List);
        }
        else if(Option_Type == 5)
        {
            int k;
            cin >> k;
            LinkLis::Move2Right(k, Test_List);
            LinkLis::print(Test_List);
        }
        else if(Option_Type == 6)
        {
            int x;
            LinkLis::Ele L1 = new LinkLis::List, L2 = new LinkLis::List;
            puts("Pleae input 2 sorted list as the following form \"Length Data1 Data2 ...\":");
            cin >> x;
            L1 = LinkLis::InputNewList(x);
            cin >> x;
            L2 = LinkLis::InputNewList(x);
            LinkLis::print(LinkLis::MergeListSorted(L1, L2));
        }
        else 
        {
            int x;
            cin >> x;
            Test_List = LinkLis::InputNewList(x);
            LinkLis::print(Test_List);
        }
    }
}
int main()
{
    Test_SeqLis();
    Test_LinkLis();
    return 0;
}
