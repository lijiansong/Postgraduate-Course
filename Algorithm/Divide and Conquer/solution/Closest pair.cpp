#include<iostream>
#include<ctime>
#include<algorithm>
using namespace std;
const int MAX_N=100000;
typedef struct point
{
	double x,y;
}point;
point a[MAX_N];
int n,s[MAX_N];
bool cmpx(int i,int j)
{
	return cmp(a[i].x-a[j].x)<0;
}
bool cmpy(int i,int j)
{
	return cmp(a[i].y-a[j].y)<0;
}
double min_dest(point a[],int s[],int l,int r)
{
	double ans=1e100;
	if(r-l<20)
	{
		for(int q=l;q<r;++q)
		{
			for(int w=q+1;w<r;++w)
			{
				ans=min(ans,(a[s[q]]-a[s[w]]).norm());
			}
		}
		return ans;
	}
	int tl,tr,m=(l+r)/2;
	ans=min(min_dist(a,s,l,m),min_dist(a,s,m,r));
	for(tl=l;)
}

int main()
{
	
	return 0;
} 
