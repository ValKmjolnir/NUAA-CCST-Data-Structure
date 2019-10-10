#include <iostream>
#define LIST_INIT_SIZE 128
using namespace std;

void print(int i)
{
	cout<<i<<" ";
	return;
}

class List
{
	private:
		int *elem;
		int length;
		int list_size;
	public:
		List()// InitList
		{
			elem=new int[LIST_INIT_SIZE];
			length=0;
			list_size=LIST_INIT_SIZE;
		}
		~List()// DestroyList
		{
			delete []elem;
		}
		void add(int e)
		{
			if(length+1>list_size)
			{
				list_size+=LIST_INIT_SIZE;
				int* newelem=new int[list_size];
				for(int i=0;i<length;++i)
					newelem[i]=elem[i];
				newelem[length]=e;
				++length;
				delete []elem;
				elem=newelem;
				newelem=NULL;
				return;
			}
			else
			{
				elem[length]=e;
				++length;
				return;
			}
			return;
		}
		void visit()
		{
			for(int i=0;i<length;++i)
				cout<<elem[i]<<" ";
			cout<<endl;
			return;
		}
		void reverse()
		{
			for(int i=0;i<(length>>1);++i)
			{
				int t=elem[i];
				elem[i]=elem[length-i-1];
				elem[length-i-1]=t;
			}
			return;
		}
};
int main()
{
	List m;
	for(int i=0;i<256;++i)
		m.add(i);
	m.visit();
	m.reverse();
	m.visit();
	return 0;
}
