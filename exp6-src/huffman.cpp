#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

struct node
{
	int elem;
	node* left_child;
	node* right_child;
};

bool cmp(node* a,node* b)
{
	return a->elem>b->elem;
}

class huffman
{
	private:
		node* root;
		node* *array;
		bool *code;
	public:
		huffman()
		{
			code=new bool[32];
			root=NULL;
			array=new node*[100];
			for(int i=0;i<100;++i)
			{
				array[i]=new node;
				array[i]->elem=i+1;
				array[i]->left_child=NULL;
				array[i]->right_child=NULL;
			}
			// input files here
			return;
		}
		~huffman()
		{
			if(code)
				delete []code;
			if(array)
				delete []array;
			if(root)
			{
				list<node*> node_queue;
				node_queue.push_back(root);
				while(!node_queue.empty())
				{
					if(node_queue.front()->left_child)
						node_queue.push_back(node_queue.front()->left_child);
					if(node_queue.front()->right_child)
						node_queue.push_back(node_queue.front()->right_child);
					node* temp=node_queue.front();
					node_queue.pop_front();
					delete temp;
				}
			}
			return;
		}
		void create_huffman_tree()
		{
			for(int i=99;i>=1;--i)
			{
				sort(array,array+i+1,cmp);
				node* temp=new node;
				temp->left_child=array[i-1];
				temp->right_child=array[i];
				temp->elem=array[i-1]->elem+array[i]->elem;
				array[i-1]=temp;
			}
			root=array[0];
			return;
		}
		void print_code(node* t,int depth,int elem)
		{
			code[depth]=false;
			if(t)
			{
				if(t->left_child)
				{
					code[depth]=false;
					print_code(t->left_child,depth+1,elem);
				}
				if(t->right_child)
				{
					code[depth]=true;
					print_code(t->right_child,depth+1,elem);
					code[depth]=false;
				}
				if(!t->left_child && !t->right_child && elem==t->elem)
				{
					cout<<t->elem<<": ";
					for(int i=0;i<depth;++i)
						cout<<code[i];
					cout<<endl;
				}
			}
			return;
		}
		void print_huffman_code()
		{
			for(int i=1;i<101;++i)
				print_code(root,0,i);
			return;
		}
};

int main()
{
	huffman tree;
	tree.create_huffman_tree();
	tree.print_huffman_code();
	return 0;
}
