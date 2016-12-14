#include <cstdio> 
#include <climits>
#include <algorithm>
#include <cstring>
#include <iostream> 
using namespace std;
const int MAXN=1001;
//const int MAXM=1001;

//source node and the sink node
int s, t;
//the matrix's size:m*n
int m, n;
//row sum
int row_sum[MAXN];
//column sum
int column_sum[MAXN];
//capacity of each edge
int c[MAXN][MAXN];
//flow of each edge
int f[MAXN][MAXN];
//stock of each node
int e[MAXN];
//height of each node
int h[MAXN];

//push operation
void push(int u, int v)
{
    int d = min(e[u], c[u][v] - f[u][v]);
    f[u][v] += d;
    f[v][u] = -f[u][v];
    e[u] -= d;
    e[v] += d;
}

//relabel operation
bool relabel(int u)
{
    int mh = INT_MAX;
    for(int i=0; i<n+m+2; ++i)
    {
        if(c[u][i] > f[u][i])
            mh = min(mh, h[i]);
    }
    if(mh == INT_MAX)
        return false; //there is no way start from the node u in the residual nework
    h[u] = mh + 1;
    for(int i=0; i<n+m+2; ++i)
    {
        //no need to push
        if(e[u] == 0)
            break;
        //meet the codition of push operation
        if(h[i] == mh && c[u][i] > f[u][i]) 
            push(u, i);
    }
    return true;
}

//initialize the preflow
void init_preflow()
{
    memset(h, 0, sizeof(h));
    memset(e, 0, sizeof(e));
    h[s] = n+2;
    for(int i=0; i<n+m+2; ++i)
    {
        if(c[s][i] == 0)
            continue;
        f[s][i] = c[s][i];
        f[i][s] = -f[s][i];
        e[i] = c[s][i];
        e[s] -= c[s][i];
    }
}

//push relabel algorithm
void push_relabel()
{
    init_preflow();
    //whether there is relabel operation 
    bool flag = true;
    while(flag)
    {
        flag = false;
        for(int i=0; i<n+m; ++i)
            if(e[i] > 0)
                flag = flag || relabel(i);
    }
}

int main()
{
    freopen("in.txt","r",stdin);
    while(cin>>m>>n)
    {
        //0~m-1 is the row node,m~m+n-1 is the column node, s is m+n, t is m+n+1
        s=m+n;
        t=s+1;
        memset(c, 0, sizeof(c));
        memset(f, 0, sizeof(f));
        //get the input
        for(int i=0;i<m;++i)
            cin>>row_sum[i];
        for(int i=0;i<n;++i)
            cin>>column_sum[i];
        //set the capacity of s to each row node to its row sum
        for(int i=0;i<m;++i)
        {
            c[s][i]=row_sum[i];
        }
        //set the capacity of each column node to t to its column sum
        for(int i=0;i<n;++i)
        {
            c[m+i][t]=column_sum[i];
        }
        //set the capacity of each row node to column node to 1 
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                c[i][m+j]=1;
            }
        }
        push_relabel();
        //cout<<e[t]<<endl;

        //total row sum
        int sum=0;
        for(int i=0;i<m;++i)
            sum+=row_sum[i];
        //the matrix really exists
        if(sum==e[t])
        {
            //output the matrix
            for(int i=0;i<m;++i)
            {
                for(int j=0;j<n;++j)
                {
                    //matrix[i][j]=f[i][m+j];
                    cout<<f[i][m+j]<<" ";
                }
                cout<<endl;
            }
        }
        else
        {
            cout<<"the matrix does not exist!"<<endl;
        }
    }
}
