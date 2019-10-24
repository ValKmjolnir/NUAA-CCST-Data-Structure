#include <iostream>
#include <cstring>
#define BLOCK_SIZE 128
using namespace std;
class stack
{
	private:
		int* elem;
		int stack_size;
		int length;
	public:
		stack()
		{
			elem=new int[BLOCK_SIZE];
			memset(elem,0,sizeof(int));
			stack_size=BLOCK_SIZE;
			length=0;
			return;
		}
		~stack()
		{
			delete []elem;
			return;
		}
		void ClearStack()
		{
			memset(elem,0,sizeof(int));
			length=0;
			return;
		}
		bool StackEmpty()
		{
			return !length;
		}
		int StackLength()
		{
			return length;
		}
		int GetTop()
		{
			return elem[length-1];
		}
		void Push(int e)
		{
			++length;
			if(length>BLOCK_SIZE)
			{
				int* temp=new int[BLOCK_SIZE+stack_size];
				stack_size+=BLOCK_SIZE;
				for(int i=0;i<length-1;++i)
					temp[i]=elem[i];
				delete []elem;
				elem=temp;
			}
			elem[length-1]=e;
			return;
		}
		int Pop()
		{
			int t=elem[length-1];
			elem[length-1]=0;
			--length;
			return t;
		}
		void StackTraverse()
		{
			for(int i=0;i<length;++i)
				cout<<elem[i]<<" ";
			cout<<endl;
			return;
		}
};
int main()
{
	stack m;
	for(int i=0;i<256;++i)
		m.Push(i);
	m.StackTraverse();
	cout<<m.Pop()<<endl;
	m.StackTraverse();
	return 0;
}
