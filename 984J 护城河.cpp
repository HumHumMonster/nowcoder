/*

984J 护城河.cpp

牛客https://ac.nowcoder.com/acm/contest/984/J

一个简单的凸包题

给一些点，要求围一个范围，把点都围进去，要求范围的边界最短

*/



#include <stdio.h>
#include <math.h>
using namespace std ;

const int MAXN = 5e3 + 10 ;
const double eps = 1e-8 ;
int sgn(double x)
{
    if (fabs(x) < eps)
        return 0 ;
    else if (x > 0)
        return 1 ;
    else
        return -1 ;
}


struct Point
{
    double x , y ;
    bool flag ;
    Point()
    {
        flag = false ;
    }
    Point(double _x , double _y)
    {
        x = _x ;
        y = _y ;
        flag = false ;
    }
    bool operator < (Point b)const
    {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x ;
    }
    Point operator - (const Point &b)const
    {
        return Point(x - b.x , y - b.y) ;
    }
    double operator ^ (const Point &b)const
    {
        return x * b.y - y * b.x ;
    }
    double distance(Point p)
    {
        return hypot(x - p.x , y - p.y) ;
    }
}point[MAXN];

Point mi ;

bool cmp(Point a , Point b)
{
    Point p = mi ;
    int d = sgn((a - p) ^ (b - p)) ;
    if (d == 0)
        return sgn(a.distance(p) - b.distance(p)) > 0 ;
    return d > 0 ;
}

int n ;
double res ;

int main ()
{
    scanf ("%d" , &n) ;
    for (int i = 1 ; i <= n ; ++i)
    {
        scanf ("%lf%lf" , &point[i].x , &point[i].y) ;
    }
    mi = point[1] ;
    int id = 1 ;
    for (int i = 2 ; i <= n ; ++i)
    {
        if (mi < point[i])
            continue ;
        mi = point[i] ;
        id = i ;
    }
    //printf ("%f  %f\n" , mi.x , mi.y) ;
    while (1)
    {
        Point u = point[1] ;
        int idp = 1 ;
        for (int i = 2 ; i <= n ; ++i)
        {
            if (cmp(point[i] , u))
            {
                u = point[i] ;
                idp = i ;
            }
        }
        res += u.distance(mi) ;
        if (idp == id)
        {
            printf ("%.2f" , res) ;
            return 0 ;
        }
        mi = u ;
    }
}
