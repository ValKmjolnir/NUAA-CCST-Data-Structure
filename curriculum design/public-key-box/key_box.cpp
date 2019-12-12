#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>

int* box;
int key_number,n;
struct event
{
	int t;
	bool borrow;
	int key;
	bool operator<(const event& p)
	{
		if(t<p.t)
			return true;
		else if(t==p.t)
		{
			if(borrow && !p.borrow)
				return false;
			else if(!borrow && p.borrow)
				return true;
			else
				return key<p.key;
		}
		else
			return false;
	}
};

void get_key(int k)
{
	for(int i=0;i<key_number;++i)
		if(box[i]==k)
		{
			box[i]=0;
			break;
		}
	return;
}
void ret_key(int k)
{
	for(int i=0;i<key_number;++i)
		if(!box[i])
		{
			box[i]=k;
			break;
		}
	return;
}

int main()
{
	std::ifstream fin("data.txt");
	fin>>key_number>>n;
	box=new int[key_number];
	for(int i=0;i<key_number;++i)
		box[i]=i+1;
	std::list<event> que;
	
	for(int i=0;i<n;++i)
	{
		int bgt,lgh,k;
		fin>>k>>bgt>>lgh;
		event tmp;
		tmp.key=k;
		tmp.borrow=true;
		tmp.t=bgt;
		que.push_back(tmp);
		tmp.borrow=false;
		tmp.t=bgt+lgh;
		que.push_back(tmp);
	}
	fin.close();
	que.sort();
	
	while(!que.empty())
	{
		std::cout<<"time "<<que.front().t<<": ";
		if(que.front().borrow)
			get_key(que.front().key);
		else
			ret_key(que.front().key);
		for(int i=0;i<key_number;++i)
		{
			if(box[i])
				std::cout<<box[i]<<" ";
			else
				std::cout<<"_ ";
		}
		std::cout<<std::endl;
		que.pop_front();
	}
	
	delete []box;
	return 0;
}
