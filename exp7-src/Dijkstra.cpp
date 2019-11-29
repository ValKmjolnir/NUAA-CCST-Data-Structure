#include <iostream>
#include <cmath>
#define INF 1000000000

class graph
{
	private:
		int node_number;
		int** map;
	public:
		graph()
		{
			std::cout<<"input the number of nodes: ";
			std::cin>>node_number;
			map=new int*[node_number];
			for(int i=0;i<node_number;++i)
				map[i]=new int[node_number];
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
			return;
		}
		int get_num(){return node_number;}
		void init_graph()
		{
			for(int i=0;i<node_number;++i)
				for(int j=0;j<node_number;++j)
					map[i][j]=INF;
			return;
		}
		void create_graph()
		{
			int arc_number;
			int begin_node,end_node,weight;
			std::cout<<"number of arcs: ";
			std::cin>>arc_number;
			for(int i=0;i<arc_number;++i)
			{
				std::cin>>begin_node>>end_node>>weight;
				map[begin_node][end_node]=weight;
			}
			return;
		}
		void dijkstra(int begin_node,int end_node)
		{
			int* d;
			bool* final;
			d=new int[node_number];
			final=new bool[node_number];
			for(int i=0;i<node_number;++i)
			{
				d[i]=map[begin_node][i];
				final[i]=false;
			}
			d[begin_node]=0;
			final[begin_node]=true;
			
			for(int i=0;i<node_number;++i)
			{
				int v;
				int mmin=INF;
				for(int j=0;j<node_number;++j)
					if(!final[j])
						if(d[j]<mmin)
						{
							v=j;
							mmin=d[j];
						}
				final[v]=true;
				for(int j=0;j<node_number;++j)
					if(!final[j] && (mmin+map[v][j]<d[j]))
						d[j]=mmin+map[v][j];
			}
			std::cout<<begin_node<<" to "<<end_node<<"\'s shortest path length is "<<(d[end_node]==INF? -1:d[end_node])<<std::endl;
			return;
		}
		void floyd(int begin_node)
		{
			int* d;
			d=new int[node_number];
			for(int i=0;i<node_number;++i)
				d[i]=map[begin_node][i];
			d[begin_node]=0;
			for(int n=0;n<node_number;++n)
				for(int i=0;i<node_number;++i)
				{
					if(d[i]!=INF)// begin_node has path to node i
						for(int j=0;j<node_number;++j)
							if(map[i][j]!=INF)// node i has path to node j
								d[j]=std::min(d[j],map[i][j]+d[i]);// length of path between begin_node and j
				}
			// O(n^3)
			for(int end_node=0;end_node<node_number;++end_node)
				std::cout<<begin_node<<" to "<<end_node<<"\'s shortest path length is "<<(d[end_node]==INF? -1:d[end_node])<<std::endl;
			delete []d;
			return;
		}
};


int main()
{
	graph G;
	G.init_graph();
	G.create_graph();
	for(int i=0;i<G.get_num();++i)
		for(int j=0;j<G.get_num();++j)
			G.dijkstra(i,j);
	for(int i=0;i<G.get_num();++i)
		G.floyd(i);
	return 0;
}
