#include <iostream>
using namespace std;
struct list_unit
{
	int elem;
	list_unit* next;
};
class List
{
	private:
		list_unit *head;
	public:
		List()
		{
			head=new list_unit;
			head->elem=0;
			head->next=NULL;
		}
		~List()
		{
			list_unit *temp;
			while(head->next)
			{
				temp=head;
				head=head->next;
			}
			delete head;
		}
		void visit()
		{
			list_unit *temp=head;
			while(temp->next)
			{
				temp=temp->next;
				cout<<temp->elem<<" ";
			}
			cout<<endl;
			return;
		}
		void add(int i)
		{
			list_unit *temp=head;
			while(temp->next)
				temp=temp->next;
			temp->next=new list_unit;
			temp=temp->next;
			temp->elem=i;
			temp->next=NULL;
		}
		void reverse()
		{
			if(!head->next || !head->next->next)
				return;
			list_unit *temp=head->next;
			list_unit *setnull=head->next;
			list_unit *next_node=temp->next;
			while(next_node)
			{
				temp=next_node;
				next_node=temp->next;
				
				temp->next=head->next;
				head->next=temp;
			}
			setnull->next=NULL;
			return;
		}
};
int main()
{
	List m;
	m.add(1);
	m.add(2);
	m.add(3);
	m.add(4);
	m.add(5);
	m.add(6);
	m.add(7);
	m.visit();
	m.reverse();
	m.visit();
	return 0;
}
