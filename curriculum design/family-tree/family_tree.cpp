#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

struct date
{
	int year;
	int month;
	int day;
};
struct person_info
{
	std::string name;
	date birthday;
	bool marriage;
	std::string address;
	bool alive;
	date death_date;
	std::list<person_info> children;
	person_info& operator=(const person_info& p)
	{
		name=p.name;
		birthday=p.birthday;
		marriage=p.marriage;
		address=p.address;
		alive=p.alive;
		death_date=p.death_date;
		children=p.children;
		return *this;
	}
};

class genealogy
{
	private:
		person_info root;
		void dfs_print(person_info& node,std::string space)
		{
			std::string str=space;
			for(int i=0;i<6;++i)
				str+=' ';
			std::cout<<str<<&node<<": "<<std::endl;
			std::cout<<str<<"[name    ] "<<node.name<<std::endl;
			std::cout<<str<<"[birth   ] "<<node.birthday.year<<"."<<node.birthday.month<<"."<<node.birthday.day<<std::endl;
			if(!node.alive)
				std::cout<<str<<"[death   ] "<<node.death_date.year<<"."<<node.death_date.month<<"."<<node.death_date.day<<std::endl;
			if(!node.children.empty())
				for(std::list<person_info>::iterator i=node.children.begin();i!=node.children.end();++i)
					dfs_print(*i,str+"|");
			return;
		}
		void dfs_initializing(std::ifstream& fin,person_info& node)
		{
			bool has_child;
			bool continue_input;
			while(!fin.eof())
			{
				person_info temp;
				fin>>temp.name;
				fin>>temp.birthday.year>>temp.birthday.month>>temp.birthday.day;
				fin>>temp.marriage;
				fin>>temp.address;
				fin>>temp.alive;
				if(!temp.alive)
					fin>>temp.death_date.year>>temp.death_date.month>>temp.death_date.day;
				fin>>has_child;
				if(fin.eof())
					break;
				if(has_child)
					dfs_initializing(fin,temp);
				node.children.push_back(temp);
				fin>>continue_input;
				if(!continue_input)
					break;
			}
			return;
		}
		void dfs_output(std::ofstream& fout,person_info& node)
		{
			fout<<node.name<<std::endl;
			fout<<node.birthday.year<<" "<<node.birthday.month<<" "<<node.birthday.day<<std::endl;
			fout<<node.marriage<<std::endl;
			fout<<node.address<<std::endl;
			fout<<node.alive<<std::endl;
			if(!node.alive)
				fout<<node.death_date.year<<" "<<node.death_date.month<<" "<<node.death_date.day<<std::endl;
			if(!node.children.empty())
			{
				fout<<1<<std::endl;
				for(std::list<person_info>::iterator i=node.children.begin();i!=node.children.end();++i)
				{
					dfs_output(fout,*i);
					++i;
					fout<<(i!=node.children.end())<<std::endl;
					--i;
				}
			}
			else
				fout<<0<<std::endl;
		}
	public:
		genealogy()
		{
			root.name="root";
			root.birthday.year=-1;
			root.birthday.month=0;
			root.birthday.day=0;
			root.address="null";
			root.marriage=false;
			root.alive=false;
			root.death_date=root.birthday;
			return;
		}
		void print_family_tree()
		{
			if(!root.children.empty())
				for(std::list<person_info>::iterator i=root.children.begin();i!=root.children.end();++i)
					dfs_print(*i,"|");
			return;
		}
		void initializing(std::string filename)
		{
			std::ifstream fin(filename);
			if(fin.fail())
			{
				std::cout<<"cannot find file \'"<<filename<<"\' ."<<std::endl;
				fin.close();
				return;
			}
			bool has_child;
			bool continue_input;
			while(!fin.eof())
			{
				fin>>has_child;
				if(fin.eof())
					break;
				if(has_child)
					dfs_initializing(fin,root);
				fin>>continue_input;
				if(!continue_input)
					break;
			}
			fin.close();
			if(root.children.empty())
				std::cout<<">> error occurred: root generation has 0 member."<<std::endl;
			return;
		}
		void file_output(std::string filename)
		{
			std::ofstream fout(filename);
			if(!root.children.empty())
			{
				fout<<1<<std::endl;
				for(std::list<person_info>::iterator i=root.children.begin();i!=root.children.end();++i)
				{
					dfs_output(fout,*i);
					++i;
					fout<<(i!=root.children.end())<<std::endl;
					--i;
				}
			}
			else
				fout<<0<<std::endl;
			fout.close();
			return;
		}
		void search_member_with_name(std::string name)
		{
			struct three_generation
			{
				person_info father;
				person_info self;
			};
			person_info null_person;
			
			null_person.name="null";
			std::cout<<"people named "<<name<<":"<<std::endl;
			std::list<three_generation> que;
			if(!root.children.empty())
				for(std::list<person_info>::iterator i=root.children.begin();i!=root.children.end();++i)
				{
					three_generation temp;
					temp.father=null_person;
					temp.self=*i;
					que.push_back(temp);
				}	
			while(!que.empty())
			{
				three_generation tmp=que.front();
				que.pop_front();
				if(tmp.self.name==name)
				{
					std::cout<<"[name    ] "<<tmp.self.name<<std::endl;
					std::cout<<"[birth   ] "<<tmp.self.birthday.year<<"."<<tmp.self.birthday.month<<"."<<tmp.self.birthday.day<<std::endl;
					std::cout<<"[marriage] "<<(tmp.self.marriage? "married":"unmarried")<<std::endl;
					std::cout<<"[address ] "<<tmp.self.address<<std::endl;
					if(!tmp.self.alive)
						std::cout<<"[death   ] "<<tmp.self.death_date.year<<"."<<tmp.self.death_date.month<<"."<<tmp.self.death_date.day<<std::endl;
					if(tmp.father.name!="null")
					{
						std::cout<<"father:"<<std::endl;
						std::cout<<"  [name    ] "<<tmp.father.name<<std::endl;
						std::cout<<"  [birth   ] "<<tmp.father.birthday.year<<"."<<tmp.father.birthday.month<<"."<<tmp.father.birthday.day<<std::endl;
						std::cout<<"  [marriage] "<<(tmp.father.marriage? "married":"unmarried")<<std::endl;
						std::cout<<"  [address ] "<<tmp.father.address<<std::endl;
						if(!tmp.father.alive)
							std::cout<<"  [death   ] "<<tmp.father.death_date.year<<"."<<tmp.father.death_date.month<<"."<<tmp.father.death_date.day<<std::endl;
					}
					if(!tmp.self.children.empty())
					{
						std::cout<<"children:"<<std::endl;
						for(std::list<person_info>::iterator i=tmp.self.children.begin();i!=tmp.self.children.end();++i)
						{
							std::cout<<"    [name    ] "<<i->name<<std::endl;
							std::cout<<"    [birth   ] "<<i->birthday.year<<"."<<i->birthday.month<<"."<<i->birthday.day<<std::endl;
							std::cout<<"    [marriage] "<<(i->marriage? "married":"unmarried")<<std::endl;
							std::cout<<"    [address ] "<<i->address<<std::endl;
							if(!i->alive)
								std::cout<<"    [death   ] "<<i->death_date.year<<"."<<i->death_date.month<<"."<<i->death_date.day<<std::endl;
						}
					}
				}
				if(!tmp.self.children.empty())
					for(std::list<person_info>::iterator i=tmp.self.children.begin();i!=tmp.self.children.end();++i)
					{
						three_generation temp;
						temp.father=tmp.self;
						temp.self=*i;
						que.push_back(temp);
					}
			}
			return;
		}
		void search_member_with_birthday(int month,int day)
		{
			std::cout<<"people born in "<<month<<"."<<day<<":"<<std::endl;
			std::list<person_info> que;
			if(!root.children.empty())
				for(std::list<person_info>::iterator i=root.children.begin();i!=root.children.end();++i)
					que.push_back(*i);
			while(!que.empty())
			{
				person_info tmp=que.front();
				que.pop_front();
				if(tmp.birthday.month==month && tmp.birthday.day==day)
				{
					std::cout<<"[name    ] "<<tmp.name<<std::endl;
					std::cout<<"[birth   ] "<<tmp.birthday.year<<"."<<tmp.birthday.month<<"."<<tmp.birthday.day<<std::endl;
					std::cout<<"[marriage] "<<(tmp.marriage? "married":"unmarried")<<std::endl;
					std::cout<<"[address ] "<<tmp.address<<std::endl;
					if(!tmp.alive)
						std::cout<<"[death   ] "<<tmp.death_date.year<<"."<<tmp.death_date.month<<"."<<tmp.death_date.day<<std::endl;
				}
				if(!tmp.children.empty())
					for(std::list<person_info>::iterator i=tmp.children.begin();i!=tmp.children.end();++i)
						que.push_back(*i);
			}
			return;
		}
		person_info* get_member_with_name(std::string name)
		{
			std::list<person_info*> result;
			std::list<person_info*> que;
			if(!root.children.empty())
				for(std::list<person_info>::iterator i=root.children.begin();i!=root.children.end();++i)
					que.push_back(&(*i));
			while(!que.empty())
			{
				person_info* tmp=que.front();
				que.pop_front();
				if(tmp->name==name)
					result.push_back(tmp);
				if(!tmp->children.empty())
					for(std::list<person_info>::iterator i=tmp->children.begin();i!=tmp->children.end();++i)
						que.push_back(&(*i));
			}
			if(result.empty())
			{
				std::cout<<">> cannot fine member named "<<name<<"."<<std::endl;
				return NULL;
			}
			std::cout<<">> people named "<<name<<":"<<std::endl;
			int cnt=1;
			for(std::list<person_info*>::iterator i=result.begin();i!=result.end();++i,++cnt)
				std::cout<<cnt<<": "<<(*i)<<": "<<(*i)->name<<" |"<<(*i)->birthday.year<<"."<<(*i)->birthday.month<<"."<<(*i)->birthday.day<<std::endl;
			int place=0;
			std::cout<<">> select one of them: ";std::cin>>place;
			cnt=1;
			for(std::list<person_info*>::iterator i=result.begin();i!=result.end();++i,++cnt)
				if(cnt==place)
					return *i;
			std::cout<<place<<"th people's information' does not exist."<<std::endl;
			return NULL;
		}
		void delete_member(person_info* node)
		{
			std::list<person_info*> que;
			if(!root.children.empty())
				for(std::list<person_info>::iterator i=root.children.begin();i!=root.children.end();++i)
				{
					if(&(*i)==node)
					{
						root.children.erase(i);
						return;
					}
					que.push_back(&(*i));
				}
			while(!que.empty())
			{
				person_info* tmp=que.front();
				que.pop_front();
				if(!tmp->children.empty())
					for(std::list<person_info>::iterator i=tmp->children.begin();i!=tmp->children.end();++i)
					{
						if(&(*i)==node)
						{
							tmp->children.erase(i);
							return;
						}
						que.push_back(&(*i));
					}
			}
			return;
		}
		bool check_descendant(person_info* node1,person_info* node2)
		{
			std::list<person_info*> que;
			if(!node1->children.empty())
				for(std::list<person_info>::iterator i=node1->children.begin();i!=node1->children.end();++i)
				{
					if(&(*i)==node2)
						return true;
					que.push_back(&(*i));
				}
			while(!que.empty())
			{
				person_info* tmp=que.front();
				que.pop_front();
				if(!tmp->children.empty())
					for(std::list<person_info>::iterator i=tmp->children.begin();i!=tmp->children.end();++i)
					{
						if(&(*i)==node2)
							return true;
						que.push_back(&(*i));
					}
			}
			return false;
		}
		bool check_brother(person_info* node1,person_info* node2)
		{
			bool found1=false;
			bool found2=false;
			std::list<person_info*> que;
			if(!root.children.empty())
			{
				for(std::list<person_info>::iterator i=root.children.begin();i!=root.children.end();++i)
				{
					if(node1==&(*i))
						found1=true;
					else if(node2==&(*i))
						found2=true;
					que.push_back(&(*i));
				}
				if(found1 && found2)
					return true;
				else if(found1 && !found2 || !found1 && found2)
					return false;
			}		
			while(!que.empty())
			{
				person_info* tmp=que.front();
				que.pop_front();
				if(!tmp->children.empty())
				{
					for(std::list<person_info>::iterator i=tmp->children.begin();i!=tmp->children.end();++i)
					{
						if(node1==&(*i))
							found1=true;
						else if(node2==&(*i))
							found2=true;
						que.push_back(&(*i));
					}
					if(found1 && found2)
						return true;
					else if(found1 && !found2 || !found1 && found2)
						return false;
				}
			}
			return false;
		}
		void print_generation(int n)
		{
			if(n<=0)
			{
				std::cout<<"wrong generation number."<<std::endl;
				return;
			}
			std::cout<<n<<" generation:"<<std::endl;
			std::list<person_info> que;
			std::list<int> cntque;
			if(!root.children.empty())
				for(std::list<person_info>::iterator i=root.children.begin();i!=root.children.end();++i)
				{
					cntque.push_back(1);
					que.push_back(*i);
				}
			while(!que.empty())
			{
				person_info tmp=que.front();
				int generation=cntque.front();
				que.pop_front();
				cntque.pop_front();
				if(generation==n)
				{
					std::cout<<"[name    ] "<<tmp.name<<std::endl;
					std::cout<<"[birth   ] "<<tmp.birthday.year<<"."<<tmp.birthday.month<<"."<<tmp.birthday.day<<std::endl;
					std::cout<<"[marriage] "<<(tmp.marriage? "married":"unmarried")<<std::endl;
					std::cout<<"[address ] "<<tmp.address<<std::endl;
					if(!tmp.alive)
						std::cout<<"[death   ] "<<tmp.death_date.year<<"."<<tmp.death_date.month<<"."<<tmp.death_date.day<<std::endl;
				}
				if(!tmp.children.empty())
					for(std::list<person_info>::iterator i=tmp.children.begin();i!=tmp.children.end();++i)
					{
						cntque.push_back(generation+1);
						que.push_back(*i);
					}
			}
			return;
		}
};

