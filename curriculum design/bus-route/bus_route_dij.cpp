#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

class bus_station_lib
{
	private:
		std::list<std::string> stations;
		int station_number;
		int route_number;
	public:
		bus_station_lib()
		{
			station_number=0;
			route_number=0;
		}
		void add_station(std::string str)
		{
			for(std::list<std::string>::iterator i=stations.begin();i!=stations.end();++i)
				if(*i==str)
					return;
			++station_number;
			stations.push_back(str);
			return;
		}
		bool search_station(std::string str)
		{
			for(std::list<std::string>::iterator i=stations.begin();i!=stations.end();++i)
				if(*i==str)
					return true;
			return false;
		}
		void input_bus_route_file()
		{
			std::ifstream fin("nanjing_bus_route.txt");
			if(fin.fail())
			{
				std::cout<<"lack file \'nanjing_bus_route.txt\'."<<std::endl;
				fin.close();
				return;
			}
			std::string input_line;
			std::string tmp;
			while(!fin.eof())
			{
				getline(fin,input_line);
				input_line+=',';
				if(fin.eof())
					break; 
				++route_number;
				int space_number=0;
				tmp="";
				for(int i=0;i<input_line.length();++i)
				{
					if(input_line[i]==' ')
					{
						++space_number;
						continue;
					}
					if(space_number==3 && input_line[i]!=',')
						tmp+=input_line[i];
					if(space_number==3 && input_line[i]==',')
					{
						add_station(tmp);
						tmp="";
					}
				}
			}
			fin.close();
			return;
		}
		int get_station_number(){return station_number;}
		int get_route_number(){return route_number;}
		std::list<std::string>& get_station_name_list(){return stations;}
};
bus_station_lib lib;

struct bus_route
{
	int station_identifier;
	int bus_route_identifier;
};
struct bus_station
{
	std::string name;
	std::list<bus_route> next_stations;
};
struct bus_route_list
{
	int id;
	std::list<int> station_id;
};

class bus_route_map
{
	private:
		bus_station* station_info;
		int station_number;
		bool* visited;
		int *path;
		// for least station path
		bus_route_list* route_info;
		bool** route_map;
		int route_number;
		bool* route_used;
		int* route;
		int* route_identifier;
		// for least route change path
		
