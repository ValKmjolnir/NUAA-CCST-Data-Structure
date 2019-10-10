#include<iostream>
#define LIST_INIT_SIZE 1

template<typename T>
class ADT_List
{
	private:
		T* elem;
		int length;
	public:
		ADT_List()
		{
			elem=new T[LIST_INIT_SIZE];
			length=0;
		}
		~ADT_List()
		{
			delete []elem;
		}
		void ClearList()
		{
			T null_type;
			for(int i=0;i<length;++i)
				elem[i]=null_type;
			length=0;
			return;
		}
		bool ListEmpty()
		{
			if(!length)
				return false;
			return true;
		}
		int ListLength()
		{
			return length;
		}
		T GetElem(const int i)
		{
			if(i>length || i==0)
			{
				T null_type;
				return null_type;
			}
			return elem[i-1];
		}
		int LocateElem(T e)
		{
			for(int i=0;i<length;++i)
				if(elem[i]==e)
					return i+1;
			return 0;
		}
		T PriorElem(T e)
		{
			for(int i=0;i<length;++i)
				if(elem[i]==e && i!=0)
					return elem[i-1];
			std::cout<<"Error when searching PriorElem"<<std::endl;
			T null_type;
			return null_type;
		}
		T NextElem(T e)
		{
			for(int i=0;i<length;++i)
				if(elem[i]==e && i<length-1)
					return elem[i+1];
			std::cout<<"Error when searching NextElem"<<std::endl;
			T null_type;
			return null_type;
		}
		void ListInsert(T e,int place)
		{
			++length;
			if(place<1 || place>length)
			{
				--length;
				return;
			}
			if(place-1==length && length>=LIST_INIT_SIZE)
			{
				T *temp=new T[length+1];
				int i=0;
				for(i=0;i<place-1;++i)
					temp[i]=elem[i];
				temp[i]=e;
				++i;
				for(;i<=length;++i)
					temp[i]=elem[i-1];
				delete []elem;
				elem=temp;
			}
			else
			{
				for(int i=length;i>=place;--i)
					elem[i]=elem[i-1];
				elem[place-1]=e;
			}
			return;
		}
		void ListDelete(int place)
		{
			if(place-1<0 || place-1>=length)
				return;
			for(int i=place-1;i<length-1;++i)
				elem[i]=elem[i+1];
			--length;
			return;
		}
		void ListTraverse()
		{
			for(int i=0;i<length;++i)
				std::cout<<elem[i]<<" ";
			std::cout<<std::endl;
			return;
		}
};

int main()
{
	ADT_List<int> m;
	m.ClearList();
	m.ListInsert(1,1);
	m.ListInsert(0x7fffffff,2);
	m.ListInsert(-23,1);
	m.ListTraverse();
	m.ListDelete(1);
	m.ListTraverse();
	m.ListInsert(-23,2);
	m.ListTraverse();
	std::cout<<m.PriorElem(-23)<<" "<<m.NextElem(-23)<<std::endl;
	m.PriorElem(1);
	m.NextElem(0x7fffffff);
	return 0;
}
