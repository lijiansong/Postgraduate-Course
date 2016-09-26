#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define esp 1e-6
using namespace std;
struct point
{
    double x,y;
}p[100010];
int px[100010],py[100010],ty[100010];
int cmpx(const point &a,const point &b)
{
    return a.y<b.y;
}
int cmpy(const int &a,const int &b)
{
    return p[a].x<p[b].x;
}
inline double min(double a,double b)
{
    return a<b?a:b;
}
inline double dist2(point &a,point &b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double min_dis = 1e100;
double mindist(int* X,int *Y,int size)
{
    if(size<=3)
    {
        if(size==2)
        return dist2(p[X[0]],p[X[1]]);
        for(int i=0; i<size; i++)
        min_dis = min(min_dis,dist2(p[X[i]],p[X[(i+1)%size]]));
        return min_dis;
    }
    int pl = (size+1)/2;
    int pr = size - pl;
    int l1 = 0,l2=pl;
    for(int i=0; i<size; i++)
    if(Y[i]<X[pl])
    ty[l1++] = Y[i];
    else ty[l2++] = Y[i];
    for(int i=0; i<size; i++)
    Y[i] = ty[i];
    min_dis = min(mindist(&X[0],&Y[0],pl),mindist(&X[pl],&Y[pl],pr));
    l1 = 0;
    for(int i=0; i<size; i++)
    if((p[Y[i]].x-p[X[pl-1]].x)*(p[Y[i]].x-p[X[pl-1]].x)<=min_dis)
    ty[l1++] = Y[i];
    for(int i=0; i<l1; i++)
    for(int j=1; j<6&&i+j<l1; j++)
    if((ty[i]-X[pl])*(ty[i+j]-X[pl])<=0)
    min_dis = min(min_dis,dist2(p[ty[i]],p[ty[i+j]]));
    return min_dis;
}

int main()
{
	freopen("p9-in.txt","r",stdin); 
    int n;
    for(int i=0; i<100010; i++)
    px[i] = i;
    while(scanf("%d",&n)&&n)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%lf %lf",&p[i].x,&p[i].y);
            py[i] = i;
        }
        sort(p,p+n,cmpx);
        sort(py,py+n,cmpy);
        min_dis = 1e100;
        printf("%.2lf\n",sqrt(mindist(px,py,n))/2);
    }
    return 0;
}
