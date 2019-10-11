#include <iostream>
using namespace std;
enum in_run_type
{
	road=0,
	red,
	yellow,
	green
};
int main()
{
	int r,y,g,n;
	cin>>r>>y>>g>>n;
	int type,time,time_cnt=0;
	for(int i=0;i<n;++i)
	{
		cin>>type>>time;
		switch(type)
		{
			case road:
			case red:time_cnt+=time;break;
			case yellow:time_cnt+=time+r;break;
			case green:break;
		}
	}
	cout<<time_cnt;
	return 0;
} 
