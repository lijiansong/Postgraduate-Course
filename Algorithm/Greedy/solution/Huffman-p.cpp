#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
#include<cassert>
#include<algorithm>

//table basic
struct node
{
	char ch;
	double frequence;// the frequence of ch
};
//huffman tree node
struct huff_tree: public node
{
	char lcode;
	char rcode;
	huff_tree *left;//left child tree
	huff_tree *right;//right child tree
};

//decreasing order
bool cmp(const node &a, const node &b)
{
	return (a.frequence - b.frequence) < 1e-9;
}

class Huffman
{
private:
	int table_size;//size of the huffman table
	node *huff_table;
	std::map<char,std::string> huff_code;
	
public:
	//encode the input file into huffman compression file
	void Encode(const char *inFileName,const char *outFileName);
	//decode from the huffman code file to get the original file
	void Decode(const char *inFileName,const char *outFileName);
	//build huffman tree
	void BuildHuffmanTree();
	// generate huffman code
	void GenHuffCode(huff_tree *node);
	//destroy huffman tree
	void DestroyTree(huff_tree *node);

};

//encode the input file into huffman compression file
void Huffman::Encode(const char *inFileName,const char *outFileNmae)
{
	std::map<char,int> freq;
	FILE* infile=fopen(inFileName,"r");
	assert(infile);
	
	char ch;
	int total=0;
	while(fscanf(infile,"%c",&ch)!=EOF)
	{
		++freq[ch];
		++total;
	}
	this->table_size=freq.size();
	//build huffman code table
	huff_table=new node[table_size];
	assert(huff_table);
	
	std::map<char,int>::iterator it;
	int i=0;
	for(it=freq.begin(),i=0;it!=freq.end();++it,++i)
	{
		huff_table[i].ch=(*it).first;
		huff_table[i].frequence=(double)((*it).second)/((double)total);
	}
	std::sort(huff_table,huff_table+table_size,cmp);
	
	//Encode by Huffman tree
	BuildHuffmanTree();
	
	FILE* outfile=fopen(outFileNmae,"wb");
	assert(outfile);
	
	fseek(infile,SEEK_SET,0);
	while(fscanf(infile,"%c",&ch)!=EOF)
	{
		//printf("%s",huff_code[ch].c_str());
		fprintf(outfile,"%s",huff_code[ch].c_str());
	}
	
	//release
	delete []huff_table;
	fclose(infile);
	fclose(outfile);
}

//build Huffman tree 
void Huffman::BuildHuffmanTree()
{
	//initilize leaf node
	huff_tree *node;
	std::vector<huff_tree*> top;
	int i,num=this->table_size;
	for(i=0;i<num;++i)
	{
		node=new huff_tree;
		assert(node);
		node->ch=huff_table[i].ch;
		node->frequence=huff_table[i].frequence;
		node->left=NULL;
		node->right=NULL;
		top.push_back(node);
	}
	//build huffman tree by combining last two nodes and replacing them with a new node
	while(num>1)
	{
		node=new huff_tree;
		assert(node);
		node->frequence=top[num-2]->frequence+top[num-1]->frequence;
		node->left=top[num-2];
		node->right=top[num-1];
		if((node->left->frequence-node->right->frequence)<1e-6)
		{
			node->lcode='0';
			node->rcode='1';
		}
		else
		{
			node->lcode='1';
			node->rcode='0';
		}
		top.pop_back();
		top.pop_back();
		
		bool flag=false;
		std::vector<huff_tree*>::iterator it;
		for(it=top.begin();it!=top.end();++it)
		{
			if(((*it)->frequence - node->frequence)<1e-6)
			{
				top.insert(it,node);
				flag=true;
				break;
			}
			if(!flag)
				top.push_back(node);
		}
		--num;
	}
	huff_tree *root=top[0];
	//generate Huffman code 
	GenHuffCode(root);
	
	//release
	DestroyTree(root);
	top.clear();
}

//generate Huffman code 
void Huffman::GenHuffCode(huff_tree *node)
{
	static std::string seq="";
	if(node->left)
	{
		seq+=node->lcode;
		GenHuffCode(node->left);
	}
	if(node->right)
	{
		seq+=node->rcode;
		GenHuffCode(node->right);
	}
	//reach leaf node 
	if(!node->left && !node->right)
	{
		this->huff_code[node->ch]=seq;
	}
	int len=seq.length();
	if(len>1)
		seq=seq.substr(0,len-1);
	else
		seq="";
}

//recursively  destroy the huffman tree
void Huffman::DestroyTree(huff_tree *node)
{
	if(node->left)
	{
		DestroyTree(node->left);
		delete node->left;
		node->left=NULL;
	}
	if(node->right)
	{
		DestroyTree(node->right);
		delete node->right;
		node->right=NULL;
	}
}

//decode from the huffman code file to get the original file
void Huffman::Decode(const char *inFileName,const char *outFileName)
{
	FILE *infile=fopen(inFileName,"r");
	assert(infile);
	
	FILE* outfile=fopen("outFileName","w");
	assert(outfile);
	
	std::map<char,std::string>::iterator it;
	char ch;
	std::string tmp="";
	while((ch = fgetc(infile))!=EOF)
	{
		tmp+=ch;
		for(it=huff_code.begin();it!=huff_code.end();++it)
		{
			if(!strcmp((*it).second.c_str(),tmp.c_str()))
			{
				tmp="";
				printf("%c",(*it).first);
				fprintf( outfile, "%c", (*it).first );
			}
		}
	}
	
	//release 
	huff_code.clear();
	fclose(infile);
	fclose(outfile);
}

int main()
{
	Huffman *h=new Huffman;
	assert(h);
	h->Encode( "Aesop_Fables.txt", "Aesop_Fables-en.txt" );
  	h->Decode( "Aesop_Fables-en.txt", "Aesop_Fables-de.txt" );
  	delete h;
	return 0;
} 
