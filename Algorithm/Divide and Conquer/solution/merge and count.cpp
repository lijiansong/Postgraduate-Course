/*
	Name: 
	Copyright: 
	Author: Json Lee 
	Date: 25/09/16 22:30
	Description: 
	divide and conquer,
	the nums of inversions can be cpmputed by this, inversions of left part and right part, and the inversions of merging the left and right part
*/

#include<cstdio>
#include<time.h>
using namespace std;
typedef long long ll;
ll ans;//the answer 
ll a[100001];//the array which contains 100001 elements
//return the inversion of array
ll sort_and_count(ll array[],ll low, ll high)
{
	ll count=0,mid;
	while(low< high)
	{
		mid=(low+high)/2;
		count+=sort_and_count(array,low,mid);
		count+=sort_and_count(array,mid+1,high);
		count+=merge_and_count(array,low,mid,high);
	}
	return count;
}
//calculate the inversions of the left part and right part 
ll merge_and_count(ll array[],ll low,ll mid,ll high)
{
	ll count=0;
	
}
int main()
{
	return 0;
} 
