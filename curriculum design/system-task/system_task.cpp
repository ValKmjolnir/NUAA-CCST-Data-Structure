#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <cstring>

int main_process_begin_time;

void print_time(int t)
{
	std::cout<<t/3600<<"h "<<(t/60)%3600<<"m "<<t%60<<"s";
	return;
}

class task
{
	private:
		char *name;
		int memory;
		int begin_time;
		int end_time;
		int time_length;
	public:
		task()
		{
			name=NULL;
			name=new char[128];
			memory=0;
		}
		task(const task& T)
		{
			begin_time=T.begin_time;
			end_time=T.end_time;
			name=NULL;
			name=new char[128];
			strcpy(name,T.name);
			memory=T.memory;
			return;
		}
		~task()
		{
			if(name)
				delete []name;
			return;
		}
		bool operator<(task& t)
		{
			return this->memory < t.memory;
		}
		bool operator>(task& t)
		{
			return this->memory > t.memory;
		}
		void set_task(char* str)
		{
			memory=0;
			// "system","4","services","0","24 K"
			char* b=str+1;
			char* p=str+1;
			while(*p)
			{
				if (*p=='\"')
				{
					*p=0;
					strcpy(name,b);
					// copy the task name to name[]
					break;
				}
				p++;
			}
			for (b=p+1;p[1]!='K';++p)
				if (*p=='\"')
					b=p;
			//b will be set to the memory token (xx K")
			for (char* c=b+1;c!=p;++c)
			{
				if (*c==',')
					continue;
				else
					memory=10*memory+*c-'0';
			}
			return;
		}
		char* get_name()
		{
			return name;
		}
		int get_begin_time()
		{
			return begin_time;
		}
		int get_end_time()
		{
			return end_time;
		}
		void set_begin_time(int t)
		{
			begin_time=t;
			return;
		}
		void set_end_time(int t)
		{
			end_time=t;
			return;
		}
		task& operator=(const task& T)
		{
			begin_time=T.begin_time;
			end_time=T.end_time;
			strcpy(name,T.name);
			memory=T.memory;
			return *this;
		}
		void print()
		{
			bool short_style=false;
			if(strlen(name)>20)
				short_style=true;
			if(short_style)
			{
				for(int i=0;i<17;++i)
					std::cout<<name[i];
				std::cout<<"... ";
			}
			else
			{
				int i;
				for(i=0;i<strlen(name);++i)
					std::cout<<name[i];
				for(;i<21;++i)
					std::cout<<' ';
			}
			std::cout<<" | start ";
			print_time(begin_time-main_process_begin_time);
			std::cout<<" last ";
			print_time(end_time-begin_time);
			std::cout<<"\t| "<<memory<<"k"<<std::endl;
			return;
		}
		bool check(char* str)
		{
			return !strcmp(name,str);
		}
};


struct bi_list_member
{
	task elem;
	bi_list_member* last;
	bi_list_member* next;
};
class bi_list
{
	private:
		int length;
		bi_list_member* head;
	public:
		bi_list()
		{
			length=0;
			head=new bi_list_member;
			head->last=NULL;
			head->next=NULL;
			return;
		}
		~bi_list()
		{
			bi_list_member* temp;
			while(head->next)
			{
				temp=head;
				head=head->next;
				delete temp;
			}
			delete head;
			return;
		}
		bi_list& operator=(const bi_list& t)
		{
			clear();
			length=t.length;
			bi_list_member* temp=head;
			bi_list_member* tnode=t.head;
			while(tnode->next)
			{
				tnode=tnode->next;
				temp->next=new bi_list_member;
				temp->next->last=temp;
				temp=temp->next;
				temp->next=NULL;
				temp->elem=tnode->elem;
			}
			return *this;
		}
		bool empty()
		{
			return !head->next;
		}
		void clear()
		{
			length=0;
			bi_list_member* temp=head->next;
			if(!temp)
				return;
			bi_list_member* del;
			while(temp->next)
			{
				del=temp;
				temp=temp->next;
				delete del;
			}
			delete temp;
			head->next=NULL;
			return;
		}
		void push_back(task var)
		{
			++length;
			bi_list_member* temp=head;
			while(temp->next)
				temp=temp->next;
			temp->next=new bi_list_member;
			temp->next->last=temp;
			temp=temp->next;
			temp->next=NULL;
			temp->elem=var;
			return;
		}
		task pop_back()
		{
			bi_list_member* temp=head;
			bi_list_member* last=head;
			while(temp->next)
			{
				last=temp;
				temp=temp->next;
			}
			last->next=NULL;
			task tmp=temp->elem;
			delete temp;
			return tmp;
		}
		void delete_node(char* name)
		{
			if(!head->next)
				return;
			bi_list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				if(temp->elem.check(name))
				{
					--length;
					temp->last->next=temp->next;
					if(temp->next)
						temp->next->last=temp->last;
					delete temp;
					break;
				}
			}
			return;
		}
		void sort()
		{
			if(!head->next)
				return;
			for(int i=0;i<length;++i)
				for(bi_list_member* j=head->next;j->next;j=j->next)
					if(j->elem<j->next->elem)
					{
						task tmp=j->elem;
						j->elem=j->next->elem;
						j->next->elem=tmp;
					}
			return;
		}
		void print_list()
		{
			bi_list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				temp->elem.print();
			}
			return;
		}
		bool search(char* name)
		{
			bi_list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				if(temp->elem.check(name))
					return true;
			}
			return false;
		}
		int get_elem_begin(char* name)
		{
			bi_list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				if(temp->elem.check(name))
					return temp->elem.get_begin_time();
			}
			return 0;
		}
};


