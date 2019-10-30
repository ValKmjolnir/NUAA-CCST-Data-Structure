#include <iostream>
using namespace std;

class matrix
{
	private:
		int row;
		int col;
		int** elem;
	public:
		matrix(int _row,int _col)
		{
			row=_row;
			col=_col;
			elem=new int* [row];
			for(int i=0;i<row;++i)
				elem[i]=new int[col];
		}
		~matrix()
		{
			for(int i=0;i<row;++i)
				delete []elem[i];
			delete []elem;
		}
		void set_num()
		{
			for(int i=0;i<row;++i)
				for(int j=0;j<col;++j)
					cin>>elem[i][j];
			return;
		}
		void find_saddle_point()
		{
			for(int i=0;i<row;++i)
			{
				int place_col=0;
				int place_row=0;
				for(int j=0;j<col;++j)
					if(elem[i][j]<=elem[i][place_col])
						place_col=j;
				for(int j=0;j<row;++j)
					if(elem[j][place_col]<=elem[place_row][place_col])
						place_row=j;
				if(place_row==i)
					cout<<"(row: "<<place_row+1<<",col: "<<place_col+1<<", "<<elem[place_row][place_col]<<")"<<endl;
			}
			return;
		}
};
int main()
{
	int row,col;
	cin>>row>>col;
	matrix m(row,col);
	m.set_num();
	m.find_saddle_point();
	return 0;
}
