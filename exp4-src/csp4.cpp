#include <iostream>
#include <cstring>
using namespace std;
int a[5][20];
int num[20];
void place_search(int n)
{
	for(int i=0;i<5;++i)
		for(int j=0;j<20;++j)
		{
			if(num[j]>=n)
			{
				int k=0;
				while(a[k][j]) ++k;
				for(int m=k;m<k+n;++m)
				{
					a[m][j]=1;
					cout<<j*5+m+1<<" ";
				}
				cout<<endl;
				num[j]-=n;
				return;
			}
		}
	return;
}
int main()
{
	memset(a,0,sizeof(a));
	for(int i=0;i<20;++i)
		num[i]=5;
	int n,m;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		cin>>m;
		place_search(m);
	}
	return 0;
}
