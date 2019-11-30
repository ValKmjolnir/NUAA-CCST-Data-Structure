#include <iostream>
#include <cmath>
#include <list>

struct node
{
	int num;
	node* left_child;
	node* right_child;
};

class bi_sort_tree
{
	private:
		node* root;
	public:
		bi_sort_tree()
		{
			root=NULL;
			return;
		}
		~bi_sort_tree()
		{
			std::list<node*> que;
			if(root)
			{
				que.push_back(root);
				while(!que.empty())
				{
					if(que.front()->left_child)
						que.push_back(que.front()->left_child);
					if(que.front()->right_child)
						que.push_back(que.front()->right_child);
					delete que.front();
					que.pop_front();
				}
			}
			return;
		}
		void isrt(node* &p,int n)
		{
			if(!p)
			{
				p=new node;
				p->left_child=NULL;
				p->right_child=NULL;
				p->num=n;
				return;
			}
			else
			{
				if(n>=p->num)
					isrt(p->right_child,n);
				else
					isrt(p->left_child,n);
			}
			return;
		}
		void insert_node(int n)
		{
			isrt(root,n);
			return;
		}
		void delt(node* &p,int n)
		{
			if(!p)
				return;
			if(n<p->num)
				delt(p->left_child,n);
			if(n>p->num)
				delt(p->right_child,n);
			if(n==p->num)
			{
				if(!p->left_child && !p->right_child)
				{
					delete p;
					p=NULL;
				}
				else if(p->left_child && !p->right_child)
				{
					node* temp=p;
					p=p->left_child;
					delete temp;
				}
				else if(!p->left_child && p->right_child)
				{
					node* temp=p;
					p=p->right_child;
					delete temp;
				}
				else if(p->left_child && p->right_child)
				{
					std::list<node*> que;
					int num=0x7fffffff;
					que.push_back(p);
					while(!que.empty())
					{
						if(que.front()->left_child)que.push_back(que.front()->left_child);
						if(que.front()->right_child)que.push_back(que.front()->right_child);
						if(que.front()->num>p->num)
							num=std::min(num,que.front()->num);
						que.pop_front();
					}
					delt(p,num);
					p->num=num;
				}
				return;
			}
		}
		void delete_node(int n)
		{
			delt(root,n);
			return;
		}
		void prt(node* p)
		{
			if(p)
			{
				prt(p->left_child);
				std::cout<<p->num<<" ";
				prt(p->right_child);
			}
			return;
		}
		void print()
		{
			std::cout<<"elems: ";
			prt(root);
			std::cout<<std::endl;
			return;
		}
};

int main()
{
	bi_sort_tree t;
	int n;
	std::cin>>n;
	for(int i=0;i<n;++i)
	{
		int elem;
		std::cin>>elem;
		t.insert_node(elem);
		t.print();
	}
	std::cin>>n;
	for(int i=0;i<n;++i)
	{
		int elem;
		std::cin>>elem;
		t.delete_node(elem);
		t.print();
	}
	return 0;
}
