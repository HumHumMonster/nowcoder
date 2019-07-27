/*
884A (图上dp，树的直径).cpp

感觉很难！自己摸索了一个方法

给出n个点，n - 1 条边（一颗树），给出一个k代表有k个人
每条边的长度都为1
给出k个人的位置，要求你选择一个点作为他们的集合点
问所有人到集合点的距离中的最长距离，最少可以是多少？

递推：DFS1处理了每个点到子树中的人的最远距离
DFS2把子树之外的点的距离合并出来，得到每个点到离它最远的人的距离
最后求其中的最小值.


看了题解以后发现果然不是正解！
正解就是树的直径除以二后向上取整
hhhh
*/

//树的直径
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std ;

const int MAXN = 1e5 + 10 ;

int n , m ;
int dp[MAXN] ;
int id[MAXN] ;
int a , b ;
vector <int> V[MAXN] ;

int vis[MAXN] ;
int p ;
int u ;

void DFS(int x , int pre)
{
    //printf ("x = %d   pre = %d\n" , x , pre) ;
    if (vis[x])
    {
        dp[x] = 0 ;
        id[x] = x ;
    }
    for (int i = 0 ; i < V[x].size() ; ++i)
    {
        int to = V[x][i] ;
        if (to == pre)
            continue ;
        DFS(to , x) ;
        if (id[to])
        {
            if (dp[x] < dp[to] + 1)
            {
                dp[x] = dp[to] + 1 ;
                id[x] = id[to] ;
            }
        }
    }
}

int main ()
{
    scanf ("%d%d" , &n , &m) ;
    for (int i = 1 ; i < n ; ++i)
    {
        scanf ("%d%d" , &a , &b) ;
        V[a].push_back(b) ;
        V[b].push_back(a) ;
    }
    for (int i = 1 ; i <= m ; ++i)
    {
        scanf ("%d" , &a) ;
        vis[a] = 1 ;
    }
    DFS(a , 0) ;
    a = id[a] ;
    memset (id , 0 , sizeof (id)) ;
    memset (dp , 0 , sizeof (dp)) ;
    DFS(a , 0) ;
    printf ("%d" , (dp[a] + 1) / 2) ;
}



//图上dp

#include <stdio.h>
#include <string.h>

const int MAXN = 1e5 + 10 ;
const int INF = 0x3f3f3f3f ;
int vis[MAXN] ;
int cnt[MAXN] ;
int n , k ;
int pp[MAXN] ;
int res ;
struct Edge
{
    int to , next ;
}edge[MAXN << 1];

int head[MAXN] , tot ;

int mm1[MAXN] ;
int mm2[MAXN] ;
int dist1[MAXN] ;
int dist2[MAXN] ;

void addedge(int u , int v)
{
    edge[tot].to = v ;
    edge[tot].next = head[u] ;
    head[u] = tot++ ;
}

void init()
{
    tot = 0 ;
    memset(head , -1 , sizeof (head)) ;
}

int a , b ;
void DFS1(int u , int pre)
{
    //printf ("u = %d  pre = %d\n" , u , pre) ;
    for (int i = head[u] ; i != -1 ; i = edge[i].next)
    {
        int v = edge[i].to ;
        if (v == pre)
            continue ;
        DFS1(v , u) ;
        if (!vis[v])
            continue ;
        vis[u] = 1 ;
        if (dist1[v] + 1 > dist1[u])
        {
            mm2[u] = mm1[u] ;
            mm1[u] = v ;
            dist2[u] = dist1[u] ;
            dist1[u] = dist1[v] + 1 ;
        }
        else if (dist1[v] + 1 > dist2[u])
        {
            mm2[u] = v ;
            dist2[u] = dist1[v] + 1 ;
        }
    }
}

void DFS2(int u , int pre)
{
    if (mm1[pre] != u)
    {
        if (dist1[u] < dist1[pre] + 1)
        {
            mm2[u] = mm1[u] ;
            mm1[u] = pre ;
            dist2[u] = dist1[u] ;
            dist1[u] = dist1[pre] + 1 ;
        }
        else if (dist2[u] < dist1[pre] + 1)
        {
            mm2[u] = pre ;
            dist2[u] = dist1[pre] + 1 ;
        }
    }
    else if (mm2[pre] != u)
    {
        if (dist1[u] < dist2[pre] + 1)
        {
            mm2[u] = mm1[u] ;
            mm1[u] = pre ;
            dist2[u] = dist1[u] ;
            dist1[u] = dist2[pre] + 1 ;
        }
        else if (dist2[u] < dist2[pre] + 1)
        {
            mm2[u] = pre ;
            dist2[u] = dist2[pre] + 1 ;
        }
    }
    for (int i = head[u] ; i != -1 ; i = edge[i].next)
    {
        if (edge[i].to == pre)
            continue ;
        DFS2(edge[i].to , u) ;
    }
}

int main ()
{
    init() ;
    scanf ("%d%d" , &n , &k) ;
    for (int i = 1 ; i < n ; ++i)
    {
        scanf ("%d%d" , &a , &b) ;
        addedge(a , b) ;
        addedge(b , a) ;
    }
    for (int i = 1 ; i <= k ; ++i)
    {
        scanf ("%d" , &a) ;
        pp[a] = 1 ;
        vis[a] = 1 ;
    }
//    for (int i = 1 ; i <= n ; ++i)
//    {
//        printf ("i = %d  : " , i) ;
//        for (int j = head[i] ; j != -1 ; j = edge[j].next)
//            printf ("%d " , edge[j].to) ;
//        printf ("\n") ;
//    }
    DFS1(1 , 0) ;
//    for (int i = 1 ; i <= n ; ++i)
//    {
//        printf ("i = %d  dist1 = %d dist2 = %d vis = %d   mm1 = %d  mm2 = %d\n" , i , dist1[i] , dist2[i] , vis[i] , mm1[i] , mm2[i]) ;
//    }


    for (int i = head[1] ; i != -1 ; i = edge[i].next)
    {
        DFS2(edge[i].to , 1) ;
    }


//    printf ("\n") ;
//    for (int i = 1 ; i <= n ; ++i)
//    {
//        printf ("i = %d  dist1 = %d dist2 = %d vis = %d   mm1 = %d  mm2 = %d\n" , i , dist1[i] , dist2[i] , vis[i] , mm1[i] , mm2[i]) ;
//    }

    res = INF ;
    for (int i = 1 ; i <= n ; ++i)
    {
        if (dist1[i] < res)
            res = dist1[i] ;
    }
    printf ("%d" , res) ;
}


