/*
19牛客多校第九场D.Knapsack Cryptosystem(二分枚举).cpp
给出36个数
问取出哪些数可以使得和为sum

每个数都有两种可能，取与不取，共有2^36的可能
但是分成两边就是2^18 + 2^18不会超时

*/


#include <stdio.h>
#include <iostream>
#include <map>
using namespace std ;

#define LL long long
LL n , sum ;
const int MAXN = 40 ;
LL num[MAXN] ;

map <LL , int > M ;
int tot ;
int ha , biu ;
int main ()
{
    scanf ("%lld%lld" , &n , &sum) ;
    for (int i = 1 ; i <= n ; ++i)
    {
        scanf ("%lld" , &num[i]) ;
    }
    ha = n / 2 ;
    tot = (1 << ha) - 1 ;
    for (int i = 0 ; i <= tot ; ++i)
    {
        LL now = 0 ;
        for (int j = 0 ; j < ha ; ++j)
        {
            if ((i >> j) & 1)
            {
                now += num[j + 1] ;
            }
        }
        M[now] = i ;
    }
    biu = n - ha ;
    tot = (1 << biu) - 1 ;
    for (int i = 0 ; i <= tot ; ++i)
    {
        LL now = 0 ;
        for (int j = 0 ; j < biu ; ++j)
        {
            if ((i >> j) & 1)
            {
                now += num[j + ha + 1] ;
            }
        }
        if (M.count(sum - now))
        {
            int u = M[sum - now] ;
            for (int j = 0 ; j < ha ; ++j)
            {
                if ((u >> j) & 1)
                {
                    printf ("1") ;
                }
                else
                {
                    printf ("0") ;
                }
            }
            for (int j = 0 ; j < biu ; ++j)
            {
                if ((i >> j) & 1)
                {
                    printf ("1") ;
                }
                else
                {
                    printf ("0") ;
                }
            }
            return 0 ;
        }
    }
}