genealogy family_tree;
std::string command;
int main()
{
	family_tree.initializing("data.txt");
	std::cout<<">> initialzing complete.input \'help\' to get help."<<std::endl;
	while(1)
	{
		std::cout<<">> ";
		std::cin>>command;
		if(command=="help")
		{
			std::cout<<">> [help     ] get help."<<std::endl;
			std::cout<<">> [sch_birth] search members with birthday."<<std::endl;
			std::cout<<">> [sch_name ] search members with name."<<std::endl;
			std::cout<<">> [prt_gen  ] print members in a same generation."<<std::endl;
			std::cout<<">> [prt_all  ] print all members."<<std::endl;
			std::cout<<">> [edit_info] edit a member's information."<<std::endl;
			std::cout<<">> [add_child] add a child for a member."<<std::endl;
			std::cout<<">> [del_memb ] delete a member from the tree."<<std::endl;
			std::cout<<">> [chk_relat] check relationship between two people."<<std::endl;
			std::cout<<">> [file_out ] output family tree."<<std::endl;
			std::cout<<">> [exit     ] exit this programme."<<std::endl;
		}
		else if(command=="sch_birth")
		{
			int month,day;
			std::cout<<">> input month: ";std::cin>>month;
			std::cout<<">> input day: ";std::cin>>day;
			family_tree.search_member_with_birthday(month,day);
		}
		else if(command=="sch_name")
		{
			std::string name;
			std::cout<<">> input name: ";std::cin>>name;
			family_tree.search_member_with_name(name);
		}
		else if(command=="prt_all")
			family_tree.print_family_tree();
		else if(command=="prt_gen")
		{
			int n;
			std::cout<<">> input generation number: ";
			std::cin>>n;
			family_tree.print_generation(n);
		}
		else if(command=="edit_info")
		{
			std::string name;
			std::cout<<">> input name: ";std::cin>>name;
			person_info* node=family_tree.get_member_with_name(name);
			if(node)
			{
				char confirm;
				std::cout<<">> edit name?(y/n) ";std::cin>>confirm;
				if(confirm=='y')
				{
					std::cout<<">> name: ";
					std::cin>>node->name;
				}
				std::cout<<">> edit birthday?(y/n) ";std::cin>>confirm;
				if(confirm=='y')
				{
					std::cout<<">> year: ";std::cin>>node->birthday.year;
					std::cout<<">> month: ";std::cin>>node->birthday.month;
					std::cout<<">> day: ";std::cin>>node->birthday.day;
				}
				std::cout<<">> edit marriage?(y/n) ";std::cin>>confirm;
				if(confirm=='y')
				{
					std::cout<<">> married?(y/n) ";std::cin>>confirm;
					node->marriage=(confirm=='y');
				}
				std::cout<<">> edit address?(y/n) ";std::cin>>confirm;
				if(confirm=='y')
				{
					std::cout<<">> new address: ";
					std::cin>>node->address;
				}
				std::cout<<">> edit alive?(y/n) ";std::cin>>confirm;
				if(confirm=='y')
				{
					std::cout<<">> alive?(y/n) ";
					std::cin>>confirm;
					node->alive=(confirm=='y');
					if(!node->alive)
					{
						std::cout<<">> edit death date?(y/n) ";std::cin>>confirm;
						if(confirm=='y')
						{
							std::cout<<">> year: ";std::cin>>node->death_date.year;
							std::cout<<">> month: ";std::cin>>node->death_date.month;
							std::cout<<">> day: ";std::cin>>node->death_date.day;
						}
					}
				}
			}
			else
				std::cout<<">> returned NULL.stop."<<std::endl;
		}
		else if(command=="add_child")
		{
			std::string name;
			std::cout<<">> input name: ";std::cin>>name;
			person_info* node=family_tree.get_member_with_name(name);
			if(node)
			{
				char confirm;
				person_info temp;
				std::cout<<">> name: ";
				std::cin>>temp.name;
				std::cout<<">> birth year: ";std::cin>>temp.birthday.year;
				std::cout<<">> birth month: ";std::cin>>temp.birthday.month;
				std::cout<<">> birth day: ";std::cin>>temp.birthday.day;
				std::cout<<">> married?(y/n) ";std::cin>>confirm;
				temp.marriage=(confirm=='y');
				std::cout<<">> address: ";std::cin>>temp.address;
				std::cout<<">> alive?(y/n) ";std::cin>>confirm;
				temp.alive=(confirm=='y');
				if(!temp.alive)
				{
					std::cout<<">> death year: ";std::cin>>temp.death_date.year;
					std::cout<<">> death month: ";std::cin>>temp.death_date.month;
					std::cout<<">> death day: ";std::cin>>temp.death_date.day;
				}
				node->children.push_back(temp);
			}
			else
				std::cout<<">> returned NULL.stop."<<std::endl;
		}
		else if(command=="del_memb")
		{
			std::string name;
			std::cout<<">> input name: ";std::cin>>name;
			person_info* node=family_tree.get_member_with_name(name);
			if(node)
			{
				family_tree.delete_member(node);
				std::cout<<">> finished."<<std::endl;
			}
			else
				std::cout<<">> returned NULL.stop."<<std::endl;
		}
		else if(command=="chk_relat")
		{
			std::string name1,name2;
			std::cout<<">> input first person's 'name: ";std::cin>>name1;
			person_info* node1=family_tree.get_member_with_name(name1);
			std::cout<<">> input second person's name: ";std::cin>>name2;
			person_info* node2=family_tree.get_member_with_name(name2);
			if(node1 && node2)
			{
				bool checked=false;
				for(std::list<person_info>::iterator i=node1->children.begin();i!=node1->children.end();++i)
					if(&(*i)==node2)
					{
						checked=true;
						std::cout<<name1<<" is "<<name2<<"\'s father"<<std::endl;
						break;
					}
				for(std::list<person_info>::iterator i=node2->children.begin();i!=node2->children.end();++i)
					if(&(*i)==node1)
					{
						checked=true;
						std::cout<<name2<<" is "<<name1<<"\'s father"<<std::endl;
						break;
					}
				if(!checked)
				{
					if(node1==node2)// self
						std::cout<<name1<<" and "<<name2<<" is the same people."<<std::endl;
					else if(family_tree.check_brother(node1,node2))// brothers
						std::cout<<name1<<" and "<<name2<<" are brothers and(or) sisters."<<std::endl;
					else if(family_tree.check_descendant(node1,node2))// descendant
						std::cout<<name2<<" is the descendant of "<<name1<<std::endl;
					else if(family_tree.check_descendant(node2,node1))// descendant
						std::cout<<name1<<" is the descendant of "<<name2<<std::endl;
					else// complexed relationship
						std::cout<<name1<<" and "<<name2<<" have another types of relationships."<<std::endl;
				}
			}
			else
				std::cout<<">> returned NULL.stop."<<std::endl;
		}
		else if(command=="file_out")
		{
			family_tree.file_output("data.txt");
			std::cout<<">> finished."<<std::endl;
		}
		else if(command=="exit")
			break;
		else
			std::cout<<">> undefined command."<<std::endl;
	}
	return 0;
}
