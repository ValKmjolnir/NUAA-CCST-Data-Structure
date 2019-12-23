#include <iostream>
#include <list>
#define INF 65536

class Graph
{
	private:
		bool* visited;
		bool** arc;
		float** map;
		int node_number;
		int vex_number;
	public:
		Graph(){visited=NULL;arc=NULL;map=NULL;node_number=0;}
		~Graph()
		{
			if(visited)
				delete []visited;
			if(arc)
			{
				for(int i=0;i<node_number;++i)
					delete []arc[i];
				delete []arc;
			}
			if(map)
			{
				for(int i=0;i<node_number;++i)
					delete []map[i];
				delete []map;
			}
			return;
		}
		void create_graph(const int n,const int v)
		{
			node_number=n;
			vex_number=v;
			visited=new bool[node_number];
			arc=new bool*[node_number];
			map=new float*[node_number];
			for(int i=0;i<node_number;++i)
				arc[i]=new bool[node_number];
			for(int i=0;i<node_number;++i)
			{
				map[i]=new float[node_number];
				for(int j=0;j<node_number;++j)
					map[i][j]=INF;
			}
			return;
		}
		void add_vex(const int start_node,const int end_node,const float vex_len)
		{
			map[start_node][end_node]=map[end_node][start_node]=vex_len;
			return;
		}
		void prim()
		{
			for(int i=0;i<node_number;++i)
				visited[i]=false;
			for(int i=0;i<node_number;++i)
				for(int j=0;j<node_number;++j)
					arc[i][j]=false;
			visited[0]=true;
			// put first node into set V
			for(int t=0;t<node_number-1;++t)
			{
				float min_vex=INF;
				int min_vex_start,min_vex_end;
				for(int i=0;i<node_number;++i)
					for(int j=0;j<node_number;++j)
						if(map[i][j]!=INF && visited[i] && !visited[j] && map[i][j]<min_vex)
						{
							// get minimum vex from set U-V
							min_vex=map[i][j];
							min_vex_start=i;
							min_vex_end=j;
						}
				if(min_vex!=INF)
				{
					arc[min_vex_start][min_vex_end]=true;
					visited[min_vex_start]=visited[min_vex_end]=true;
					// add new node to set V
				}
			}
			std::cout<<"prim: "<<std::endl;
			float sum=0;
			for(int i=0;i<node_number;++i)
				for(int j=0;j<node_number;++j)
					if(arc[i][j])
					{
						std::cout<<i<<"->"<<j<<std::endl;
						sum+=map[i][j];
					}
			std::cout<<"sum: "<<sum<<std::endl;
			return;
		}
		bool check_loop(int node)
		{
			for(int i=0;i<node_number;++i)
				visited[i]=false;
			std::list<int> que;
			que.push_back(node);
			while(!que.empty())
			{
				int begin_node=que.front();
				// because of for(int i=0;i<node_number;++i)
				// every vex will be checked twice
				// so you will not miss any vex here
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
		void kruskal()
		{
			for(int i=0;i<node_number;++i)
				for(int j=0;j<node_number;++j)
					arc[i][j]=false;
			for(int t=0;t<node_number-1;++t)
			{
				float min_vex=INF;
				int min_vex_start,min_vex_end;
				for(int i=0;i<node_number;++i)
					for(int j=0;j<node_number;++j)
						if(map[i][j]!=INF && !arc[i][j] && map[i][j]<min_vex)
						{
							arc[i][j]=true;
							if(!check_loop(i))
							{
								min_vex=map[i][j];
								min_vex_start=i;
								min_vex_end=j;
							}
							arc[i][j]=false;
						}
				if(min_vex!=INF)
					arc[min_vex_start][min_vex_end]=true;
			}
			std::cout<<"kruskal: "<<std::endl;
			float sum=0;
			for(int i=0;i<node_number;++i)
				for(int j=0;j<node_number;++j)
					if(arc[i][j])
					{
						std::cout<<i<<"->"<<j<<std::endl;
						sum+=map[i][j];
					}
			std::cout<<"sum: "<<sum<<std::endl;
			return;
		}
};

Graph G;
int main()
{
	int node_num,vex_num;
	int start_node,end_node;
	float vex_len;
	std::cin>>node_num>>vex_num;
	G.create_graph(node_num,vex_num);
	for(int i=0;i<vex_num;++i)
	{
		std::cin>>start_node>>end_node>>vex_len;
		G.add_vex(start_node,end_node,vex_len);
	}
	G.prim();
	G.kruskal();
	return 0;
}
