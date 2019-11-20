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
		char GetVex(int node)
		{
			if(node<node_num)
				return elem[node];
			else
				std::cout<<"error\n";
			return 0;
		}
		void PutVex(int node)
		{
			if(node<node_num)
				std::cin>>elem[node];
			else
				std::cout<<"error\n";
			return;
		}
		char* FirstAdjVex(int node)
		{
			if(node<node_num)
				for(int i=0;i<node_num;++i)
					if(map[node][i])
						return &elem[i];
			return NULL;
		}
		char* NextAdjVex(int node1,int node2)
		{
			if(node1<node_num && node2<node_num)
				for(int i=node2+1;i<node_num;++i)
					if(map[node1][i])
						return &elem[i];
			return NULL;
		}
		void InsertVex(char new_node_elem)
		{
			++node_num;
			char* t=new char[node_num];
			for(int i=0;i<node_num-1;++i)
				t[i]=elem[i];
			t[node_num-1]=new_node_elem;
			delete []elem;
			elem=t;
			delete []visited;
			visited=new bool[node_num];
			int** tm=new int*[node_num];
			for(int i=0;i<node_num;++i)
				tm[i]=new int[node_num];
			for(int i=0;i<node_num-1;++i)
				for(int j=0;j<node_num-1;++j)
					tm[i][j]=map[i][j];
			for(int i=0;i<node_num-1;++i)
				delete []map[i];
			delete []map;
			map=tm;
			return;
		}
		void DeleteVex(char node_elem)
		{
			int place=-1;
			for(int i=0;i<node_num;++i)
				if(elem[i]==node_elem)
				{
					place=i;
					break;
				}
			if(place<0)
				return;
			elem[place]=0;
			for(int i=0;i<node_num;++i)
				map[place][i]=map[i][place]=0;
			return;
		}
		void InsertArc(int node1,int node2)
		{
			if(node1<node_num && node2<node_num)
				map[node1][node2]=map[node2][node1]=1;
			return;
		}
		void DeleteArc(int node1,int node2)
		{
			if(node1<node_num && node2<node_num)
				map[node1][node2]=map[node2][node1]=0;
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
