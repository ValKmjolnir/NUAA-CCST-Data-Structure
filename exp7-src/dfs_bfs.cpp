#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

class graph
{
	private:
		int** map;
		char *elem;
		bool *visited;
		int node_num;
	public:
		graph()
		{
			int n;
			std::cin>>n;
			
			node_num=n;
			visited=new bool[n];
			elem=new char[n];
			for(int i=0;i<n;++i)
				std::cin>>elem[i];
			
			map=new int*[n];
			for(int i=0;i<n;++i)
			{
				map[i]=new int[n];
				for(int j=0;j<n;++j)
					map[i][j]=0;
			}
			return;
		}
		~graph()
		{
			if(map)
			{
				for(int i=0;i<node_num;++i)
					delete []map[i];
				delete []map;
				return;
			}
			if(elem)
				delete []elem;
			if(visited)
				delete []visited;
		}
		void CreateGraph()
		{
			int num;
			std::cin>>num;
			int node1,node2;
			for(int i=0;i<num;++i)
			{
				std::cin>>node1>>node2;
				if(node1<node_num && node2<node_num)
					map[node1][node2]=map[node2][node1]=1;
			}
			return;
		}
		void DestroyGraph()
		{
			for(int i=0;i<node_num;++i)
				for(int j=0;j<node_num;++j)
					map[i][j]=0;
			memset(visited,0,sizeof(visited));
			return;
		}
		void clear_visit()
		{
			memset(visited,0,sizeof(visited));
			return;
		}
		void DFSTraverse(int node)
		{
			if(elem[node])
			{
				std::cout<<elem[node]<<" ";
				visited[node]=true;
				for(int i=0;i<node_num;++i)
					if(map[node][i] && !visited[i])
						DFSTraverse(i);
			}
			return;
		}
		void BFSTraverse()
		{
			memset(visited,0,sizeof(bool));
			std::list<int> node_queue;
			for(int i=0;i<node_num;++i)
				if(elem[i])
				{
					node_queue.push_back(i);
					visited[i]=true;
				}
			while(!node_queue.empty())
			{
				for(int i=0;i<node_num;++i)
					if(map[node_queue.front()][i] && !visited[i])
					{
						node_queue.push_back(i);
						visited[i]=true;
					}
				std::cout<<elem[node_queue.front()]<<" ";
				node_queue.pop_front();
			}
			std::cout<<std::endl;
			return;
		}
};

int main()
{
	graph g;
	g.CreateGraph();
	g.BFSTraverse();
	g.clear_visit();
	g.DFSTraverse(0);
	return 0;
}
