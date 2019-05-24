/*

https://ac.nowcoder.com/acm/contest/894/B

给出四个整数n , m , L , R
现在给出 n 个数，构成A数组
给出 m 个数，构成B数组
你会得到C二维数组
C[i][j] = A[i] * B[j]
现在规定一个矩阵的权为该矩阵所有数的和
那么你的C矩阵中有多少子矩阵的权是在[L , R]之间的

思路：
求A数组和B数组的前缀和
你会发现以[x1][y1] ~ [x2][y2]这个矩阵的权值等于数组A中[x1 , x2]的和与数组B中[y1 , y2]的和的乘积
你可以通过前缀和得到区间和
那么你可以把所有数组B的区间和放到一个vector中
对数组A的每个数你可以用二分查找来找相应的区间


这个题对upper_bound的应用有点妙~
*/

#include <unordered_map>
#include <unordered_set>
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

LL n , m ;
const LL MAXN = 1e3 + 10 ;
LL sum_a[MAXN] , sum_b[MAXN] ;
LL now ;
LL L , R ;
LL res ;
vector <LL> V ;
int main ()
{
    while (scanf ("%lld%lld" , &n , &m) != EOF)
    {
        V.clear() ;
        sum_a[0] = sum_b[0] = 0 ;
        res = 0 ;
        scanf ("%lld%lld" , &L , &R) ;
        for (LL i = 1 ; i <= n ; ++i)
        {
            scanf ("%lld" , &now) ;
            sum_a[i] = sum_a[i - 1] + now ;
        }
        for (LL i = 1 ; i <= m ; ++i)
        {
            scanf ("%lld" , &now) ;
            sum_b[i] = sum_b[i - 1] + now ;
        }
        for (LL i = 1 ; i <= m ; ++i)
        {
            for (LL j = i ; j <= m ; ++j)
            {
                V.push_back(sum_b[j] - sum_b[i - 1]) ;
            }
        }
        sort (V.begin() , V.end()) ;
//        for (int i = 0 ; i < V.size() ; ++i)
//            printf ("%lld\n" , V[i]) ;
        for (int i = 1 ; i <= n ; ++i)
        {
            for (int j = i ; j <= n ; ++j)
            {
                now = sum_a[j] - sum_a[i - 1] ;
                LL resl = L / now ;
                LL resr = R / now ;
                if (resl * now < L)
                    ++resl ;
                if (resr * now > R)
                    --resr ;
                //printf ("now = %lld   resl = %lld  resr = %lld\n" , now , resl , resr) ;
                res += upper_bound(V.begin() , V.end() , resr) - lower_bound(V.begin() , V.end() , resl) ;
            }
        }
        printf ("%lld\n" , res) ;
    }
}

