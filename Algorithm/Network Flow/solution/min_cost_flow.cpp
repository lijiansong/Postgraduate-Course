#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
using namespace std;
const int MAXV=1001;
const int INF=0x7fffffff;
//the number of nodes and edges
int V,edges;
int supply/*,demand*/;
//source node and the sink node
int s,t;
//edge
struct edge
{
	int to,cap,cost,rev;
};
//the network graph
vector<edge> G[MAXV];
//minimum distance
int dist[MAXV];
//prevv:the previous node in the shortest path
//preve:the edge in the shortest path
int prevv[MAXV],preve[MAXV];

//add edge to construct the graph
void add_edge(int from,int to,int cap,int cost)
{
	edge tmp;
	tmp.to = to, tmp.cap = cap, tmp.cost=cost,tmp.rev = G[to].size();
	G[from].push_back(tmp);
	tmp.to = from, tmp.cap = 0, tmp.cost = -cost, tmp.rev = G[from].size() - 1;
	G[to].push_back(tmp);
	// G[from].push_back((edge){to,cap,cost,G[to].size()});
	// G[to].push_back((edge){from,0,-cost,G[from].size()-1});
}

//min-cost flow algorithm
int min_cost_flow(int s,int t,int f)
{
	int res=0;
	//using Bellman-Ford Algorithm to get the shortest path from s to t
	while(f>0)
	{
		fill(dist,dist+V,INF);
		dist[s]=0;
		bool update=true;
		while(update)
		{
			update=false;
			for(int v=0;v<V;++v)
			{
				if(dist[v]==INF)	continue;
				for(int i=0;i<G[v].size();++i)
				{
					edge &e=G[v][i];
					if(e.cap>0 && dist[e.to]>dist[v]+e.cost)
					{
						dist[e.to]=dist[v]+e.cost;
						prevv[e.to]=v;
						preve[e.to]=i;
						update=true;
					}
				}
			}
		}
		if(dist[t]==INF)
		{
			return -1;
		}

		//argument along the shortest path form s to t
		int d=f;
		for(int v=0;v!=s;v=prevv[v])
		{
			d=min(d,G[prevv[v]][preve[v]].cap);
		}
		f-=d;
		res+=d*dist[t];
		for(int v=t;v!=s;v=prevv[v])
		{
			edge &e=G[prevv[v]][preve[v]];
			e.cap-=d;
			G[v][e.rev].cap+=d;
		}
	}
	return res;
}

//parse the input
void parse(string line)
{
	char ch=line[0];
	//commments
	if('c'==ch)
		//continue;
		return;
	//problem description, parse the nodes num and the edges num
	else if('p'==ch)
	{
		sscanf(line.c_str(),"%*s %*s %d %d",&V,&edges);
		cout<<"nodes num: "<<V<<" arcs num: "<<edges<<endl;
	}
	//the source and the sink, parse to get the supply
	else if('n'==ch)
	{
		int tmp_s,tmp_supply;
		sscanf(line.c_str(),"%*s %d %d",&tmp_s,&tmp_supply);
		//the source node
		if(tmp_supply>0)
		{
			s=tmp_s-1;
			supply=tmp_supply;
			cout<<"s: "<<tmp_s<<" supply: "<<tmp_supply<<endl;
		}
		//the sink node
		else
		{
			t=tmp_s-1;
			cout<<"t: "<<tmp_s<<endl;
		}
	}
	//the edges
	else if('a'==ch)
	{
		int tmp_from,tmp_to,tmp_minflow,tmp_maxflow,tmp_cost;
		sscanf(line.c_str(),"%*s %d %d %d %d %d",&tmp_from,&tmp_to,&tmp_minflow,&tmp_maxflow,&tmp_cost);
		if(0==tmp_minflow)
		{
			cout<<"from: "<<tmp_from<<" to: "<<tmp_to<<" cap: "<<tmp_maxflow<<" cost: "<<tmp_cost<<endl;
			add_edge(tmp_from-1,tmp_to-1,tmp_maxflow,tmp_cost);
		}
		else
		{
			cout<<"Error:invalid input,the minflow of each edge must be 0!"<<endl;
		}
	}
	else
	{
		cout<<"Error:invalid input!"<<endl;
	}
}

int main()
{
	ifstream infile;
	infile.open("in.txt");
	if(infile.is_open())
	{
		string line;
		while(getline(infile,line)&&line!="")
		{
			parse(line);
		}
		cout<<min_cost_flow(s,t,supply)<<endl;
		s=0,t=0,supply=0;
		infile.close();
	}
	else
	{
		cout<<"fail to open the input file!"<<endl;
	}
	return 0;
}
