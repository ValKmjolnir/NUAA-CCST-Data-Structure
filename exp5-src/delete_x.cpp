#include <iostream>
#include <list>

class binary_tree
{
	private:
		char elem;
		binary_tree* left_child;
		binary_tree* right_child;
	public:
		binary_tree()
		{
			left_child=NULL;
			right_child=NULL;
			return;
		}
		~binary_tree()
		{
			if(left_child)
				delete left_child;
			if(right_child)
				delete right_child;
		}
		void CreateBiTree()
		{
			std::cin>>elem;
			if(elem=='#')
				return;
			if(!left_child)
			{
				left_child=new binary_tree;
				left_child->CreateBiTree();
				if(left_child->elem=='#')
				{
					delete left_child;
					left_child=NULL;
				}
			}
			if(!right_child)
			{
				right_child=new binary_tree;
				right_child->CreateBiTree();
				if(right_child->elem=='#')
				{
					delete right_child;
					right_child=NULL;
				}
			}
			return;
		}
		void ClearBiTree()
		{
			if(left_child)
				delete left_child;
			if(right_child)
				delete right_child;
			return;
		}
		char Value()
		{
			return elem;
		}
		void PreOrderTraverse(void (*func)(binary_tree*))
		{
			func(this);
			if(left_child)
				left_child->PreOrderTraverse(func);
			if(right_child)
				right_child->PreOrderTraverse(func);
			return;
		}
		void delete_node(char x)
		{
			if(left_child)
			{
				if(left_child->elem==x)
				{
					delete left_child;
					left_child=NULL;
				}
				else
					left_child->delete_node(x);
			}
			if(right_child)
			{
				if(right_child->elem==x)
				{
					delete right_child;
					right_child=NULL;
				}
				else
					right_child->delete_node(x);
			}
			return;
		}
};
void visit(binary_tree* p)
{
	std::cout<<p->Value();
	return;
}
int main()
{
	binary_tree root;
	root.CreateBiTree();
	root.PreOrderTraverse(visit);
	std::cout<<std::endl;
	root.delete_node('x');
	root.PreOrderTraverse(visit);
	
	return 0;
}