	public:
		bus_route_map()
		{
			station_number=0;
			station_info=NULL;
			route_info=NULL;
			visited=NULL;
			path=NULL;
			route_map=NULL;
			route_used=NULL;
			route=NULL;
			route_identifier=NULL;
			return;
		}
		~bus_route_map()
		{
			if(station_info)
				delete []station_info;
			if(route_info)
				delete []route_info;
			if(visited)
				delete []visited;
			if(path)
				delete []path;
			if(route_map)
			{
				for(int i=0;i<route_number;++i)
					delete []route_map[i];
				delete []route_map;
			}
			if(route_used)
				delete []route_used;
			if(route)
				delete []route;
			if(route_identifier)
				delete []route_identifier;
			return;
		}
		bool check_route_intersect(int route_id1,int route_id2)
		{
			for(std::list<int>::iterator i=route_info[route_id1].station_id.begin();i!=route_info[route_id1].station_id.end();++i)
				for(std::list<int>::iterator j=route_info[route_id2].station_id.begin();j!=route_info[route_id2].station_id.end();++j)
					if(*j==*i)
						return true;
			return false;
		}
		void create_station_info_lib()
		{
			station_number=lib.get_station_number();
			route_number=lib.get_route_number();
			station_info=new bus_station[station_number];
			route_info=new bus_route_list[route_number];
			visited=new bool[station_number];
			path=new int[station_number];
			route_used=new bool[route_number];
			route=new int[route_number];
			route_identifier=new int[route_number];
			int identifier=0;
			for(std::list<std::string>::iterator i=lib.get_station_name_list().begin();i!=lib.get_station_name_list().end();++i,++identifier)
				station_info[identifier].name=*i;
			for(int i=0;i<route_number;++i)
				route_info[i].id=i;
			route_map=new bool*[route_number];
			for(int i=0;i<route_number;++i)
				route_map[i]=new bool[route_number];
			return;
		}
		int get_bus_station_identifier(std::string str)
		{
			static int cnt=1;
			for(int i=0;i<station_number;++i)
				if(station_info[i].name==str)
					return i;
			return -1;
		}
		void generate_bus_station_map()
		{
			std::ifstream fin("nanjing_bus_route.txt");
			if(fin.fail())
			{
				std::cout<<"lack file \'nanjing_bus_route.txt\'."<<std::endl;
				fin.close();
				return;
			}
			std::string input_line;
			std::string tmp;
			int route_count=-1;
			std::list<std::string> route_stations;
			
			while(!fin.eof())
			{
				route_stations.clear();
				getline(fin,input_line);
				input_line+=',';
				if(fin.eof())
					break;
				++route_count;
				int space_number=0;
				tmp="";
				for(int i=0;i<input_line.length();++i)
				{
					if('0'<=input_line[i] && input_line[i]<='9')
						route_identifier[route_count]=route_identifier[route_count]*10+(int)(input_line[i]-'0');
					else
						break;
				}
				for(int i=0;i<input_line.length();++i)
				{
					if(input_line[i]==' ')
						++space_number;
					else if(space_number==3 && input_line[i]!=',')
						tmp+=input_line[i];
					else if(space_number==3 && input_line[i]==',')
					{
						route_stations.push_back(tmp);
						tmp="";
					}
				}
				
				for(std::list<std::string>::iterator i=route_stations.begin();i!=route_stations.end();++i)
				{
					std::list<std::string>::iterator next_iter=i;
					++next_iter;
					route_info[route_count].station_id.push_back(get_bus_station_identifier(*i));
					
					if(next_iter==route_stations.end())// if don't add this check,next_iter will point to (std::string) tmp
						continue;
					int this_station_identifier=get_bus_station_identifier(*i);
					int next_station_identifier=get_bus_station_identifier(*next_iter);
					
					if(this_station_identifier>=0 && next_station_identifier>=0)
					{
						bus_route t;
						t.bus_route_identifier=route_count;
						t.station_identifier=next_station_identifier;
						station_info[this_station_identifier].next_stations.push_back(t);
						t.station_identifier=this_station_identifier;
						station_info[next_station_identifier].next_stations.push_back(t);
					}
				}
			}
			fin.close();
			// generate route map
			for(int i=0;i<route_number;++i)
				for(int j=0;j<=i;++j)
						route_map[i][j]=route_map[j][i]=check_route_intersect(i,j);
			return;
		}
		void least_station_route(std::string start_station,std::string end_station)
		{
			int beg_id=get_bus_station_identifier(start_station);
			int end_id=get_bus_station_identifier(end_station);
			
			if(beg_id<0)
			{
				std::cout<<start_station<<" does not exist."<<std::endl;
				return;
			}
			if(end_id<0)
			{
				std::cout<<end_station<<" does not exist."<<std::endl;
				return;
			}
			std::list<std::string> generated_route;
			int min_station_number=0;
			for(int i=0;i<station_number;++i)
				visited[i]=false;
			for(int i=0;i<station_number;++i)
				path[i]=-1;
			std::list<int> que;
			// begin dijkstra with queue
			que.push_back(beg_id);
			visited[beg_id]=true;
			path[beg_id]=-1;
			while(!que.empty())
			{
				int tmp=que.front();
				// reach the end_station then quit the loop
				if(tmp==end_id)
					break;
				que.pop_front();
				for(std::list<bus_route>::iterator i=station_info[tmp].next_stations.begin();i!=station_info[tmp].next_stations.end();++i)
					if(!visited[i->station_identifier])
					{
						visited[i->station_identifier]=true;
						que.push_back(i->station_identifier);
						path[i->station_identifier]=tmp;
					}
			}
			int node=end_id;
			++min_station_number;
			// generate route
			generated_route.push_back(station_info[end_id].name);
			while(path[node]>=0)
			{
				++min_station_number;
				generated_route.push_front(station_info[path[node]].name);
				node=path[node];
			}
			
			std::cout<<std::endl<<min_station_number<<" stations: ";
			for(std::list<std::string>::iterator i=generated_route.begin();i!=generated_route.end();++i)
			{
				std::cout<<*i;
				++i;
				if(i!=generated_route.end())
					std::cout<<" -> ";
				--i;
			}
			std::cout<<std::endl;
			return;
		}
		bool check_station_in_route(int route_id,int station_id)
		{
			for(std::list<int>::iterator i=route_info[route_id].station_id.begin();i!=route_info[route_id].station_id.end();++i)
				if(station_id==*i)
					return true;
			return false;
		}
		void least_route_change(std::string start_station,std::string end_station)
		{
			int beg_id=get_bus_station_identifier(start_station);
			int end_id=get_bus_station_identifier(end_station);
			
			if(beg_id<0)
			{
				std::cout<<start_station<<" does not exist."<<std::endl;
				return;
			}
			if(end_id<0)
			{
				std::cout<<end_station<<" does not exist."<<std::endl;
				return;
			}
			std::list<int> generated_route;
			int min_route_change=5000;
			std::list<int> beg_station_routes;
			std::list<int> end_station_routes;
			for(int i=0;i<route_number;++i)
			{
				if(check_station_in_route(i,beg_id))
					beg_station_routes.push_back(i);
				if(check_station_in_route(i,end_id))
					end_station_routes.push_back(i);
			}
			
			for(std::list<int>::iterator i=beg_station_routes.begin();i!=beg_station_routes.end();++i)
			{
				std::list<int> que;
				std::list<int> cntque;
				que.push_back(*i);
				cntque.push_back(1);
				for(int j=0;j<route_number;++j)
					route_used[j]=false;
				route_used[*i]=true;
				route[*i]=-1;
				
				int found=-1;
				int temp_cnt;// store the number of route changes
				while(!que.empty())
				{
					int tmp=que.front();
					temp_cnt=cntque.front();
					que.pop_front();
					cntque.pop_front();
					// check if tmp route includes the end station
					for(std::list<int>::iterator j=end_station_routes.begin();j!=end_station_routes.end();++j)
						if(tmp==*j)
						{
							found=tmp;
							break;
						}
					if(found>=0)
						break;
					// add routes that have public station with tmp route to queue
					for(int j=0;j<route_number;++j)
						if(!route_used[j] && route_map[tmp][j])
						{
							route_used[j]=true;
							route[j]=tmp;
							que.push_back(j);
							cntque.push_back(temp_cnt+1);
						}
				}
				// update new least route change path
				int node=found;
				if(temp_cnt<min_route_change && node>=0)
				{
					min_route_change=temp_cnt;
					generated_route.clear();
					generated_route.push_front(node);
					while(route[node]>=0)
					{
						generated_route.push_front(route[node]);
						node=route[node];
					}
				}
			}
			std::cout<<std::endl<<min_route_change<<" routes: ";
			for(std::list<int>::iterator i=generated_route.begin();i!=generated_route.end();++i)
			{
				std::cout<<route_identifier[*i]<<" route";
				++i;
				if(i!=generated_route.end())
					std::cout<<" -> ";
				--i;
			}
			std::cout<<std::endl;
			return;
		}
		bool check_route(std::string start_station,std::string end_station)
		{
			int beg_id=get_bus_station_identifier(start_station);
			int end_id=get_bus_station_identifier(end_station);
			if(beg_id<0 || end_id<0)
			{
				std::cout<<start_station<<" or "<<end_station<<" don't exist."<<std::endl;
				return false;
			}
			std::list<int> que;
			for(int i=0;i<station_number;++i)
				visited[i]=false;
			que.push_back(beg_id);
			visited[beg_id]=true;
			while(!que.empty())
			{
				int tmp=que.front();
				if(tmp==end_id)
				{
					que.clear();
					return true;
				}
				que.pop_front();
				for(std::list<bus_route>::iterator i=station_info[tmp].next_stations.begin();i!=station_info[tmp].next_stations.end();++i)
					if(!visited[i->station_identifier])
					{
						visited[i->station_identifier]=true;
						que.push_back(i->station_identifier);
					}
			}
			return false;
		}
};
bus_route_map nanjing_bus_route;

std::string start_station;
std::string end_station;
int main()
{
	lib.input_bus_route_file();
	nanjing_bus_route.create_station_info_lib();
	nanjing_bus_route.generate_bus_station_map();
	while(1)
	{
		std::cout<<"start at: ";
		std::cin>>start_station;
		std::cout<<"end at: ";
		std::cin>>end_station;
		if(nanjing_bus_route.check_route(start_station,end_station))
		{
			std::cout<<"least stations route: ";
			nanjing_bus_route.least_station_route(start_station,end_station);
			std::cout<<"least route change: ";
			nanjing_bus_route.least_route_change(start_station,end_station);
		}
		else
			std::cout<<"cannot take a bus from "<<start_station<<" to "<<end_station<<std::endl;
	}
	return 0;
}
