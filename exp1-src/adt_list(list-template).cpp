#include<iostream>

template<typename T>
struct list_member
{
	T elem;
	list_member<T>* next;
};

template<typename T>
class ADT_List
{
	private:
		list_member<T>* head;
		int length;
	public:
		ADT_List()// InitList
		{
			head=new list_member<T>;
			head->next=NULL;
			length=0;
		}
		~ADT_List()// DestroyList
		{
			list_member<T>* temp;
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
			length=0;
			if(!head->next)
				return;
			list_member<T>* temp=head->next;
			list_member<T>* delete_node;
			head->next=NULL;
			while(temp->next)
			{
				delete_node=temp;
				temp=temp->next;
				delete delete_node;
			}
			delete temp;
			return;
		}
		bool ListEmpty()
		{
			if(head->next)
				return false;
			return true;
		}
		int ListLength()
		{
			return length;
		}
		T GetElem(const int i)
		{
			list_member<T>* temp=head;
			int cnt;
			while(temp->next)
			{
				temp=temp->next;
				++cnt;
				if(cnt==i)
					return *temp;
			}
			T null_type;
			return null_type;
		}
		int LocateElem(T e)
		{
			int cnt=0;
			list_member<T>* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				++cnt;
				if(temp->elem==e)
					return cnt;
			}
			return 0;
		}
		T PriorElem(T e)
		{
			list_member<T>* temp=head;
			list_member<T>* last_node;
			while(temp->next)
			{
				last_node=temp;
				temp=temp->next;
				if(temp->elem==e)
				{
					if(last_node!=head)
						return last_node->elem;
					break;
				}
			}
			std::cout<<"Error when searching PriorElem"<<std::endl;
			T null_type;
			return null_type;
		}
		T NextElem(T e)
		{
			list_member<T>* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				if(temp->elem==e)
				{
					if(temp->next)
						return temp->next->elem;
					break;
				}
			}
			std::cout<<"Error when searching NextElem"<<std::endl;
			T null_type;
			return null_type;
		}
		void ListInsert(T e,int place)
		{
			if(place<0 || place>length+1)
				return;
			int cnt=0;
			list_member<T>* temp=head;
			list_member<T>* t_node=new list_member<T>;
			t_node->elem=e;
			if(place==1)
			{
				t_node->next=temp->next;
				temp->next=t_node;
				++length;
				return;
			}
			while(temp->next)
			{
				temp=temp->next;
				++cnt;
				if(cnt==place-1)
				{
					++length;
					t_node->next=temp->next;
					temp->next=t_node;
					return;
				}
			}
			return;
		}
		void ListDelete(int place)
		{
			if(place>length)
				return;
			int cnt=0;
			list_member<T>* temp=head;
			list_member<T>* last_node;
			while(temp->next)
			{
				last_node=temp;
				temp=temp->next;
				++cnt;
				if(cnt==place)
				{
					last_node->next=temp->next;
					delete temp;
					--length;
					return;
				}
			}
			return;
		}
		void ListTraverse()
		{
			list_member<T>* temp=head;
			while(temp->next)
			{
				temp=temp->next;
				std::cout<<temp->elem<<" ";
			}
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
