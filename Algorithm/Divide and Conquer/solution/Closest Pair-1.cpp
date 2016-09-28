/*
	Name: Closest Pair
	Copyright: 
	Author: Json Lee
	Date: 27/09/16 21:49
	Description: divide and conquer
*/
#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <cmath>  
#include <algorithm>  
using namespace std;
const double INF = 1e20;//INF is large enough
const int N = 100005;//max points numbers 
//define the point struct
struct Point  
{  
    double x;  
    double y;  
}point[N];  
int n;//number of points 
int tmpt[N];//temporary array to store the points' order

//bool function, for sorting by x-coordinate
bool cmpxy(const Point& a, const Point& b)  
{  
    if(a.x != b.x)  
        return a.x < b.x;  
    return a.y < b.y;  
}

//bool function, for sorting by y-coordinate
bool cmpy(const int& a, const int& b)  
{  
    return point[a].y < point[b].y;  
}

//return the minimum of a and b 
double min(double a, double b)  
{  
    return a < b ? a : b;  
}  

//return the Euclidean distance of point[i] and point[j]
double dis(int i, int j)  
{  
    return sqrt((point[i].x-point[j].x)*(point[i].x-point[j].x)  
                + (point[i].y-point[j].y)*(point[i].y-point[j].y));  
}  

//return distance of  closest pair
double Closest_Pair(int left, int right)  
{
	//initilize d to large enough
    double d = INF;  
    if(left==right)
        return d;
    if(left + 1 == right)
        return dis(left, right);
    int mid = (left+right)>>1;//(left+right)/2
    //get the left part closest distance
    double d1 = Closest_Pair(left,mid);
    //get the right part closest distance
    double d2 = Closest_Pair(mid+1,right);  
    d = min(d1,d2);
    //conquer to get the closest distance that between left and right
    int i,j,k=0;
    //get the section whose width is d
    for(i = left; i <= right; i++)  
    {
        if(fabs(point[mid].x-point[i].x) <= d)  
            tmpt[k++] = i;
    }
    //sort by y-coordinate
    sort(tmpt,tmpt+k,cmpy);
    //linear scan
    for(i = 0; i < k; i++)  
    {
        for(j = i+1; j < k && point[tmpt[j]].y-point[tmpt[i]].y<d; j++)  
        {
            double d3 = dis(tmpt[i],tmpt[j]);
            if(d > d3)
                d = d3;
        }
    }
    return d;
}

int main()
{
	freopen("p9-in.txt","r",stdin);
    while(scanf("%d",&n)!=EOF)  
    {
        for(int i = 0; i < n; i++)
            scanf("%lf %lf",&point[i].x,&point[i].y);
        //sort by x-coordinate
        sort(point,point+n,cmpxy);
        printf("closest distance: %.2lf\n",Closest_Pair(0,n-1));
    }
    fclose(stdin);
    return 0;
}
