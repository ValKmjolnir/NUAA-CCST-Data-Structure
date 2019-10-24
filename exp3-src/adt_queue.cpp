#include <iostream>
using namespace std;
struct que_member
{
	int elem;
	que_member* next;
};

class queue
{
	private:
		que_member* head;
		que_member* tail;
		int length;
	public:
		queue()
		{
			head=new que_member;
			head->next=NULL;
			tail=head;
			length=0;
			return;
		}
		~queue()
		{
			que_member* temp=head;
			while(head->next)
			{
				head=head->next;
				delete temp;
				temp=head;
			}
			delete temp;
			return;
		}
		void ClearQueue()
		{
			if(!head->next)
				return;
			que_member* temp=head->next;
			que_member* last=temp;
			while(temp->next)
			{
				temp=temp->next;
				delete last;
				last=temp;
			}
			delete last;
			return;
		}
		bool QueueEmpty()
		{
			return !length;
		}
		int QueueLength()
		{
			return length;
		}
		int GetHead()
		{
			if(head->next)
				return head->next->elem;
			return 0;
		}
		void EnQueue(const int n)
		{
			tail->next=new que_member;
			tail=tail->next;
			tail->next=NULL;
			tail->elem=n;
			++length;
			return;
		}
		int DeQueue()
		{
			if(head->next)
			{
				que_member* temp=head->next;
				head->next=head->next->next;
				int m=temp->elem;
				delete temp;
				return m;
			}
			return 0;
		}
		void QueueTraverse()
		{
			que_member* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				cout<<temp->elem<<" ";
			}
			cout<<endl;
			return;
		}
};

int main()
{
	queue q;
	q.ClearQueue();
	for(int i=0;i<16;++i)
		q.EnQueue(i);
	q.QueueTraverse();
	cout<<q.DeQueue()<<endl;
	q.QueueTraverse();
	return 0;
}
