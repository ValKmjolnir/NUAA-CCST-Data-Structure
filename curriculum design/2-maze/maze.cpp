#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define maze_size 20

struct coordinate
{
	int x;
	int y;
	coordinate& operator=(const coordinate& p)
	{
		x=p.x;
		y=p.y;
		return *this;
	}
	bool operator!=(const coordinate& p)
	{
		return !(this->x==p.x && this->y==p.y);
	}
	bool operator==(const coordinate& p)
	{
		return this->x==p.x && this->y==p.y;
	}
};

coordinate route[maze_size][maze_size];
int maze[maze_size][maze_size];
bool visited[maze_size][maze_size];
std::string confirm;

void print_maze()
{
	for(int y=0;y<maze_size;++y)
	{
		for(int x=0;x<maze_size;++x)
		{
			switch(maze[x][y])
			{
				case 0:std::cout<<"  ";break;
				case 1:std::cout<<"¡ö";break;
				case 2:std::cout<<"* ";break;
				case 3:std::cout<<"O ";break;
				case 4:std::cout<<"X ";break;
			}
		}
		std::cout<<std::endl;
	}
	return;
}

void rand_init()
{
	std::srand(unsigned(std::time(NULL)));
	for(int y=0;y<maze_size;++y)
		for(int x=0;x<maze_size;++x)
		{
			maze[x][y]=(std::rand()%100>=30? 0:1);
			visited[x][y]=false;
		}
	for(int y=0;y<maze_size;++y)
		maze[0][y]=maze[maze_size-1][y]=1;
	for(int x=0;x<maze_size;++x)
		maze[x][0]=maze[x][maze_size-1]=1;
	return;
}

bool route_gen(int begin_x,int begin_y,int end_x,int end_y)
{
	coordinate begin_node;
	begin_node.x=begin_x;
	begin_node.y=begin_y;
	coordinate end_node;
	end_node.x=end_x;
	end_node.y=end_y;
	
	std::list<coordinate> bfs_queue;
	bfs_queue.push_back(begin_node);
	
	visited[begin_node.x][begin_node.y]=true;
	maze[end_node.x][end_node.y]=0;
	route[end_node.x][end_node.y].x=route[end_node.x][end_node.y].y=0;
	while(!bfs_queue.empty())
	{
		coordinate tmp=bfs_queue.front();
		bfs_queue.pop_front();
		if(tmp==end_node)
			break;
		if(tmp.x-1>=0 && !maze[tmp.x-1][tmp.y] && !visited[tmp.x-1][tmp.y])
		{
			coordinate t;
			t.x=tmp.x-1;
			t.y=tmp.y;
			bfs_queue.push_back(t);
			visited[t.x][t.y]=true;
			route[t.x][t.y]=tmp;
		}
		if(tmp.y-1>=0 && !maze[tmp.x][tmp.y-1] && !visited[tmp.x][tmp.y-1])
		{
			coordinate t;
			t.x=tmp.x;
			t.y=tmp.y-1;
			bfs_queue.push_back(t);
			visited[t.x][t.y]=true;
			route[t.x][t.y]=tmp;
		}
		if(tmp.x+1<maze_size && !maze[tmp.x+1][tmp.y] && !visited[tmp.x+1][tmp.y])
		{
			coordinate t;
			t.x=tmp.x+1;
			t.y=tmp.y;
			bfs_queue.push_back(t);
			visited[t.x][t.y]=true;
			route[t.x][t.y]=tmp;
		}
		if(tmp.y+1<maze_size && !maze[tmp.x][tmp.y+1] && !visited[tmp.x][tmp.y+1])
		{
			coordinate t;
			t.x=tmp.x;
			t.y=tmp.y+1;
			bfs_queue.push_back(t);
			visited[t.x][t.y]=true;
			route[t.x][t.y]=tmp;
		}
	}
	coordinate route_node=end_node;
	if(!route[end_node.x][end_node.y].x && !route[end_node.x][end_node.y].y)
		return false;
	while(route_node!=begin_node)
	{
		maze[route_node.x][route_node.y]=2;
		route_node=route[route_node.x][route_node.y];
	}
	maze[begin_node.x][begin_node.y]=2;
	return true;
}

int main()
{
	int x,y;
	int begin_x,begin_y;
	int end_x,end_y;
	while(1)
	{
		system("cls");
		rand_init();
		print_maze();
		while(1)
		{
			std::cout<<">> input the coordinate of starting point:"<<std::endl;
			std::cout<<">> input x: ";std::cin>>x;
			std::cout<<">> input y: ";std::cin>>y;
			if(0<=x && x<maze_size && 0<=y && y<maze_size && !maze[x][y])
				maze[x][y]=3;
			else
			{
				std::cout<<">> please input a place that has no block."<<std::endl;
				continue;
			}
			system("cls");
			print_maze();
			std::cout<<">> are you sure this is the starting point?(y/n)";std::cin>>confirm;
			if(confirm.length()>0 && confirm[0]=='y')
			{
				begin_x=x;
				begin_y=y;
				break;
			}
			else
			{
				maze[x][y]=0;
				system("cls");
				print_maze();
			}
		}
		while(1)
		{
			std::cout<<">> input the coordinate of end point:"<<std::endl;
			std::cout<<">> input x: ";std::cin>>x;
			std::cout<<">> input y: ";std::cin>>y;
			if(0<=x && x<maze_size && 0<=y && y<maze_size && !maze[x][y])
				maze[x][y]=4;
			else
			{
				std::cout<<">> please input a place that has no block."<<std::endl;
				continue;
			}
			system("cls");
			print_maze();
			std::cout<<">> are you sure this is the end point?(y/n)";std::cin>>confirm;
			if(confirm.length()>0 && confirm[0]=='y')
			{
				end_x=x;
				end_y=y;
				break;
			}
			else
			{
				maze[x][y]=0;
				system("cls");
				print_maze();
			}
		}
		if(route_gen(begin_x,begin_y,end_x,end_y))
		{
			system("cls");
			print_maze();
		}
		else
			std::cout<<">> cannot find a path from ("<<begin_x<<","<<begin_y<<") to ("<<end_x<<","<<end_y<<") ."<<std::endl;
		std::cout<<">> do you want to play again?(y/n)"<<std::endl;
		std::cin>>confirm;
		if(!(confirm.length()>0 && confirm[0]=='y'))
			break;
	}
	return 0;
}
