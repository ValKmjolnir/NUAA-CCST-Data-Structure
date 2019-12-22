#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <ctime>
#include <cmath>
int array[50000];
int temp[50000];

void insert_sort()
{
	int tmp;
	for(int i=1;i<50000;++i)
	{
		tmp=array[i];
		int j;
		for(j=i;j>0 && array[j-1]>tmp;--j)
			array[j]=array[j-1];
		array[j]=tmp;
	}
	return;
}

void shell_sort()
{
	int tmp;
	for(int d=20000;d>0;--d)
		for(int i=d;i<50000;i+=d)
		{
			tmp=array[i];
			int j;
			for(j=i;j-d>=0 && array[j-d]>tmp;j-=d)
				array[j]=array[j-d];
			array[j]=tmp;
		}
	return;
}

void bubble_sort()
{
	for(int i=0;i<49999;++i)
		for(int j=0;j<49999-i;++j)
			if(array[j]>array[j+1])
			{
				int t=array[j];
				array[j]=array[j+1];
				array[j+1]=t;
			}
	return;
}

void quick_sort(int l,int r)
{
	if(l>=r)
		return;
	int mid=array[(l+r)>>1];
	int i=l,j=r;
	while(i<=j)
	{
		while(array[i]<mid)++i;
		while(array[j]>mid)--j;
		if(i<=j)
		{
			int t=array[i];
			array[i]=array[j];
			array[j]=t;
			++i;
			--j;
		}	
	}
	quick_sort(l,j);
	quick_sort(i,r);
	return;
}

void select_sort()
{
	for(int i=0;i<49999;++i)
	{
		int min_place=i;
		for(int j=i+1;j<50000;++j)
			if(array[j]<array[min_place])
				min_place=j;
		if(min_place!=i)
		{
			int t=array[i];
			array[i]=array[min_place];
			array[min_place]=t;
		}
	}
	return;
}

void heap_adjust(int parent, int length)
{
    int temp=array[parent];// parent node
    int child=(parent<<1)+1;  // get left child
    while(child<length)
	{
        // if right child exists and right child is larger than left child
        // get the right child
        if(child+1<length && array[child]<array[child+1])
            ++child;
        if (temp>=array[child])
            break;
        array[parent]=array[child];
        parent=child;
        child=(parent<<1)+1;
    }
    array[parent]=temp;
    return;
}
void heap_sort()
{
	for(int i=25000;i>=0;--i)
		heap_adjust(i,50000);
	for(int n=49999;n>0;--n)
	{
		int temp_int=array[n];
		array[n]=array[0];
		array[0]=temp_int;
		heap_adjust(0,n);
	}
	return;
}

void merge_sort(int l,int r)
{
	if(l==r)return;
	if(l+1==r)
	{
		if(array[l]>array[r])
		{
			int t=array[l];
			array[l]=array[r];
			array[r]=t;
		}
		return;
	}
	int mid=(l+r)>>1;
	merge_sort(l,mid);
	merge_sort(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i!=mid+1 && j!=r+1)
	{
		if(array[i]<array[j])
			temp[k++]=array[i++];
		else
			temp[k++]=array[j++];
	}
	while(i!=mid+1)
		temp[k++]=array[i++];
	while(j!=r+1)
		temp[k++]=array[j++];
	for(int t=l;t<=r;++t)
		array[t]=temp[t];
	return;
}

void radix_sort()
{
	std::list<int> bucket[10];
	int k=1;
	for(int i=0;i<4;++i)// 0000~9999
	{
		k*=10;
		for(int j=0;j<50000;++j)
			bucket[(array[j]%k)/(k/10)].push_back(array[j]);
		int node=0;
		for(int j=0;j<10;++j)
		{
			for(std::list<int>::iterator iter=bucket[j].begin();iter!=bucket[j].end();++iter)
				array[node++]=*iter;
			bucket[j].clear();
		}	
	}
	return;
}
struct sort_method
{
	std::string name;
	double total_time;
	double each_time[10];
	sort_method& operator=(const sort_method& p)
	{
		name=p.name;
		total_time=p.total_time;
		for(int i=0;i<10;++i)
			each_time[i]=p.each_time[i];
		return *this;
	}
	bool operator<(const sort_method& b)
	{
		return this->total_time<b.total_time;
	}
};

