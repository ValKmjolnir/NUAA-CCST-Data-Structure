#include <iostream>
using namespace std;
int a[10001]={0};
int main()
{
	int n,m,cnt=0,mmax=0;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		cin>>m;
		++a[m];
		if(m>mmax)
			mmax=m;
	}
	for(int i=0;i<mmax;++i)
		if(a[i]&&a[i+1])
			++cnt;
	cout<<cnt;
	return 0;
}
