/*

984F 随机数(组合数学).cpp


链接：https://ac.nowcoder.com/acm/contest/984/F
来源：牛客网

正如你所知，奶牛们没有手指以至于不能玩“石头剪刀布”来任意地决定例如谁先挤奶的顺序。她们甚至也不能通过仍硬币的方式。
所以她们通过"round number"竞赛的方式。第一头牛选取一个整数，小于20亿。第二头牛也这样选取一个整数。如果这两个数都是 "round numbers"，那么第一头牛获胜，否则第二头牛获胜。
如果一个正整数N的二进制表示中，0的个数大于或等于1的个数，那么N就被称为"round number" 。例如，整数9，二进制表示是1001，1001 有两个'0'和两个'1'; 因此，9是一个round number。26 的二进制表示是 11010 ; 由于它有2个'0'和3个'1'，所以它不是round number。
很明显，奶牛们会花费很大精力去转换进制，从而确定谁是胜者。 Bessie 想要作弊，而且认为只要她能够知道在一个指定区间范围内的"round numbers"个数。
帮助她写一个程序，能够告诉她在一个闭区间中有多少Hround numbers。区间是[start, finish]，包含这两个数。 (1 <= Start < Finish <= 2,000,000,000)



据说大家都是数位dp，我用组合数学也过了


*/


#include <stdio.h>
#include <string.h>
#define LL long long

int vis[100] ;

const LL INF = 0x3f3f3f3f ;

LL C(LL n , LL b)
{
    for (LL i = 0 ; i <= b ; ++i)
        vis[i] = 0 ;
    if (b > n)
        return 0 ;
    LL res = 1 ;
    for (LL i = n ; i > (n - b) ; --i)
    {
        if (res >= INF)
        {
            for (LL j = 1 ; j <= b ; ++j)
            {
                if (res % j == 0 && vis[j] == 0)
                {
                    res /= j ;
                    vis[j] = 1 ;
                }
            }
        }
        res *= i ;
    }
    for (int j = 1 ; j <= b ; ++j)
    {
        if (!vis[j])
            res /= j ;
    }
    return res ;
}

int num[60] ;

LL solve(LL a , LL b , LL c)
{
    LL res = 0 ;
    for (int i = 0 ; i <= c ; ++i)
    {
        if (a + i >= b + (c - i))
            res += C(c , i) ;
    }
    return res ;
}


LL Solve(LL x)
{
    int id = 0 ;
    while (x)
    {
        num[++id] = x & 1 ;
        x >>= 1 ;
    }
    LL res = 0 ;
    LL b = 1 , a = 0 ;
    for (int i = id - 1 ; i >= 1 ; --i)
    {
        res += solve(0 , 1 , i - 1) ;
        if (num[i] == 1)
        {
            res += solve(a + 1 , b , i - 1) ;
            ++b ;

        }
        else
            ++a ;
    }
    if (a >= b)
        ++res ;
    return res ;
}

LL a , b ;
int main ()
{
    scanf ("%lld %lld" , &a , &b) ;
    printf ("%lld" , Solve(b) - Solve(a - 1)) ;
}