void calc()
{
	std::string filename="data";
	std::string suffix=".txt";
	clock_t start,end;
	sort_method sorts[8];
	
	sorts[0].name="insert sort";
	std::cout<<sorts[0].name<<" is in progress."<<std::endl;
	sorts[0].total_time=0;
	for(char i='0';i<='9';++i)
	{
		std::cout<<i<<(i=='9'? '\n':' ');
		std::ifstream fin(filename+i+suffix);
		for(int j=0;j<50000;++j)
			fin>>array[j];
		fin.close();
		start=clock();
		insert_sort();
		end=clock();
		sorts[0].each_time[i-'0']=(double)(end-start)/CLOCKS_PER_SEC;
		sorts[0].total_time+=sorts[0].each_time[i-'0'];
	}
	
	sorts[1].name="shell sort";
	std::cout<<sorts[1].name<<" is in progress."<<std::endl;
	sorts[1].total_time=0;
	for(char i='0';i<='9';++i)
	{
		std::cout<<i<<(i=='9'? '\n':' ');
		std::ifstream fin(filename+i+suffix);
		for(int j=0;j<50000;++j)
			fin>>array[j];
		fin.close();
		start=clock();
		shell_sort();
		end=clock();
		sorts[1].each_time[i-'0']=(double)(end-start)/CLOCKS_PER_SEC;
		sorts[1].total_time+=sorts[1].each_time[i-'0'];
	}
	
	sorts[2].name="bubble sort";
	std::cout<<sorts[2].name<<" is in progress."<<std::endl;
	sorts[2].total_time=0;
	for(char i='0';i<='9';++i)
	{
		std::cout<<i<<(i=='9'? '\n':' ');
		std::ifstream fin(filename+i+suffix);
		for(int j=0;j<50000;++j)
			fin>>array[j];
		fin.close();
		start=clock();
		bubble_sort();
		end=clock();
		sorts[2].each_time[i-'0']=(double)(end-start)/CLOCKS_PER_SEC;
		sorts[2].total_time+=sorts[2].each_time[i-'0'];
	}

	sorts[3].name="quick sort";
	std::cout<<sorts[3].name<<" is in progress."<<std::endl;
	sorts[3].total_time=0;
	for(char i='0';i<='9';++i)
	{
		std::cout<<i<<(i=='9'? '\n':' ');
		std::ifstream fin(filename+i+suffix);
		for(int j=0;j<50000;++j)
			fin>>array[j];
		fin.close();
		start=clock();
		quick_sort(0,49999);
		end=clock();
		sorts[3].each_time[i-'0']=(double)(end-start)/CLOCKS_PER_SEC;
		sorts[3].total_time+=sorts[3].each_time[i-'0'];
	}

	sorts[4].name="select sort";
	std::cout<<sorts[4].name<<" is in progress."<<std::endl;
	sorts[4].total_time=0;
	for(char i='0';i<='9';++i)
	{
		std::cout<<i<<(i=='9'? '\n':' ');
		std::ifstream fin(filename+i+suffix);
		for(int j=0;j<50000;++j)
			fin>>array[j];
		fin.close();
		start=clock();
		select_sort();
		end=clock();
		sorts[4].each_time[i-'0']=(double)(end-start)/CLOCKS_PER_SEC;
		sorts[4].total_time+=sorts[4].each_time[i-'0'];
	}
	
	sorts[5].name="heap sort";
	std::cout<<sorts[5].name<<" is in progress."<<std::endl;
	sorts[5].total_time=0;
	for(char i='0';i<='9';++i)
	{
		std::cout<<i<<(i=='9'? '\n':' ');
		std::ifstream fin(filename+i+suffix);
		for(int j=0;j<50000;++j)
			fin>>array[j];
		fin.close();
		start=clock();
		heap_sort();
		end=clock();
		sorts[5].each_time[i-'0']=(double)(end-start)/CLOCKS_PER_SEC;
		sorts[5].total_time+=sorts[5].each_time[i-'0'];
	}

	sorts[6].name="merge sort";
	std::cout<<sorts[6].name<<" is in progress."<<std::endl;
	sorts[6].total_time=0;
	for(char i='0';i<='9';++i)
	{
		std::cout<<i<<(i=='9'? '\n':' ');
		std::ifstream fin(filename+i+suffix);
		for(int j=0;j<50000;++j)
			fin>>array[j];
		fin.close();
		start=clock();
		merge_sort(0,49999);
		end=clock();
		sorts[6].each_time[i-'0']=(double)(end-start)/CLOCKS_PER_SEC;
		sorts[6].total_time+=sorts[6].each_time[i-'0'];
	}
	
	sorts[7].name="radix_sort";
	std::cout<<sorts[7].name<<" is in progress."<<std::endl;
	sorts[7].total_time=0;
	for(char i='0';i<='9';++i)
	{
		std::cout<<i<<(i=='9'? '\n':' ');
		std::ifstream fin(filename+i+suffix);
		for(int j=0;j<50000;++j)
			fin>>array[j];
		fin.close();
		start=clock();
		radix_sort();
		end=clock();
		sorts[7].each_time[i-'0']=(double)(end-start)/CLOCKS_PER_SEC;
		sorts[7].total_time+=sorts[7].each_time[i-'0'];
	}
	
	std::sort(sorts,sorts+8);
	for(int i=0;i<8;++i)
	{
		std::cout<<sorts[i].name<<std::endl;
		std::cout<<"    total:  "<<sorts[i].total_time<<std::endl;
		std::cout<<"    detail: ";
		for(int j=0;j<10;++j)
			std::cout<<sorts[i].each_time[j]<<" ";
		std::cout<<std::endl;
	}
	return;
}

int main()
{
	calc();
	return 0;
}
