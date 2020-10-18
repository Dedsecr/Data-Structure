#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
const int MAXN = 100;
struct Fraction
{
    int numerator, denominator;
    Fraction()
    {
        Simplification();
    }
    Fraction(int _n, int _d)
    {
        numerator = _n;
        denominator = _d;
        Simplification();
    }
    Fraction(int _n)
    {
        numerator = _n;
        denominator = 1;
    }
    int gcd(int x, int y)
    {
        if (x == 0)
            return y;
        return gcd(y % x, x);
    }
    void Simplification()
    {
        int _ = gcd(abs(numerator), abs(denominator));
        numerator /= _;
        denominator /= _;
    }
    bool operator < (const Fraction _) const
    {
        return 1.0 * numerator / denominator < 1.0 * _.numerator / _.denominator;
    }
    bool operator > (const Fraction _) const
    {
        return 1.0 * numerator / denominator > 1.0 * _.numerator / _.denominator;
    }
    bool operator == (const Fraction _) const
    {
        return (numerator == _.numerator) && (denominator == _.denominator);
    }
    Fraction operator * (const Fraction _) const
    {
        Fraction Res;
        Res.numerator = numerator * _.numerator;
        Res.denominator = denominator * _.denominator;
        Res.Simplification();
        return Res;
    }
    Fraction operator / (const Fraction _) const
    {
        Fraction Res;
        Res.numerator = numerator * _.denominator;
        Res.denominator = denominator * _.numerator;
        Res.Simplification();
        return Res;
    }
    Fraction operator + (const Fraction _) const
    {
        Fraction Res;
        Res.numerator = numerator * _.denominator + denominator * _.numerator;
        Res.denominator = denominator * _.denominator;
        Res.Simplification();
        return Res;
    }
    Fraction operator - (const Fraction _) const
    {
        Fraction Res;
        Res.numerator = numerator * _.denominator - denominator * _.numerator;
        Res.denominator = denominator * _.denominator;
        Res.Simplification();
        return Res;
    }
};
struct EleNum
{
    Fraction coef;
    int expo;
    EleNum() {}
    EleNum(Fraction _c, int _e)
    {
        coef = _c, expo = _e;
    }
    EleNum operator + (const EleNum _) const
    {
        if(expo != _.expo && expo)
        {
            cerr << "Error in " << __LINE__;
            exit(-1);
        }
        EleNum Res;
        Res.coef = coef + _.coef;
        Res.expo = expo;
        return Res;
    }
    EleNum operator - (const EleNum _) const
    {
        if(expo != _.expo && expo)
        {
            cerr << "Error in " << __LINE__;
            exit(-1);
        }
        EleNum Res;
        Res.coef = coef - _.coef;
        Res.expo = expo;
        return Res;
    }
    EleNum operator * (const EleNum _) const
    {
        EleNum Res;
        Res.coef = coef * _.coef;
        Res.expo = expo + _.expo;
        return Res;
    }
};
struct Ele
{
    EleNum Elements;
    int Next;
    Ele() {}
    Ele(EleNum _E, int _N)
    {
        Elements = _E, Next = _N;
    }
};
struct Polyn
{
    Ele Elements[MAXN];
    int Available[MAXN];
    int Length;
    int AvailableP;
    Polyn() {}
    Polyn(int _L)
    {
        AvailableP = 0;
        Length = _L;
        for (int i = 1; i <= _L; ++i)
        {
            Available[++AvailableP] = AvailableP;
        }
    }
};
EleNum Tmp[MAXN * MAXN], EleNum_Zero = EleNum(0, 0);
int GetNewPos(Polyn &polyn)
{
    int Res = polyn.Available[polyn.AvailableP--];
    polyn.Elements[Res].Next = 0;
    return Res;
}
int GetNewLen(Polyn &A, Polyn &B)
{
    int Res = 0;
    int P_A = A.Elements[0].Next, P_B = B.Elements[0].Next;
    while(P_A && P_B)
    {
        if(A.Elements[P_A].Elements.expo > B.Elements[P_B].Elements.expo)
        {
            Res++;
            P_A = A.Elements[P_A].Next;
        }
        else if(A.Elements[P_A].Elements.expo < B.Elements[P_B].Elements.expo)
        {
            Res++;
            P_B = B.Elements[P_B].Next;
        }
        else
        {
            Res++;
            P_A = A.Elements[P_A].Next;
            P_B = B.Elements[P_B].Next;    
        }
    }
    return Res;
}
int GetNewLen_Multiply(Polyn &A, Polyn &B)
{
    int TmpP = 0, Res = 1;
    for (int P_A = A.Elements[0].Next; P_A; P_A = A.Elements[P_A].Next)
        for (int P_B = B.Elements[0].Next; P_B; P_B = B.Elements[P_B].Next)
            Tmp[++TmpP] = A.Elements[P_A].Elements * B.Elements[P_B].Elements;
    sort(Tmp + 1, Tmp + 1 + TmpP, Cmp);
    for (int i = 2; i <= TmpP; ++i)
        if(Tmp[i].expo != Tmp[i-1].expo)
            Res++;
    return Res;
}
bool IsDigit(char x)
{
    return x >= '0' && x <= '9';
}
bool CoefIsLigal(string x)
{
    int Len = x.length();
    for (int i = 0; i < Len; ++i)
    {
        if ((!IsDigit(x[i]) && x[i] != '/') || (x[i] == '/' && (i == 0 || i == Len - 1)))
            return 0;
    }
    return 1;
}
bool ExpoIsLigal(string x)
{
    int Len = x.length();
    for (int i = 0; i < Len; ++i)
    {
        if (!IsDigit(x[i]))
            return 0;
    }
    return 1;
}
int IsFrac(string x)
{
    int Len = x.length();
    for (int i = 0; i < Len; ++i)
    {
        if (x[i] == '/')
            return i + 1;
    }
    return 0;
}
bool GetElements(int Pos, Polyn &polyn)
{
    string input1, input2;
    int input1L, input2L, FracP;
    cin >> input1 >> input2;
    if (!CoefIsLigal(input1) || !ExpoIsLigal(input2))
        return 0;
    input1L = input1.length();
    input2L = input2.length();

    FracP = IsFrac(input1);
    if (FracP)
    {
        FracP--;
        int x = 0;
        for (int i = 0; i < FracP; ++i)
        {
            x = x * 10 + input1[i] - '0';
        }
        polyn.Elements[Pos].Elements.coef.numerator = x;
        x = 0;
        for (int i = FracP + 1; i < input1L; ++i)
        {
            x = x * 10 + input1[i] - '0';
        }
        polyn.Elements[Pos].Elements.coef.denominator = x;
    }
    else
    {
        int x = 0;
        for (int i = 0; i < input1L; ++i)
        {
            x = x * 10 + input1[i] - '0';
        }
        polyn.Elements[Pos].Elements.coef.numerator = x;
        polyn.Elements[Pos].Elements.coef.denominator = 1;
    }

    int x = 0;
    for (int i = 0; i < input2L; ++i)
    {
        x = x * 10 + input2[i] - '0';
    }
    polyn.Elements[Pos].Elements.expo = x;

    return 1;
}
bool Cmp(const EleNum &a, const EleNum &b)
{
    return a.expo > b.expo;
}
void Sort(Polyn &polyn)
{
    int Length = polyn.Length;
    int P = 0;
    for (int i = 1; i <= Length; ++i)
    {
        P = polyn.Elements[P].Next;
        Tmp[i] = polyn.Elements[P].Elements;
    }
    sort(Tmp + 1, Tmp + 1 + Length, Cmp);
    P = 0;
    for (int i = 1; i <= Length; ++i)
    {
        P = polyn.Elements[P].Next;
        polyn.Elements[P].Elements = Tmp[i];
    }
}
Polyn Input(int Length)
{
    Polyn Res(Length);
    int LastP = 0;
    for (int i = 1; i <= Length; ++i)
    {
        int NewPos = GetNewPos(Res);
        Res.Elements[LastP].Next = NewPos;
        LastP = NewPos;
        while (!GetElements(NewPos, Res))
        {
            puts("Wrong format!");
        }
        Sort(Res);
    }
    return Res;
}
Polyn Add(Polyn &A, Polyn &B)
{
    int _L = GetNewLen(A, B);
    Polyn Res(_L);
    int LastP = 0;
    int P_A = A.Elements[0].Next, P_B = B.Elements[0].Next;
    while(P_A && P_B)
    {
        if(A.Elements[P_A].Elements.expo > B.Elements[P_B].Elements.expo)
        {
            int NewPos = GetNewPos(Res);
            Res.Elements[LastP].Next = NewPos;
            LastP = NewPos;
            Res.Elements[NewPos].Elements = A.Elements[P_A].Elements;
            P_A = A.Elements[P_A].Next;
        }
        else if(A.Elements[P_A].Elements.expo < B.Elements[P_B].Elements.expo)
        {
            int NewPos = GetNewPos(Res);
            Res.Elements[LastP].Next = NewPos;
            LastP = NewPos;
            Res.Elements[NewPos].Elements = B.Elements[P_B].Elements;
            P_B = B.Elements[P_B].Next;
        }
        else
        {
            int NewPos = GetNewPos(Res);
            Res.Elements[LastP].Next = NewPos;
            LastP = NewPos;
            Res.Elements[NewPos].Elements = A.Elements[P_A].Elements + B.Elements[P_B].Elements;
            P_A = A.Elements[P_A].Next;
            P_B = B.Elements[P_B].Next;
        }
    }
    while(P_A)
    {
        int NewPos = GetNewPos(Res);
        Res.Elements[LastP].Next = NewPos;
        LastP = NewPos;
        Res.Elements[NewPos].Elements = A.Elements[P_A].Elements;
        P_A = A.Elements[P_A].Next;
    }
    while(P_B)
    {
        int NewPos = GetNewPos(Res);
        Res.Elements[LastP].Next = NewPos;
        LastP = NewPos;
        Res.Elements[NewPos].Elements = B.Elements[P_B].Elements;
        P_B = B.Elements[P_B].Next;
    }
    return Res;
}
Polyn Minus(Polyn &A, Polyn &B)
{
    int _L = GetNewLen(A, B);
    Polyn Res(_L);
    int LastP = 0;
    int P_A = A.Elements[0].Next, P_B = B.Elements[0].Next;
    while(P_A && P_B)
    {
        if(A.Elements[P_A].Elements.expo > B.Elements[P_B].Elements.expo)
        {
            int NewPos = GetNewPos(Res);
            Res.Elements[LastP].Next = NewPos;
            LastP = NewPos;
            Res.Elements[NewPos].Elements = A.Elements[P_A].Elements;
            P_A = A.Elements[P_A].Next;
        }
        else if(A.Elements[P_A].Elements.expo < B.Elements[P_B].Elements.expo)
        {
            int NewPos = GetNewPos(Res);
            Res.Elements[LastP].Next = NewPos;
            LastP = NewPos;
            Res.Elements[NewPos].Elements = EleNum_Zero - B.Elements[P_B].Elements;
            P_B = B.Elements[P_B].Next;
        }
        else
        {
            int NewPos = GetNewPos(Res);
            Res.Elements[LastP].Next = NewPos;
            LastP = NewPos;
            Res.Elements[NewPos].Elements = A.Elements[P_A].Elements - B.Elements[P_B].Elements;
            P_A = A.Elements[P_A].Next;
            P_B = B.Elements[P_B].Next;
        }
    }
    while(P_A)
    {
        int NewPos = GetNewPos(Res);
        Res.Elements[LastP].Next = NewPos;
        LastP = NewPos;
        Res.Elements[NewPos].Elements = A.Elements[P_A].Elements;
        P_A = A.Elements[P_A].Next;
    }
    while(P_B)
    {
        int NewPos = GetNewPos(Res);
        Res.Elements[LastP].Next = NewPos;
        LastP = NewPos;
        Res.Elements[NewPos].Elements = EleNum_Zero - B.Elements[P_B].Elements;
        P_B = B.Elements[P_B].Next;
    }
    return Res;
}
Polyn Multiply(Polyn &A, Polyn &B)
{
    int _L = GetNewLen_Multiply(A, B);
    Polyn Res(_L);
    int LastP = 0;
    int TmpP = 0;
    for (int P_A = A.Elements[0].Next; P_A; P_A = A.Elements[P_A].Next)
        for (int P_B = B.Elements[0].Next; P_B; P_B = B.Elements[P_B].Next)
            Tmp[++TmpP] = A.Elements[P_A].Elements * B.Elements[P_B].Elements;
    sort(Tmp + 1, Tmp + 1 + TmpP, Cmp);
    Tmp[0].expo = Tmp[1].expo + 1;
    for (int i = 1; i <= TmpP; ++i)
    {
        if(Tmp[i].expo != Tmp[i-1].expo)
        {
            int NewPos = GetNewPos(Res);
            Res.Elements[LastP].Next = NewPos;
            LastP = NewPos;
            Res.Elements[NewPos].Elements = Tmp[i];
        }
        else
            Res.Elements[LastP].Elements = Res.Elements[LastP].Elements + Tmp[i];
    }
    return Res;
}

int main()
{

    return 0;
}