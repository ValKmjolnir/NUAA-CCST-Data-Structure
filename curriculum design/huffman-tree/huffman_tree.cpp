#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>

// total_chars is used to record the number of chars in file
// this can also be put in code.dat to make sure output file is the same as source file
int total_chars=0;


// code[128] are used to record each character's huffman-code
struct char_codes
{
	char character;
	int cnt;
	int length;
	bool seq[40];
}code[128];
bool length_cmp(char_codes a,char_codes b)
{
	return a.length<b.length;
}

// huffman tree's node
struct node
{
	int num;
	char character;
	node* left_child;
	node* right_child;
};
bool cmp(node* a,node* b)
{
	return (a->num)>(b->num);
}


/*
	huffman tree is used to count every chars and generate a tree
	then use code[128] to record the result
*/
class huffman_tree
{
	private:
		int cnt[128];
		bool tempcode[40];
		node* root;
	public:
		huffman_tree()
		{
			root=NULL;
			for(int i=0;i<128;++i)
				cnt[i]=0;
			return;
		}
		~huffman_tree()
		{
			if(!root)
				return;
			// use bfs to delete all nodes
			std::list<node*> node_queue;
			node_queue.push_back(root);
			while(!node_queue.empty())
			{
				if(node_queue.front()->left_child)
					node_queue.push_back(node_queue.front()->left_child);
				if(node_queue.front()->right_child)
					node_queue.push_back(node_queue.front()->right_child);
				node* temp=node_queue.front();
				delete temp;
				node_queue.pop_front();
			}
			return;
		}
		void input_file(const char* filename)
		{
			std::ifstream fin(filename,std::ios::binary);
			if(fin.fail())
			{
				std::cout<<"cannot open "<<filename<<"."<<std::endl;
				fin.close();
				return;
			}
			char c;
			while(!fin.eof())
			{
				c=fin.get();
				if(fin.eof())
					break;
				if(0<=c && c<128)
				{
					++cnt[c];
					++total_chars;
				}
			}
			fin.close();
			return;
		}
		void create_tree()
		{
			root=NULL;
			for(int i=0;i<128;++i)
			{
				if(cnt[i])
					break;
				if(!cnt[i] && i==127)
					return;
			}
			node* nodes[128];
			for(int i=0;i<128;++i)
			{
				nodes[i]=new node;
				nodes[i]->left_child=NULL;
				nodes[i]->right_child=NULL;
				nodes[i]->num=cnt[i];
				nodes[i]->character=(char)i;
			}
			for(int i=127;i>=1;--i)
			{
				std::sort(nodes,nodes+i+1,cmp);
				node* temp=new node;
				temp->left_child=nodes[i-1];
				temp->right_child=nodes[i];
				temp->num=nodes[i-1]->num+nodes[i]->num;
				nodes[i-1]=temp;
			}
			root=nodes[0];
			return;
		}
		void dfs(node* tree,int depth)
		{
			if(!tree)
				return;
			if(!tree->left_child && !tree->right_child)
			{
				code[tree->character].character=tree->character;
				code[tree->character].length=depth;
				code[tree->character].cnt=tree->num;
				for(int i=0;i<depth;++i)
					code[tree->character].seq[i]=tempcode[i];
				return;
			}
			else
			{
				if(tree->left_child)
				{
					tempcode[depth]=false;
					dfs(tree->left_child,depth+1);
				}
				if(tree->right_child)
				{
					tempcode[depth]=true;
					dfs(tree->right_child,depth+1);
					tempcode[depth]=false;
				}
			}
			return;
		}
		void generate_code()
		{
			dfs(root,0);
			return;
		}
};

// output the huffman code of each char from 0 to 127
void information_output()
{
	std::ofstream fout("Huffman.txt");
	for(int i=0;i<128;++i)
	{
		fout<<code[i].cnt<<" ";
		for(int j=0;j<code[i].length;++j)
			fout<<code[i].seq[j];
		fout<<std::endl;
	}
	fout.close();
	return;
}

// condense inputfilename -> outputfilename
void generate_file(const char* inputfilename,const char*outputfilename)
{
	std::list<bool> sequence;
	std::ifstream fin(inputfilename,std::ios::binary);
	std::ofstream fout(outputfilename,std::ios::binary);
	if(fin.fail())
	{
		std::cout<<"cannot open "<<inputfilename<<"."<<std::endl;
		fin.close();
		fout.close();
		return;
	}
	char c;
	while(!fin.eof())
	{
		c=fin.get();
		if(fin.eof())
			break;
		for(int i=0;i<code[c].length;++i)
			sequence.push_back(code[c].seq[i]);
	}
	int cnt=7;
	c=0;// must set to zero or the decoded file will be wrong
	for(std::list<bool>::iterator i=sequence.begin();i!=sequence.end();++i,--cnt)
	{
		if(cnt<0)
		{
			// each 8 bits make an output
			cnt=7;
			fout.put(c);
			c=0;
		}
		c+=((*i)<<cnt);
	}
	fout.put(c);
	fin.close();
	fout.close();
	return;
}

void decoder(const char* inputfilename,const char* outputfilename)
{
	char_codes temp[128];
	for(int i=0;i<128;++i)
		temp[i]=code[i];
	std::sort(temp,temp+128,length_cmp);
	// must use sort first or some chars will be wrong
	
	std::list<bool> sequence;
	std::ifstream fin(inputfilename,std::ios::binary);
	std::ofstream fout(outputfilename,std::ios::binary);
	if(fin.fail())
	{
		std::cout<<"cannot open "<<inputfilename<<"."<<std::endl;
		fin.close();
		fout.close();
		return;
	}
	char c;
	while(!fin.eof())
	{
		c=fin.get();
		if(fin.eof())
			break;
		for(int i=7;i>=0;--i)
			sequence.push_back(c&(1<<i));
	}
	fin.close();
	
	int char_cnt=0;
	for(std::list<bool>::iterator i=sequence.begin();i!=sequence.end();++i)
		for(int j=0;j<128;++j)
		{
			int cnt=0;
			bool put=false;
			for(std::list<bool>::iterator k=i;cnt<temp[j].length;++k,++cnt)
			{
				if(k==sequence.end())
					break;
				if(*k!=temp[j].seq[cnt])
					break;
				if(*k==temp[j].seq[cnt] && cnt==temp[j].length-1)
				{
					if(char_cnt<total_chars)
					{
						std::cout<<temp[j].character;
						fout.put(temp[j].character);
						++char_cnt;
					}
					i=k;
					put=true;
					break;
				}
			}
			if(put)
				break;
		}
	fout.close();
	return;
}

int main()
{
	huffman_tree t;
	t.input_file("article.txt");
	t.create_tree();
	t.generate_code();
	
	information_output();
	generate_file("article.txt","code.dat");
	decoder("code.dat","recode.txt");
	return 0;
}
