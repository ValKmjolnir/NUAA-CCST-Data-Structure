#include <iostream>
#include <cmath>
#include <ctime>
#define LIST_INIT_SIZE 128
using namespace std;

void print(int i)
{
	cout<<i<<" ";
	return;
}

class list
{
	private:
		int *elem;
		int length;
		int list_size;
	public:
		list()// InitList
		{
			elem=new int[LIST_INIT_SIZE];
			length=0;
			list_size=LIST_INIT_SIZE;
		}
		~list()// DestroyList
		{
			delete []elem;
		}
		void ClearList()
		{
			delete []elem;
			elem=new int[LIST_INIT_SIZE];
			length=0;
			list_size=LIST_INIT_SIZE;
			return;
		}
		bool ListEmpty()
		{
			return length==0;
		}
		int ListLength()
		{
			return length;
		}
		void ListInsert(int i,int e)
		{
			if(i<1 || i>length+1)
				return;
			if(length+1>list_size)
			{
				++length;
				list_size+=LIST_INIT_SIZE;
				int* newelem=new int[list_size];
				for(int j=0;j<i-1;++j)
					newelem[j]=elem[j];
				newelem[i-1]=e;
				for(int j=i;j<length;++j)
					newelem[j]=elem[j-1];
				delete []elem;
				elem=newelem;
				newelem=NULL;
				return;
			}
			else
			{
				++length;
				for(int j=length-1;j>=i;--j)
					elem[j]=elem[j-1];
				elem[i-1]=e;
				return;
			}
			return;
		}
		int ListDelete(int i)
		{
			if(i<1 || i>length)
				return 0;
			int e;
			e=elem[i-1];
			--length;
			for(int j=i-1;j<length;++j)
				elem[j]=elem[j+1];
			return e;
		}
		void ListTraverse(void (*func)(int))
		{
			for(int i=0;i<length;++i)
				func(elem[i]);
			return;
		}
		void ListSort()
		{
			int mmin;
			int rec;
			for(int i=1;i<length;++i)
			{
				mmin=elem[i];
				rec=i;
				for(int j=i+1;j<length+1;++j)
					if(elem[j]<=mmin)
					{
						mmin=elem[j];
						rec=j;
					}
				if(rec!=i)
				{
					int t=elem[i];
					elem[i]=elem[rec];
					elem[rec]=t;
				}
			}
			return;
		}
};
int main()
{
	srand(unsigned(time(NULL)));
	list m;
	for(int i=0;i<160;++i)
		m.ListInsert(1,rand()%16);
	m.ListTraverse(print);
	cout<<endl;
	m.ListSort();
	m.ListTraverse(print);
	return 0;
}
