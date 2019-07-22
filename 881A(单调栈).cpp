/*

881A(单调栈).cpp


题意：
两个长度为n的数组，求最大的m，使得1到m之内的所有区间的最小值位置相同。
思路：
单调栈:
记录每个值的左边第一个比当前值小的位置。
从左到右遍历一遍，记录下第一个单调栈结果不同的地方，该位置前一个位置就是答案。
证明：
如果你确认了位置i是正确的，并且单调栈记录的位置是pos，那么（pos,i）,(pos+1,i）... (i,i)都是符合条件的。
如果pos左侧的值都比pos处的值要大，那么显而易见，（1,i）,（2,i）,...,(pos-1,i)也是符合题意的。
如果pos左侧的值有比pos处的值小的，那么从右边数，第一个比pos小的值的位置pos2，对于两个数组，也一定相等，(因为之前已经检测过pos了，不然也不会走到i)
那么（pos2+1,i),(pos2+2,i)...(pos-1,i)也是符合题意的。
再从pos2开始考虑，用类似递归的思想，很容易明白，（1,i）,（2,i）,...,(pos-1,i)都是符合题意的。
这是右端点是i的情况，但是因为i从左向右遍历，所以之前的所有区间其实都已经检测过了。

再考虑不相等的情况：
如果在位置i，第一个数组从右向左的第一个位置为pos1，第二个是pos2，且pos1<pos2
那么对于第一个数组，（pos2,i)的最小值位置是i，对于第一个数组，（pos2,i)的最小值位置是pos2,显然不同。

*/


#include <stdio.h>
#include <stack>
using namespace std ;


stack <int> S ;

const int MAXN = 1e5 + 10 ;

int n ;
int num1[MAXN] , num2[MAXN] ;

int dp1[MAXN] , dp2[MAXN] ;



int main()
{
    num1[0] = num2[0] = -1 ;
    while (scanf ("%d" , &n) != EOF)
    {
        for (int i = 1 ; i <= n ; ++i)
            scanf ("%d" , &num1[i]) ;
        for (int i = 1 ; i <= n ; ++i)
            scanf ("%d" , &num2[i]) ;
        while (!S.empty())
            S.pop() ;
        for (int i = n ; i >= 0 ; --i)
        {
            while (!S.empty() && num1[S.top()] > num1[i])
            {
                dp1[S.top()] = i ;
                S.pop() ;
            }
            S.push(i) ;
        }
        while (!S.empty())
            S.pop() ;
        for (int i = n ; i >= 0 ; --i)
        {
            while (!S.empty() && num2[S.top()] > num2[i])
            {
                dp2[S.top()] = i ;
                S.pop() ;
            }
            S.push(i) ;
        }
        int res = n ;
        for (int i = 1 ; i <= n ; ++i)
        {
            if (dp1[i] != dp2[i])
            {
                res = i - 1;
                break ;
            }
        }
        printf ("%d\n" , res) ;
    }
}
