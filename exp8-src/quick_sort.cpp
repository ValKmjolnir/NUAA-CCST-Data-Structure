#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int num[1024];

void init()
{
	std::srand(unsigned(std::time(NULL)));
	for(int i=0;i<1024;++i)
		num[i]=rand()%1024;
	return;
}

void quick_sort(int begin,int end)
{	
	int i=begin;
	int j=end;
	if(i<j)
	{
		int mid=num[(begin+end)>>1];
		while(i<=j)
		{
			while(num[j]>mid)--j;
			while(num[i]<mid)++i;
			if(i<=j)
			{
				int t=num[i];
				num[i]=num[j];
				num[j]=t;
				++i;
				--j;
			}
		}
		quick_sort(begin,j);
		quick_sort(i,end);
	}
	return;
}

int main()
{
	init();
	quick_sort(0,1023);
	for(int i=0;i<1024;++i)
		std::cout<<num[i]<<" ";
	return 0;
}
