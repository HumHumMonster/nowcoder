/*
699A (二分查找、素数筛).cpp

给出一个T
给出T个数
输出离这些数最近的素数与它的距离


第一次对数组用lower_bound和upper_bound
这道题要用upper_bound,因为我的素数筛模板第一个prime[0]存放的是素数的数量
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

int T ;

LL now ;

const int MAXN = 1e6 ;
LL prime[MAXN + 1] ;

bool notprime[MAXN] ;

void getPrime()
{
    prime[0] = 0 ;
    memset (notprime , false , sizeof (notprime)) ;
    for (int i = 2 ; i <= MAXN ; ++i)
    {
        if (!notprime[i])
            prime[++prime[0]] = i ;
        for (int j = 1 ; j <= prime[0] && prime[j] <= MAXN / i ; ++j)
        {
            notprime[prime[j] * i] = true ;
            if (i % prime[j] == 0)
                break ;
        }
    }
}

int main ()
{
    scanf ("%d" , &T) ;
    getPrime() ;
//    for (int i = 1 ; i <= prime[0] ; ++i)
//    {
//        printf ("i = %d   %lld\n" , i , prime[i]) ;
//        getchar() ;
//    }
    while (T--)
    {
        scanf ("%lld" , &now) ;
        int p = upper_bound(prime , prime + 1 + prime[0] , now) - prime ;
        //printf ("p = %d\n" , p ) ;
        LL res = prime[p] - now ;
        res = _min(now - prime[p - 1] , res) ;
        printf ("%lld %lld\n" , now , res) ;
    }
}
