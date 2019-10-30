#include <iostream>
#include <algorithm>
#define MAXSIZE 100
using namespace std;
struct triple
{
	int col,row,elem;
};
bool cmp(triple a,triple b)
{
	if(a.row<b.row)
		return true;
	if(a.row==b.row && a.col<=b.col)
		return true;
	return false;
}
class sparse_matrix
{
	private:
		triple *list;
		int row;
		int col;
		int length;
		int size;
	public:
		sparse_matrix(int _col,int _row)
		{
			list=new triple[MAXSIZE];
			size=MAXSIZE;
			col=_col;
			row=_row;
			length=0;
			return;
		}
		~sparse_matrix()
		{
			delete []list;
			return;
		}
		void traverce()
		{
			for(int i=0;i<length;++i)
				cout<<"["<<list[i].row<<","<<list[i].col<<"]: "<<list[i].elem<<endl;
			cout<<endl;
			return;
		}
		void add(int _row,int _col,int _elem)
		{
			if(length+1>=size)
			{
				size+=MAXSIZE;
				triple *new_list=new triple[size];
				for(int i=0;i<length;++i)
				{
					new_list[i].col=list[i].col;
					new_list[i].row=list[i].row;
					new_list[i].elem=list[i].elem;
				}
				delete []list;
				list=new_list;
			}
			++length;
			list[length-1].col=_col;
			list[length-1].row=_row;
			list[length-1].elem=_elem;
			return;
		}
		void transpose_1()
		{
			for(int i=0;i<length;++i)
			{
				int t=list[i].row;
				list[i].row=list[i].col;
				list[i].col=t;
			}
			sort(list,list+length,cmp);
			return;
		}
		void transpose_2()
		{
			int *num,*cpot;
			triple *new_list;
			new_list=new triple[size];
			num=new int[col+1];
			cpot=new int[col+1];
			cpot[1]=1;
			for(int i=1;i<=col;++i)
				num[i]=0;
			for(int i=0;i<length;++i)
				++num[list[i].col];
			for(int i=2;i<=col;++i)
				cpot[i]=cpot[i-1]+num[i-1];
			int _col,q;
			for(int i=0;i<length;++i)
			{
				_col=list[i].col;
				q=cpot[_col];
				new_list[q-1].row=list[i].col;
				new_list[q-1].col=list[i].row;
				new_list[q-1].elem=list[i].elem;
				++cpot[_col];
			}
			delete []num;
			delete []cpot;
			delete []list;
			list=new_list;
			return;
		}
};
int main()
{
	sparse_matrix m(100,100);
	m.add(1,2,12);
	m.add(1,3,9);
	m.add(3,1,-3);
	m.add(3,6,14);
	m.add(4,3,24);
	m.add(5,2,18);
	m.add(6,1,15);
	m.add(6,4,-7);
	m.traverce();
	m.transpose_1();
	m.traverce();
	m.transpose_1();
	m.transpose_2();
	m.traverce();
	return 0;
}
