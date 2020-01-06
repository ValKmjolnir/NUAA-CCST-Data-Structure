#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <list>
#define map_length 22
#define map_width 12

const std::string curve_example=" @#$%&*+?OB";
// curve_example[0] is space.
// curve_example[1~10] is the curve in use.
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

class link_up_map
{
	private:
		coordinate total_begin_node;
		int map[map_length][map_width];
		bool visited[map_length][map_width];
		coordinate route[map_length][map_width];
		bool dfs(int begin_x,int begin_y,int end_x,int end_y)
		{
			coordinate begin_node,end_node;
			begin_node.x=begin_x;begin_node.y=begin_y;
			end_node.x=end_x;end_node.y=end_y;
			if(begin_node==end_node)
			{
				int change_cnt=0;
				bool x_change=false;
				bool y_change=false;
				coordinate route_node=end_node;
				while(1)
				{
					if(route_node.x==route[route_node.x][route_node.y].x && !x_change) {++change_cnt;x_change=true;y_change=false;}
					else if(route_node.y==route[route_node.x][route_node.y].y && !y_change) {++change_cnt;x_change=false;y_change=true;}
					if(route_node==total_begin_node)
						break;
					route_node=route[route_node.x][route_node.y];
				}
				if(change_cnt<=3)
					return true;
				else
					return false;
			}
			if(begin_x-1>=0 && !map[begin_x-1][begin_y] && !visited[begin_x-1][begin_y])
			{
				visited[begin_x-1][begin_y]=true;
				route[begin_x-1][begin_y]=begin_node;
				if(dfs(begin_x-1,begin_y,end_x,end_y))
					return true;
				visited[begin_x-1][begin_y]=false;
			}
			if(begin_y-1>=0 && !map[begin_x][begin_y-1] && !visited[begin_x][begin_y-1])
			{
				visited[begin_x][begin_y-1]=true;
				route[begin_x][begin_y-1]=begin_node;
				if(dfs(begin_x,begin_y-1,end_x,end_y))
					return true;
				visited[begin_x][begin_y-1]=false;
			}
			if(begin_x+1<map_length && !map[begin_x+1][begin_y] && !visited[begin_x+1][begin_y])
			{
				visited[begin_x+1][begin_y]=true;
				route[begin_x+1][begin_y]=begin_node;
				if(dfs(begin_x+1,begin_y,end_x,end_y))
					return true;
				visited[begin_x+1][begin_y]=false;
			}
			if(begin_y+1<map_width && !map[begin_x][begin_y+1] && !visited[begin_x][begin_y+1])
			{
				visited[begin_x][begin_y+1]=true;
				route[begin_x][begin_y+1]=begin_node;
				if(dfs(begin_x,begin_y+1,end_x,end_y))
					return true;
				visited[begin_x][begin_y+1]=false;
			}
			return false;
		}
	public:
		link_up_map()
		{
			std::memset(map,0,sizeof(map));
			return;
		}
		void print_map()
		{
			system("cls");
			std::cout<<"   ";
			for(int i=1;i<map_length-1;++i)
			{
				if(i<10)
					std::cout<<i<<"  ";
				else
					std::cout<<i<<" ";
			}
			std::cout<<std::endl;
			for(int y=1;y<map_width-1;++y)
			{
				if(y<10)
					std::cout<<y<<"  ";
				else
					std::cout<<y<<" ";
				for(int x=1;x<map_length-1;++x)
					std::cout<<curve_example[map[x][y]]<<"  ";
				std::cout<<std::endl;
			}
			return;
		}
		void rand_init()
		{
			//std::srand(unsigned(std::time(NULL)));
			int char_cnt[10];
			bool checked[10];
			std::memset(map,0,sizeof(map));
			std::memset(char_cnt,0,sizeof(char_cnt));
			std::memset(checked,0,sizeof(checked));
			
			for(int y=1;y<map_width-1;++y)
				for(int x=1;x<map_length-1;++x)
				{
					map[x][y]=1+std::rand()%10;// 1~10
					++char_cnt[map[x][y]-1];
				}
			for(int i=0;i<10;++i)
				checked[i]=char_cnt[i]&1;
			for(int i=0;i<10;++i)
				for(int j=i+1;j<10;++j)
				{
					if(checked[i] && checked[j])
					{
						for(int y=1;y<map_width-1;++y)
							for(int x=1;x<map_length-1;++x)
								if(map[x][y]==i+1)
								{
									map[x][y]=j+1;
									break;
								}
					}
				}
			return;
		}
		bool check_same(int begin_x,int begin_y,int end_x,int end_y)
		{
			return map[begin_x][begin_y]==map[end_x][end_y];
		}
		bool check_null(int begin_x,int begin_y,int end_x,int end_y)
		{
			return !map[begin_x][begin_y] || !map[end_x][end_y];
		}
		bool check_clear()
		{
			for(int y=0;y<map_width;++y)
				for(int x=0;x<map_length;++x)
					if(map[x][y])
						return false;
			return true;
		}
		bool route_gen(int begin_x,int begin_y,int end_x,int end_y)
		{
			std::memset(visited,0,sizeof(visited));
			int record=map[end_x][end_y];
			coordinate begin_node,end_node;
			begin_node.x=begin_x;begin_node.y=begin_y;
			end_node.x=end_x;end_node.y=end_y;
			
			total_begin_node=begin_node;
			visited[begin_node.x][begin_node.y]=true;
			map[end_node.x][end_node.y]=0;

			if(begin_x-1>=0 && !map[begin_x-1][begin_y] && !visited[begin_x-1][begin_y])
			{
				visited[begin_x-1][begin_y]=true;
				route[begin_x-1][begin_y]=begin_node;
				if(dfs(begin_x-1,begin_y,end_x,end_y))
				{
					map[begin_x][begin_y]=map[end_x][end_y]=0;
					return true;
				}
				visited[begin_x-1][begin_y]=false;
			}
			if(begin_y-1>=0 && !map[begin_x][begin_y-1] && !visited[begin_x][begin_y-1])
			{
				visited[begin_x][begin_y-1]=true;
				route[begin_x][begin_y-1]=begin_node;
				if(dfs(begin_x,begin_y-1,end_x,end_y))
				{
					map[begin_x][begin_y]=map[end_x][end_y]=0;
					return true;
				}
				visited[begin_x][begin_y-1]=false;
			}
			if(begin_x+1<map_length && !map[begin_x+1][begin_y] && !visited[begin_x+1][begin_y])
			{
				visited[begin_x+1][begin_y]=true;
				route[begin_x+1][begin_y]=begin_node;
				if(dfs(begin_x+1,begin_y,end_x,end_y))
				{
					map[begin_x][begin_y]=map[end_x][end_y]=0;
					return true;
				}
				visited[begin_x+1][begin_y]=false;
			}
			if(begin_y+1<map_width && !map[begin_x][begin_y+1] && !visited[begin_x][begin_y+1])
			{
				visited[begin_x][begin_y+1]=true;
				route[begin_x][begin_y+1]=begin_node;
				if(dfs(begin_x,begin_y+1,end_x,end_y))
				{
					map[begin_x][begin_y]=map[end_x][end_y]=0;
					return true;
				}
				visited[begin_x][begin_y+1]=false;
			}
			map[end_x][end_y]=record;
			return false;
		}
};
link_up_map game_map;
std::string confirm;
int main()
{
	int begin_x,begin_y;
	int end_x,end_y;
	while(1)
	{
		game_map.rand_init();
		game_map.print_map();
		while(1)
		{
			std::cout<<">> input begin coordinate: ";
			std::cin>>begin_x>>begin_y;
			std::cout<<">> input end coordinate: ";
			std::cin>>end_x>>end_y;
			if(1<=begin_x && begin_x<map_length-1 && 1<=end_x && end_x<map_length-1 && 1<=begin_y && begin_y<map_width-1 && 1<=end_y && end_y<map_width-1)
			{
				if(game_map.check_same(begin_x,begin_y,end_x,end_y) && !game_map.check_null(begin_x,begin_y,end_x,end_y))
				{
					if(!game_map.route_gen(begin_x,begin_y,end_x,end_y))
					{
						game_map.print_map();
						std::cout<<">> too much lines to link these two."<<std::endl;
					}
					else
						game_map.print_map();
				}
				else if(game_map.check_null(begin_x,begin_y,end_x,end_y))
				{
					game_map.print_map();
					std::cout<<">> null place"<<std::endl;
				}
				else
					std::cout<<">> they are not the same."<<std::endl;
			}
			else
				std::cout<<">> incorrect begin/end coordinate."<<std::endl;
			if(game_map.check_clear())
				break;
		}
		std::cout<<">> do you want to play again?(y/n) ";
		std::cin>>confirm;
		if(!(confirm.length() && confirm[0]=='y'))
			break;
	}
	return 0;
}
