#include <iostream>
#include <fstream>
#include <list>
#include <cstring>

struct tree_node
{
	char c;
	std::list<tree_node> children;
	void add_new_word(std::string word,int n)
	{
		if(n==word.length())
		{
			tree_node new_node;
			new_node.c=0;
			this->children.push_back(new_node);
			return;
		}
		for(std::list<tree_node>::iterator i=children.begin();i!=children.end();++i)
			if(i->c==word[n])
			{
				i->add_new_word(word,n+1);
				return;
			}
		tree_node new_node;
		new_node.c=word[n];
		new_node.add_new_word(word,n+1);
		this->children.push_back(new_node);
		return;
	}
	bool search_word(std::string word,int n)
	{
		if(n==word.length())
		{
			for(std::list<tree_node>::iterator i=children.begin();i!=children.end();++i)
				if(!i->c)
					return true;
			return false;
		}
		for(std::list<tree_node>::iterator i=children.begin();i!=children.end();++i)
			if(i->c==word[n])
				return i->search_word(word,n+1);
		return false;
	}
	void output_words(std::ofstream& fout,std::string word)
	{
		if(children.empty())
			return;
		for(std::list<tree_node>::iterator i=children.begin();i!=children.end();++i)
		{
			if(!i->c)
				fout<<word<<std::endl;
			else
				i->output_words(fout,word+i->c);
		}
		return;
	}
	bool delete_word(std::string word,int n)
	{
		// n finally get to the word.length()+1 because word in key-tree has a '\0' node as its end
		if(n==word.length()+1 && children.empty())
			return true;
		for(std::list<tree_node>::iterator i=children.begin();i!=children.end();++i)
			if(i->c==word[n] && i->delete_word(word,n+1))
			{
				children.erase(i);
				break;
			}	
		// if children list is empty,it can be deleted
		return children.empty();
	}
	tree_node& operator=(const tree_node& p)
	{
		c=p.c;
		children=p.children;
		return *this;
	}
};

class key_tree
{
	private:
		tree_node root;
	public:
		key_tree()
		{
			root.c=0;
			return;
		}
		void add_word(std::string word)
		{
			if(!word.length())
				return;
			for(int i=0;i<word.length();++i)
			{
				if('A'<=word[i] && word[i]<='Z')
					word[i]+='a'-'A';
				if(!('a'<=word[i] && word[i]<='z'))
					return;
			}
			root.add_new_word(word,0);
			return;
		}
		bool search_word(std::string word)
		{
			if(!word.length())
				return false;
			for(int i=0;i<word.length();++i)
			{
				if('A'<=word[i] && word[i]<='Z')
					word[i]+='a'-'A';
				if(!('a'<=word[i] && word[i]<='z'))
					return false;
			}
			return root.search_word(word,0);
		}
		void output_words(std::ofstream& fout)
		{
			std::string tmp="";
			root.output_words(fout,tmp);
			return;
		}
		void delete_word(std::string word)
		{
			if(!word.length())
				return;
			for(int i=0;i<word.length();++i)
			{
				if('A'<=word[i] && word[i]<='Z')
					word[i]+='a'-'A';
				if(!('a'<=word[i] && word[i]<='z'))
					return;
			}
			root.delete_word(word,0);
			return;
		}
};

std::string word;
std::string target_word;
std::string after_edit_word;
std::string command;
key_tree KeyTree;
int main()
{
	std::ifstream fin("data.txt");
	if(fin.fail())
	{
		std::cout<<"cannot open file data.txt"<<std::endl;
		return 0;
	}
	while(!fin.eof())
	{
		fin>>word;
		if(fin.eof())
			break;
		KeyTree.add_word(word);
	}
	std::cout<<">> input \'help\' to get help."<<std::endl;
	while(1)
	{
		std::cout<<">> ";
		std::cin>>command;
		if(command=="help")
		{
			std::cout<<">> [add   ] add a new word."<<std::endl;
			std::cout<<">> [search] search a word."<<std::endl;
			std::cout<<">> [delete] delete a word."<<std::endl;
			std::cout<<">> [edit  ] edit a word."<<std::endl;
			std::cout<<">> [exit  ] exit the program."<<std::endl;
		}
		else if(command=="add")
		{
			std::cout<<">> input the word you want to add into the dictionary: ";
			std::cin>>word;
			if(!KeyTree.search_word(word))
			{
				KeyTree.add_word(word);
				std::cout<<">> finished."<<std::endl;
			}
			else
				std::cout<<">> this word exists."<<std::endl;
		}
		else if(command=="search")
		{
			std::cout<<">> input the word you want to search in the dictionary: ";
			std::cin>>word;
			if(!KeyTree.search_word(word))
				std::cout<<">> this word does not exist."<<std::endl;
			else
				std::cout<<">> this word exists."<<std::endl;
		}
		else if(command=="delete")
		{
			std::cout<<">> input the word you want to delete in the dictionary: ";
			std::cin>>word;
			if(!KeyTree.search_word(word))
				std::cout<<">> this word does not exist."<<std::endl;
			else
			{
				KeyTree.delete_word(word);
				std::cout<<">> finished."<<std::endl;
			}
		}
		else if(command=="edit")
		{
			std::cout<<">> input the word you want to edit in the dictionary: ";
			std::cin>>target_word;
			if(!KeyTree.search_word(target_word))
				std::cout<<">> this word does not exist."<<std::endl;
			else
			{
				std::cout<<">> input the changed word: ";
				std::cin>>after_edit_word;
				if(KeyTree.search_word(after_edit_word))
					std::cout<<">> this word exists."<<std::endl;
				else
				{
					KeyTree.delete_word(target_word);
					KeyTree.add_word(after_edit_word);
					std::cout<<">> finished."<<std::endl;
				}
			}
		}
		else if(command=="exit")
			break;
		else
			std::cout<<">> undefined command."<<std::endl;
	}
	std::ofstream fout("data.txt");
	KeyTree.output_words(fout);
	fin.close();
	fout.close();
	return 0;
}
