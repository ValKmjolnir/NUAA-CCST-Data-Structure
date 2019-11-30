#include <iostream>
#include <cstdlib>
#include <ctime>

int num[100];

void init()
{
	std::srand(unsigned(std::time(NULL)));
	for(int i=0;i<100;++i)
		num[i]=std::rand()%200;
	return;
}

void bubble()
{
	for(int i=0;i<100;++i)
		for(int j=0;j<99;++j)
			if(num[j]>num[j+1])
			{
				int t=num[j];
				num[j]=num[j+1];
				num[j+1]=t;
			}
	for(int i=0;i<100;++i)
		std::cout<<num[i]<<" ";
	std::cout<<std::endl;
	return;
}

void select()
{
	for(int i=0;i<99;++i)
	{
		int mmin=num[i];
		int node=i;
		for(int j=i+1;j<100;++j)
			if(num[j]<mmin)
			{
				node=j;
				mmin=num[j];
			}
		if(node!=i)
		{
			int t=num[i];
			num[i]=num[node];
			num[node]=t;
		}
	}
	for(int i=0;i<100;++i)
		std::cout<<num[i]<<" ";
	std::cout<<std::endl;
	return;
}

void insert()
{
    int temp;
    for(int i=1;i<100;++i)
    {
        temp=num[i];
        int j;
        for(j=i;j>0 && num[j-1]>temp;--j)
            num[j]=num[j-1];
        num[j]=temp;
    }
	for(int i=0;i<100;++i)
		std::cout<<num[i]<<" ";
	std::cout<<std::endl;
	return;
}

void merge_work(int i,int j)
{
	if(i+1==j)
	{
		if(num[i]>num[j])
		{
			int t=num[i];
			num[i]=num[j];
			num[j]=t;
		}
		return;
	}
	if(i==j)
		return;
	else
	{
		merge_work(i,(i+j)>>1);
		merge_work(1+(i+j)>>1,j);
		for(int k=i;k<j;++k)
			for(int l=i;l<j-1;++l)
				if(num[l]>num[l+1])
				{
					int t=num[l];
					num[l]=num[l+1];
					num[l+1]=t;
				}
		return;
	}
	return;
}
void merge()
{
	merge_work(0,99);
	for(int i=0;i<100;++i)
		std::cout<<num[i]<<" ";
	std::cout<<std::endl;
	return;
}

int main()
{
	init();
	bubble();
	init();
	select();
	init();
	insert();
	init();
	merge();
	return 0;
}
