#include <iostream>
#include <cstring>
using namespace std;
int map[10][10];
bool cls[10][10];
int n,m;
void print()
{
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)
			cout<<map[i][j]<<" ";
		cout<<endl;
	}
	return;
}
void check()
{
	for(int i=0;i<n;++i)
		for(int j=0;j<m-2;++j)
		{
			if(map[i][j]==map[i][j+1] && map[i][j+1]==map[i][j+2])
				cls[i][j]=cls[i][j+1]=cls[i][j+2]=true;
		}
	for(int j=0;j<m;++j)
		for(int i=0;i<n-2;++i)
		{
			if(map[i][j]==map[i+1][j] && map[i+1][j]==map[i+2][j])
				cls[i][j]=cls[i+1][j]=cls[i+2][j]=true;
		}
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			if(cls[i][j])
				map[i][j]=0;
	return;
}
int main()
{
	memset(cls,0,sizeof(bool));
	cin>>n>>m;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			cin>>map[i][j];
	check();
	print();
	return 0;
}
