#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

struct list_member
{
	int elem;
	list_member* next;
};

void print(list_member* t)
{
	cout<<t->elem<<" ";
	return;
}

class list
{
	private:
		list_member* head;
		int length;
	public:
		list()// InitList
		{
			head=new list_member;
			head->elem=0;
			head->next=NULL;
			length=0;
		}
		~list()// DestroyList
		{
			list_member* temp;
			while(head->next)
			{
				temp=head;
				head=head->next;
				delete temp;
			}
			delete head;
		}
		void ClearList()
		{
			list_member* temp=head->next;
			list_member* last=temp;
			if(!temp)
				return;
			length=0;
			while(temp->next)
			{
				temp=temp->next;
				delete last;
				last=temp;
			}
			delete temp;
			return;
		}
		bool ListEmpty()
		{
			return !head->next;
		}
		int ListLength()
		{
			return length;
		}
		void ListInsert(int i,int e)
		{
			if(i<1 || i>length+1)
				return;
			if(i==1)
			{
				list_member* new_node=new list_member;
				new_node->next=head->next;
				head->next=new_node;
				new_node->elem=e;
			}
			else if(i==length+1)
			{
				list_member* temp=head;
				list_member* new_node=new list_member;
				while(temp->next)
					temp=temp->next;
				temp->next=new_node;
				new_node->next=NULL;
				new_node->elem=e;
			}
			else
			{
				list_member* temp=head;
				list_member* new_node=new list_member;
				for(int j=0;j<i-1;++j)
					temp=temp->next;
				new_node->next=temp->next;
				temp->next=new_node;
				new_node->elem=e;
			}
			++length;
			return;
		}
		void ListTraverse(void (*func)(list_member*))
		{
			list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				func(temp);
			}
			return;
		}
		void ListSort()
		{
			list_member* fir_temp=head;
			list_member* sec_temp=head->next;
			list_member* fir_temp_last_node;
			list_member* sec_temp_last_node;
			list_member* rec_last_node;
			list_member* rec=NULL;
			int mmin;
			while(fir_temp->next)
			{
				fir_temp_last_node=fir_temp;
				fir_temp=fir_temp->next;
				if(!fir_temp->next)
					break;
				mmin=fir_temp->elem;
				sec_temp=fir_temp;
				rec=NULL;
				while(sec_temp->next)
				{
					sec_temp_last_node=sec_temp;
					sec_temp=sec_temp->next;
					if(sec_temp->elem<=mmin)
					{
						mmin=sec_temp->elem;
						rec_last_node=sec_temp_last_node;
						rec=sec_temp;
					}
				}
				if(rec!=NULL)
				{
					if(fir_temp->next!=rec)
					{
						list_member* fir_temp_next=fir_temp->next;
						fir_temp->next=rec->next;
						rec->next=fir_temp_next;
						rec_last_node->next=fir_temp;
						fir_temp_last_node->next=rec;
					}
					else
					{
						fir_temp->next=rec->next;
						rec->next=fir_temp;
						fir_temp_last_node->next=rec;
					}
					fir_temp=rec;
				}
			}
			return;
		}
		void ListMerge(list& p)
		{
			list_member* a_temp=head->next;
			list_member* a_last=head;
			list_member* b_temp=p.head->next;
			list_member* new_node=NULL;
			if(!b_temp)
				return;
			if(!a_temp)
			{
				a_temp=head;
				while(b_temp)
				{
					new_node=new list_member;
					new_node->next=NULL;
					new_node->elem=b_temp->elem;
					b_temp=b_temp->next;
					a_temp->next=new_node;
					a_temp=new_node;
				}
				return;
			}
			while(1)
			{
				while(b_temp->elem>a_temp->elem)
				{
					if(!a_temp->next)
						break;
					a_last=a_temp;
					a_temp=a_temp->next;
				}
				if(b_temp->elem<a_temp->elem)
				{
					new_node=new list_member;
					new_node->elem=b_temp->elem;
					new_node->next=a_last->next;
					a_last->next=new_node;
					b_temp=b_temp->next;
					if(!b_temp)
						break;
				}
				else if(!a_temp->next && b_temp->elem!=a_temp->elem)
				{
					a_temp->next=new list_member;
					a_temp=a_temp->next;
					a_temp->elem=b_temp->elem;
					a_temp->next=NULL;
					b_temp=b_temp->next;
					if(!b_temp)
						break;
				}
				else
				{
					b_temp=b_temp->next;
					if(!b_temp)
						break;
				}
			}
			return;
		}
};
int main()
{
	srand(unsigned(time(NULL)));
	list a,b;
	for(int i=0;i<16;++i)
	{
		a.ListInsert(1,i-1);
		b.ListInsert(1,i*2);
	}
	a.ListSort();
	b.ListSort();
	a.ListTraverse(print);
	cout<<endl;
	b.ListTraverse(print);
	cout<<endl;
	a.ListMerge(b);
	a.ListTraverse(print);
	return 0;
}
