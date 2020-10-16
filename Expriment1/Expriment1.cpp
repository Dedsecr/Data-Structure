#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
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
        if(x == 0) return y;
        return gcd(y % x, x);
    }
    void Simplification()
    {
        int _ = gcd(numerator, denominator);
        numerator /= _;
        denominator /= _;
    }
    bool operator < (const Fraction _)const
    {
        return 1.0 * numerator / denominator < 1.0 * _.numerator / _.denominator;
    }
    bool operator > (const Fraction _)const
    {
        return 1.0 * numerator / denominator > 1.0 * _.numerator / _.denominator;
    }
    bool operator == (const Fraction _)const
    {
        return (numerator == _.numerator) && (denominator == _.denominator);
    }
    Fraction operator * (const Fraction _)const
    {
        Fraction Res;
        Res.numerator = numerator * _.numerator;
        Res.denominator = denominator * _.denominator;
        Res.Simplification();
        return Res;
    }
    Fraction operator / (const Fraction _)const
    {
        Fraction Res;
        Res.numerator = numerator * _.denominator;
        Res.denominator = denominator * _.numerator;
        Res.Simplification();
        return Res;
    }
};
struct EleNum
{
    Fraction coef;
    int expo;
    EleNum(){}
    EleNum(Fraction _c, int _e)
    {
        coef = _c, expo = _e;
    }
};
struct Ele
{
    EleNum Elements;
    int Next;
    Ele(){}
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
    Polyn(){}
    Polyn(int _L)
    {
        AvailableP = 0;
        Length = _L;
        for(int i = 1; i <= _L; ++i)
        {
            Available[++AvailableP] = AvailableP;
        }
    }
};
int GetNewPos(Polyn polyn)
{
    return polyn.Available[polyn.AvailableP--];
}
bool IsDigit(char x)
{
    return x >= '0' && x <= '9';
}
bool CoefIsLigal(string x)
{
    int Len = x.length();
    for(int i = 0; i < Len; ++i)
    {
        if((!IsDigit(x[i]) && x[i] != '/') || (x[i] == '/' && (i == 0 || i == Len - 1)))
            return 0;
    }
    return 1;
}
bool ExpoIsLigal(string x)
{
    int Len = x.length();
    for(int i = 0; i < Len; ++i)
    {
        if(!IsDigit(x[i]))
            return 0;
    }
    return 1;
}
int IsFrac(string x)
{
    int Len = x.length();
    for(int i = 0; i < Len; ++i)
    {
        if(x[i] == '/')
            return i + 1;
    }
    return 0;
}
bool GetElements(int Pos, Polyn &polyn)
{
    string input1, input2;
    int input1L, input2L, FracP;
    cin >> input1 >> input2;
    if(!CoefIsLigal(input1) || !ExpoIsLigal(input2))
        return 0;
    input1L = input1.length();
    input2L = input2.length();

    FracP = IsFrac(input1);
    if(FracP)
    {
        FracP --;
        int x = 0;
        for(int i = 0; i < FracP; ++i)
        {
            x = x * 10 + input1[i] - '0';
        }
        polyn.Elements[Pos].Elements.coef.numerator = x;
        x = 0;
        for(int i = FracP + 1; i < input1L; ++i)
        {
            x = x * 10 + input1[i] - '0';
        }
        polyn.Elements[Pos].Elements.coef.denominator = x;
    }
    else
    {
        int x = 0;
        for(int i = 0; i < input1L; ++i)
        {
            x = x * 10 + input1[i] - '0';
        }
        polyn.Elements[Pos].Elements.coef.numerator = x;
        polyn.Elements[Pos].Elements.coef.denominator = 1;
    }
    
    int x = 0;
    for(int i = 0; i < input2L; ++i)
    {
        x = x * 10 + input2[i] - '0';
    }
    polyn.Elements[Pos].Elements.expo = x;
    
    return 1;
}
bool Cmp(const Polyn &a, const Polyn &b)
{
    return a.Elements->Elements.expo < b.Elements->Elements.expo;
}
Polyn Input(int Length)
{
    Polyn Res(Length);
    for(int i = 1; i <= Length; ++i)
    {
        int NewPos = GetNewPos(Res);
        
        while(!GetElements(NewPos, Res))
        {
            puts("Wrong format!");
        }
        //scanf("%d%d",&Res.Elements->Elements.coef, &Res.Elements->Elements.expo);
    }
    sort(Res.Elements + 1, Res.Elements + 1 + Length, Cmp);
    return Res;
}
Polyn Add(Polyn A, Polyn B)
{
    Polyn Res;
    
}

int main()
{

    return 0;
}