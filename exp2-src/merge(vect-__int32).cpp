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
			for(int i=0;i<length-1;++i)
			{
				mmin=elem[i];
				rec=i;
				for(int j=i;j<length;++j)
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
		void ListMerge(list& p)
		{
			int a=0,b=0;
			if(!p.length)
				return;
			if(!length)
			{
				for(int i=0;i<p.length;++i)
					this->ListInsert(i+1,p.elem[i]);
				return;
			}
			while(1)
			{
				while(p.elem[b]>elem[a])
				{
					if(a<=length)
						++a;
					else
						break;
				}
				if(p.elem[b]==elem[a])
				{
					++b;
					if(b>p.length)
						break;
					if(a<=length)
						++a;
				}
				else if(p.elem[b]>elem[a])
				{
					this->ListInsert(a,p.elem[b]);
					++b;
					if(b>p.length)
						break;
					if(a<=length)
						++a;
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