struct list_member
{
	task elem;
	list_member* next;
};
class sg_list
{
	private:
		list_member* head;
	public:
		sg_list()
		{
			head=new list_member;
			head->next=NULL;
			return;
		}
		~sg_list()
		{
			list_member* temp;
			while(head->next)
			{
				temp=head;
				head=head->next;
				delete temp;
			}
			delete head;
			return;
		}
		void clear()
		{
			list_member* temp=head->next;
			if(!temp)
				return;
			list_member* del;
			while(temp->next)
			{
				del=temp;
				temp=temp->next;
				delete del;
			}
			delete temp;
			head->next=NULL;
			return;
		}
		void push_back(task var)
		{
			list_member* temp=head;
			while(temp->next)
				temp=temp->next;
			temp->next=new list_member;
			temp=temp->next;
			temp->next=NULL;
			temp->elem=var;
			return;
		}
		void delete_node(char* name)
		{
			if(!head->next)
				return;
			list_member* temp=head;
			list_member* last=head;
			while(temp->next)
			{
				last=temp;
				temp=temp->next;
				if(temp->elem.check(name))
				{
					last->next=temp->next;
					delete temp;
					break;
				}
			}
			return;
		}
		void print_list()
		{
			list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				temp->elem.print();
			}
			return;
		}
		bool search(char* name)
		{
			list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				if(temp->elem.check(name))
					return true;
			}
			if(temp->elem.check(name))
				return true;
			return false;
		}
};

bi_list in_running_process;
bi_list tmp_list;
sg_list exited_process;


int main()
{
	char buffer[128];
	char cmd[]="tasklist /FO CSV";
	
	main_process_begin_time=time(NULL);
	in_running_process.clear();
	tmp_list.clear();
	exited_process.clear();
	
	while(1)
	{
		tmp_list.clear();
		FILE* pipe=_popen(cmd,"r");
		if (!pipe)
			return -1;
		fgets(buffer,128,pipe);// get the first line
		while (!feof(pipe))
		{
			if(fgets(buffer,128,pipe))
			{
				task t;
				t.set_task(buffer);
				if(in_running_process.search(t.get_name()))
				{
					t.set_begin_time(in_running_process.get_elem_begin(t.get_name()));
					in_running_process.delete_node(t.get_name());
					t.set_end_time(time(NULL));
				}
				else if(exited_process.search(t.get_name()))
				{
					exited_process.delete_node(t.get_name());
					t.set_begin_time(time(NULL));
					t.set_end_time(time(NULL));
				}
				else
				{
					t.set_begin_time(time(NULL));
					t.set_end_time(time(NULL));
				}
				tmp_list.push_back(t);
			}
		}
		_pclose(pipe);

		while(!in_running_process.empty())
			exited_process.push_back(in_running_process.pop_back());
		in_running_process=tmp_list;
		in_running_process.sort();
		
		std::cout<<"running process: "<<std::endl;
		in_running_process.print_list();
		std::cout<<"exited process: "<<std::endl;
		exited_process.print_list();
		Sleep(1000);
	}
	return 0;
}
