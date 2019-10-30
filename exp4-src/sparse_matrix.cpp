#include <iostream>
#define MAXSIZE 100
using namespace std;
struct triple
{
	int col,row,elem;
};
class sparse_matrix
{
	private:
		triple *list;
		int row;
		int col;
		int length;
	public:
		sparse_matrix()
		{
			list=new triple[MAXSIZE];
		}
};
int main()
{
	
	return 0;
}
