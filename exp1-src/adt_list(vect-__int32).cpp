#include <iostream>
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
		int GetElem(int i)
		{
			if(i<1 || i>length)
				return 0;
			return elem[i];
		}
		int LocateElem(int e)
		{
			for(int i=0;i<length;++i)
				if(elem[i]==e)
					return i+1;
			return 0;
		}
		int PriorElem(int e)
		{
			for(int i=0;i<length;++i)
				if(elem[i]==e && i>0)
					return elem[i-1];
			return 0;
		}
		int NextElem(int e)
		{
			for(int i=0;i<length;++i)
				if(elem[i]==e && i<length-1)
					return elem[i+1];
			return 0;
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
	m.ListInsert(1,0x7fffffff);
	for(int i=0;i<16;++i)
	{
		m.ListInsert(2,i);
		cout<<endl;
		m.ListTraverse(print);
	}
	return 0;
}
