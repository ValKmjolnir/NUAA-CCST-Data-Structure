#include <iostream>
using namespace std;

class cir_list
{
	private:
		int* elem;
		bool* used;
		int length;
	public:
		cir_list(const int n)
		{
			length=n;
			elem=new int[n];
			used=new bool[n];
			for(int i=0;i<length;++i)
			{
				elem[i]=i+1;
				used[i]=false;
			}
		}
		~cir_list()
		{
			delete []elem;
			delete []used;
		}
		void visit()
		{
			for(int i=0;i<length;++i)
				cout<<elem[i]<<' ';
			cout<<endl;
			return;
		}
		void run(const int m)
		{
			int cnt=0,out=0,ptr=0;
			while(out!=length)
			{
				if(ptr==length)
					ptr=0;
				if(!used[ptr])
					++cnt;
				if(cnt%m==0 && !used[ptr])
				{
					++out;
					used[ptr]=true;
					cout<<elem[ptr]<<' ';
				}
				++ptr;
			}
			cout<<endl;
			return;
		}
};

int main()
{
	int n,m;
	cin>>n>>m;
	cir_list lit(n);
	lit.visit();
	lit.run(m);
	return 0;
}
