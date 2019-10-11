#include <iostream>
using namespace std;


struct list_mem
{
	int elem;
	bool used;
	list_mem* next;
};
class cir_list
{
	private:
		list_mem* head;
		int length;
	public:
		cir_list(const int n)
		{
			length=n;
			head=new list_mem;
			head->next=NULL;
			list_mem* temp=head;
			temp->next=new list_mem;
			for(int i=1;i<=n;++i)
			{
				temp=temp->next;
				temp->elem=i;
				temp->used=false;
				temp->next=new list_mem;
			}
			delete temp->next;
			temp->next=NULL;
		}
		~cir_list()
		{
			list_mem* temp;
			while(head->next)
			{
				temp=head;
				head=head->next;
				delete temp;
			}
			delete head;
		}
		void visit()
		{
			list_mem* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				cout<<temp->elem<<' ';
			}
			cout<<endl;
			return;
		}
		void run(const int m)
		{
			int cnt=0;
			int out=0;
			list_mem* temp=head;
			while(out!=length)
			{
				temp=temp->next;
				if(!temp)
					temp=head->next;
				if(!temp->used)
					++cnt;
				if(cnt%m==0 && !temp->used)
				{
					++out;
					temp->used=true;
					cout<<temp->elem<<' ';
				}
			}
			cout<<endl;
			return;
		}
};

int main()
{
	int n,m;
	cin>>n>>m;
	cir_list lit(n);
	lit.visit();
	lit.run(m);
	return 0;
}
