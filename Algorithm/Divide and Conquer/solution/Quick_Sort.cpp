#include<vector> 
#include<iostream>
#include<cstdlib>
using namespace std;
long long Quick_Sort(vector<int> nums )
{
	if(nums.size() <= 1)return 0;
	unsigned int rad = rand()%(nums.size());
	int key = nums[rad];
	vector<int> bigger,litter;
	long long count = 0;
	for(int i = 0; i < rad ; i++){
		if( key > nums[i] ){
			litter.push_back(nums[i]);
			count += bigger.size();
		}
		else {
			bigger.push_back(nums[i]);
			count++;
		}
	}
	for(int i = rad + 1; i < nums.size() ; i++){
		if( key < nums[i] ){
			bigger.push_back(nums[i]);
		}
		else {
			litter.push_back(nums[i]);
			count++;
			count += bigger.size();
		}
	}
	count += Quick_Sort(litter);
	count += Quick_Sort(bigger);
	return count;
}

int main()
{
	freopen("Q8.txt","r",stdin);
	vector<int> test;
	int n=0;
	while(cin>>n)
	{
		test.push_back(n);
	}
	cout<<Quick_Sort(test)<<endl;
	return 0;
}
