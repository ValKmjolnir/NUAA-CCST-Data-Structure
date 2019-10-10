#include <iostream>
#include<math.h>
using namespace std;

struct list_member
{
	int elem;
	list_member* last;
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
			head->last=NULL;
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
		int GetElem(int i)
		{
			if(i<1 || i>length)
				return 0;
			list_member* temp=head;
			for(int j=0;j<i;++j)
				temp=temp->next;
			return temp->elem;
		}
		int LocateElem(int e)
		{
			list_member* temp=head;
			int cnt=0;
			while(temp->next)
			{
				++cnt;
				temp=temp->next;
				if(temp->elem==e)
					return cnt;
			}
			return -1;
		}
		int PriorElem(int e)
		{
			list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				if(temp->elem==e && temp->last!=head)
					return temp->last->elem;
			}
			return 0;
		}
		int NextElem(int e)
		{
			list_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				if(temp->elem==e && temp->next)
					return temp->next->elem;
			}
			return 0;
		}
		void ListInsert(int i,int e)
		{
			if(i<1 || i>length+1)
				return;
			if(i==1)
			{
				list_member* new_node=new list_member;
				new_node->last=head;
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
				new_node->last=temp;
				new_node->next=NULL;
				new_node->elem=e;
			}
			else
			{
				list_member* temp=head;
				list_member* new_node=new list_member;
				for(int j=0;j<i;++j)
					temp=temp->next;
				new_node->last=temp;
				new_node->next=temp->next;
				temp->next=new_node;
				new_node->elem=e;
			}
			++length;
			return;
		}
		int ListDelete(int i)
		{
			if(i<1 || i>length)
				return 0;
			list_member* temp=head;
			int e=0;
			for(int j=0;j<i;++j)
				temp=temp->next;
			if(temp)
			{
				e=temp->elem;
				temp->last->next=temp->next;
				if(temp->next)
					temp->next->last=temp->last;
				--length;
				delete temp;
			}
			return e;
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
};
int main()
{
	list m;
	cout<<m.ListEmpty()<<endl;
	m.ListInsert(1,1);
	m.ListInsert(1,2);
	m.ListInsert(1,3);
	m.ListTraverse(print);
	m.ListDelete(1);
	m.ListTraverse(print);
	cout<<m.PriorElem(2)<<" "<<m.NextElem(2)<<endl;
	m.ListTraverse(print);
	cout<<endl<<m.ListDelete(2)<<endl;
	m.ListTraverse(print);
	m.ClearList();
	m.ListTraverse(print);
	for(int i=0;i<16;++i)
	{
		m.ListInsert(1,i);
		cout<<endl;
		m.ListTraverse(print);
	}
	return 0;
}
