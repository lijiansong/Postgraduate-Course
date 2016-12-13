#include<iostream>
#include<vector>
using namespace std;
const int MAX_V=100001;
const int MAX_N=100001;
const int MAX_K=100001;
const int INF=0x7ffffffff;
struct edge
{
	int to,cap,rev;
};
vector<edge> G[MAX_V];
bool visited[MAX_V];

void add_edge(int from,int to,int cap)
{
	G[from].push_back((edge){to,cap,G[to].size()});
	G[to].push_back((edge){from,0,G[from].size()-1});
}
int dfs(int v,int t,int f)
{
	if(v==t) return f;
	visited[v]=true;
	for (int i = 0; i < G[v].size(); ++i)
	{
		edge &e=G[v][i];
		if(!visited[e.to]&&e.cap>0)
		{
			int d=dfs(e.to,t,min(f,e.cap));
			if(d>0)
			{
				e.cap-=d;
				G[e.to][e.rev].cap+=d;
				return d;
			}
		}
	}
	return 0;
}
int max_flow(int s,int t)
{
	int flow=0;
	for ( ; ; )
	{
		memset(visited,0,sizeof(visited));
		int f=dfs(s,t,INF);
		if(f==0) return flow;
		flow+=f;
	}
}
int n,k;
bool can[MAX_N][MAX_K];
void solve()
{
	int s=n+k;
	int t=s+1;
	for(int i=0;i<n;++i)
	{
		add_edge(s,i,1);
	}
	for(int i=0;i<k;++i)
	{
		add_edge(t,n+i,1);
	}
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<k;++j)
		{
			if(can[i][j])
			{
				add_edge(i,n+j,1);
			}
		}
	}
	cout<<max_flow(s,t)<<endl;
}
int main()
{
	return 0;
} 
