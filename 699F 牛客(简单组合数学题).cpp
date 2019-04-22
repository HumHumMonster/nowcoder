/*

699F 牛客(简单组合数学题).cpp


输入包含7个整数，分别为a ,b ,c, k ,e ,f, g每两个整数之间用一个空格隔开。
求对于(ax+by+cz)的k次方展开式中，(x^e)(y^f)(z^g)的系数是多少
*/


#include <stdio.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <cstring>
#include <stack>
#include <cmath>
#include <queue>
#include <vector>
#include <iterator>
#include <set>
using namespace std ;
#define LL long long
#define INF 0x3f3f3f3f
const double PI = acos(-1.0) ;
const double eps = 1e-8 ;

inline int _max(int a , int b){return a > b ? a : b ;}
inline int _min(int a , int b){return a < b ? a : b ;}
inline int _abs(int a){return a > 0 ? a : -a ;}
inline double _max(double a , double b){return a > b ? a : b ;}
inline double _min(double a , double b){return a < b ? a : b ;}
inline double _fabs(double a){return a > 0 ? a : -a ;}
inline LL _max(LL a , LL b){return a > b ? a : b ;}
inline LL _min(LL a , LL b){return a < b ? a : b ;}
inline LL _labs(LL a){return a > 0 ? a : -a ;}

int sgn(double x)   //判断正负，正为1，零为0，负为-1
{
    if (_fabs(x) < eps) return 0 ;
    else if (x < 0) return -1 ;
    else return 1 ;
}


/***************************************************************/

const LL MOD = 10007 ;
const int MAXN = 1005 ;

LL fac[MAXN],inv[MAXN];
//快速乘法
long long quick_mul(long long a , long long b , long long m)
{
    long long ans = 0 ;
    while (b)
    {
        if (b & 1)
            ans = (ans + a) % m ;
        a = (a + a) % m ;
        b >>= 1 ;
    }
    return ans ;
}
//快速幂
long long quick_pow(long long a , long long b , long long m)
{
    long long ans = 1 ;
    while (b)
    {
        if (b & 1)
            ans = quick_mul(ans , a , m);
        a = quick_mul(a , a , m) ;
        b >>= 1 ;
    }
    return ans ;
}

void init()     //使用前必须init()
{
    LL i;
    fac[0] = fac[1] = 1;
    for(i = 2; i < MAXN; i++)
        fac[i] = fac[i - 1] * i % MOD;
    inv[MAXN - 1] = quick_pow(fac[MAXN - 1] , MOD - 2 , MOD);
    for(i = MAXN - 2; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
}
LL C(LL n,LL k)     //在 n 中选 k 个
{
    return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}

LL a , b , c , k , e , f , g ;

int main ()
{
    init() ;
    scanf ("%lld%lld%lld%lld%lld%lld%lld" , &a , &b , &c , &k , &e , &f , &g) ;
    LL res = (C(k , e) * quick_pow(a , e , MOD)) % MOD ;
    res = (res * (C(k - e , f) * quick_pow(b , f , MOD)) % MOD) % MOD ;
    res = (res * quick_pow(c , g , MOD)) % MOD ;
    printf ("%lld" , res) ;
}
