/*

Bobsledding(变形背包).cpp
https://ac.nowcoder.com/acm/contest/1077/B

题意：
有n种电脑，每种电脑有ki种游戏
每个电脑有自己的价格，游戏也有自己的价格，游戏有自己的贡献度
问给定的钱最多能创造多少

思路：
对每个电脑，在原来的dp基础上买下电脑，然后再对游戏01背包一下


*/


#include <stdio.h>
#define LL long long
const int MAXN = 100000 + 10 ;
LL dp[MAXN] ;
LL now[MAXN] ;

int n , V ;
int p , a , b , u ;

LL _max(LL a , LL b){return a > b ? a : b ;}

int main ()
{
    scanf ("%d%d" , &n , &V) ;
    for (int i = 1 ; i <= n ; ++i)
    {
        scanf ("%d" , &p) ;
        for (int j = p ; j <= V ; ++j)
        {
            now[j] = dp[j - p] ;
        }
        scanf ("%d" , &u) ;
        while (u--)
        {
            scanf ("%d%d" , &a , &b) ;
            for (int j = V - a ; j >= p ; --j)
            {
                now[j + a] =  _max(now[j + a] , now[j] + b) ;
            }
        }
        for (int j = p ; j <= V ; ++j)
        {
            dp[j] = _max(dp[j] , now[j]) ;
        }
    }
//    for (int i = 1 ; i <= V ; ++i)
//    {
//        printf ("i = %d   dp = %lld\n" , i , dp[i]) ;
//    }
    printf ("%lld" , dp[V]) ;
}
