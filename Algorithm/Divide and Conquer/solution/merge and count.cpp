/*
Name:
Copyright:
Author: Json Lee
Date: 25/09/16 22:30
Description:
divide and conquer,
the nums of inversions can be cpmputed by this, inversions of left part and right part, and the inversions of merging the left and right part
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<time.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7ffffffff;
ll ans;//the answer 
ll a[100001];//the array which contains 100001 elements
//calculate the inversions of the left part and right part 
ll merge_and_count(ll array[], ll low, ll mid, ll high)
{
	ll count = 0/*, i = 0, j = 0, k = 0*/;
	ll left_len = mid - low + 1;
	ll right_len = high - mid;
	ll *left = new ll[left_len + 1];
	ll *right = new ll[right_len + 1];
	ll i, j, k;
	//get the copy of left part
	//memcpy(left,array+low,left_len);
	for (i = 0; i < left_len; ++i)	left[i] = array[low + i];
	left[i] = INF;
	//get copy of right part
	//memcpy(right,array+mid+1,right_len);
	for (i = 0; i < right_len; ++i)	right[i] = array[mid + i + 1];
	right[i] = INF;
	
	for (i=0,j=0,k = low; k<high + 1; ++k)
	{
		if (left[i]>right[j])
		{
			array[k] = right[j];
			++j;
			count += left_len - i;
		}
		else
		{
			array[k] = left[i];
			++i;
		}
	}
	delete left, right;
	return count;
}
//return the inversion of array
ll sort_and_count(ll array[], ll low, ll high)
{
	ll c=0, mid;
	if(low< high)
	{
		mid = (low + high) / 2;
		c += sort_and_count(array, low, mid);
		c += sort_and_count(array, mid + 1, high);
		c += merge_and_count(array, low, mid, high);
	}
	return c;
}
int main()
{
	ll a[] = { 2, 8, 3, 6, 1 };
	clock_t t1, t2;
	t1 = clock();
	ans=sort_and_count(a, 0, 4);
	t2 = clock();
	double duration = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout <<ans<<endl;
	cout << "time consumption: " << duration << " s" << endl;
	//system("pause");
	return 0;
}
