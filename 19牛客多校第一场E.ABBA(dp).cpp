/*
19牛客多校第一场E.ABBA(dp).cpp

问给你长度为2*（n+m）的字符串，由n+m个‘A'和’B'组成，要求有n个AB子序列，和m个BA子序列，这样的串有多少种 ？ 

先看一个合法串什么什么样的，因为子序列有n个AB，m个BA，那么显然前n个A必为AB的A，前m个B必为BA的B，因为如果我前n个A中有一个是BA的A,那么我们可以从更后面 随便找一个A给这个B用。

定义dp状态： dp[i][j] 为放了i个A，j个B，合法的状态数。

放A：
如果i < n 那么可以直接放这个A，理由如上。

B 同理：
如果j< m 直接放这个B


题目很好！好玩的是这题用memset会超时hhhh
必须用两个for循环清空dp数组
*/


#include <stdio.h>
#include <string.h>

#define LL long long
int n , m ;
const int MAXN = 1e3 + 10 ;
LL dp[MAXN << 1][MAXN << 1] ;
const LL MOD = 1e9 + 7 ;
int main ()
{
    while (scanf ("%d%d" , &n , &m) != EOF)
    {
        //memset (dp , 0 , sizeof (dp)) ;
        for (int i = 0 ; i <= n + m ; ++i)
            for (int j = 0 ; j <= n + m ; ++j)
                dp[i][j] = 0 ;
        dp[0][0] = 1 ;
        for (int i = 0 ; i <= n + m ; ++i)
        {
            for (int j = 0 ; j <= n + m ; ++j)
            {
                if (i < n || i - n < j)
                    dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD ;
                if (j < m || j - m < i)
                    dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % MOD ;
            }
        }
        printf ("%lld\n" , dp[n + m][n + m]) ;
    }
    return 0 ;
}
