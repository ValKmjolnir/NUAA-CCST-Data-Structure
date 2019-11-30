#include <iostream>
#include <cmath>
#include <list>
#define INF 1000000000

class graph
{
	private:
		int node_number;
		int** map;
		bool** arc;
	public:
		graph()
		{
			std::cin>>node_number;// n
			map=new int*[node_number];
			arc=new bool*[node_number];
			for(int i=0;i<node_number;++i)
			{
				map[i]=new int[node_number];
				arc[i]=new bool[node_number];
			}
			return;
		}
		~graph()
		{
			if(map)
			{
				for(int i=0;i<node_number;++i)
					if(map[i])
						delete []map[i];
				delete []map;
			}
			if(arc)
			{
				for(int i=0;i<node_number;++i)
					if(arc[i])
						delete []arc[i];
				delete []arc;
			}
			return;
		}
		void init_graph()
		{
			for(int i=0;i<node_number;++i)
				for(int j=0;j<node_number;++j)
					map[i][j]=INF;
			for(int i=0;i<node_number;++i)
				for(int j=0;j<node_number;++j)
					arc[i][j]=false;
			return;
		}
		void create_graph()
		{
			int arc_number;
			int begin_node,end_node,weight;
			std::cin>>arc_number;// m
			for(int i=0;i<arc_number;++i)
			{
				std::cin>>begin_node>>end_node>>weight;// ai bi ci
				map[begin_node-1][end_node-1]=weight;
				map[end_node-1][begin_node-1]=weight;
			}
			return;
		}
		bool loop(int node)
		{
			bool* visited;
			visited=new bool[node_number];
			for(int i=0;i<node_number;++i)
				visited[i]=false;
			std::list<int> que;
			que.push_back(node);
			while(!que.empty())
			{
				int begin_node=que.front();
				for(int i=0;i<node_number;++i)
				{
					if(arc[begin_node][i] && visited[i])
						return true;
					if(arc[begin_node][i] && !visited[i])
					{
						que.push_back(i);
						visited[i]=true;
					}
				}
				que.pop_front();
			}
			return false;
		}
		void min_cost_span_tree()
		{
			int sum=0;
			for(int t=0;t<node_number-1;++t)
			{
				int mmin=INF;
				for(int i=0;i<node_number;++i)
					for(int j=0;j<node_number;++j)
						if(map[i][j]!=INF && !arc[i][j] && map[i][j]<mmin)
						{
							arc[i][j]=true;
							if(loop(i))
								arc[i][j]=false;
							else
								mmin=map[i][j];
						}
				if(mmin!=INF)
					sum+=mmin;
			}
			std::cout<<sum;
			return;
		}
};


int main()
{
	graph G;
	G.init_graph();
	G.create_graph();
	G.min_cost_span_tree();
	return 0;
}
