#include <cstdlib>
#include <cstdio>
//#include <sys/wait.h>  
//#include <sys/types.h>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
int main(int argc, char const *argv[])
{
	for(int i=1;i<=34;++i)
	{
		stringstream ss;
		ss<<i;
		//char *num=itoa(i);
		string cmd_str="clang -c -emit-llvm -g3 test"+ss.str()+".c";
		printf("%s\n",cmd_str.c_str());
		system(cmd_str.c_str());
		//delete num;
		ss.clear();
	}
	printf("done!\n");
	return 0;
}