#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <cstring>
#include <cstdio>
using namespace std;

struct pnode
{
  char ch; // char
  float p; // frequency
};

//sort in decreasing order
static int cmp( const void *elem1, const void *elem2 )
{
  const pnode a = *(pnode*)elem1;
  const pnode b = *(pnode*)elem2;
  if( a.p < b.p ) return 1;
  else if( a.p > b.p ) return -1;
  return 0;
}

struct treenode : public pnode
{
  char lcode;
  char rcode;
  treenode *left; // left child
  treenode *right; // right child
};

class Huffman
{
private:
  int tab_size; // huffman code table size
  pnode *huff_table; // huffman table
  map<char, string> huff_code; // huffman code for each char

public:
  void Encode( const char *inputFilename, const char *outputFilename )
  {
    map<char, int> freqs; // frequency for each char from input text
    int i;

    FILE *inputFile;
    inputFile = fopen( inputFilename, "r" );
    assert( inputFile );

    //  Counting chars
    char ch;
    unsigned total = 0;
    while( fscanf( inputFile, "%c", &ch ) != EOF )
    {
      freqs[ch]++;
      total++;
    }
    tab_size = (int)freqs.size();

    //  Building decreasing freqs table
    huff_table = new pnode[tab_size];
    assert( huff_table );
    float ftot = float(total);
    map<char, int>::iterator fi;
    for( fi=freqs.begin(),i=0; fi!=freqs.end(); ++fi,++i )
    {
      huff_table[i].ch = (*fi).first;
      huff_table[i].p = float((*fi).second) / ftot;
    }
    qsort( huff_table, tab_size, sizeof(pnode), cmp );

    // Build huffamn tree
    BuildHuffmanTree();

    
    FILE *outputFile;
    outputFile = fopen( outputFilename, "wb" );
    assert( outputFile );

    //  Outputing encoded text
    fseek( inputFile, SEEK_SET, 0 );
    
    while( fscanf( inputFile, "%c", &ch ) != EOF )
    {
      //printf("%s", huff_code[ch].c_str());
      fprintf(outputFile, "%s", huff_code[ch].c_str());
    }

    //  Release
    delete[] huff_table;
    fclose( outputFile );
    fclose( inputFile );
  }
  
  void Decode( const char *inputFilename, const char *outputFilename )
  {
    //  Opening input file
    FILE *inputFile;
    inputFile = fopen( inputFilename, "r" );
    assert( inputFile );

    
    //  Opening output file
    FILE *outputFile;
    outputFile = fopen( outputFilename, "w" );
    assert( outputFile );

    //  Decoding and outputing to file
    char ch;
    string accum = "";
    map<char, string>::iterator ci;
    while((ch = fgetc(inputFile)) != EOF)
    {
      accum += ch;
      for( ci=huff_code.begin(); ci!=huff_code.end(); ++ci )
        if( !strcmp( (*ci).second.c_str(), accum.c_str() ) )
        {
          accum = "";
          //printf( "%c", (*ci).first );
          fprintf( outputFile, "%c", (*ci).first );
        }
    }

    //  Release
    huff_code.clear();
    fclose( outputFile );
    fclose( inputFile );
  }
private:
  void BuildHuffmanTree()
  {
    //  Creating leaves (initial top-nodes)
    treenode *n;
    vector<treenode*> tops; // top-nodes
    int i, numtop=tab_size;
    for( i=0; i<numtop; i++ )
    {
      n = new treenode;
      assert( n );
      n->ch = huff_table[i].ch;
      n->p = huff_table[i].p;
      n->left = NULL;
      n->right = NULL;
      tops.push_back( n );
    }

    //  Building huffman tree by combining last two nodes and replacing them by new node
    while( numtop > 1 )
    {
      n = new treenode;
      assert( n );
      n->p = tops[numtop-2]->p + tops[numtop-1]->p;
      n->left = tops[numtop-2];
      n->right = tops[numtop-1];
      if( n->left->p < n->right->p )
      {
        n->lcode = '0';
        n->rcode = '1';
      }
      else
      {
        n->lcode = '1';
        n->rcode = '0';
      }
      tops.pop_back();
      tops.pop_back();
      bool isins = false;
      std::vector<treenode*>::iterator ti;
      for( ti=tops.begin(); ti!=tops.end(); ++ti )
        if( (*ti)->p < n->p )
        {
          tops.insert( ti, n );
          isins = true;
          break;
        }
      if( !isins ) tops.push_back( n );
      numtop--;
    }

    //  Building huff_code
    treenode *root = tops[0];
    GenHuffCode( root );
    //  Release
    DestroyTree( root );
    tops.clear();
  }
  // generate huffman code
  void GenHuffCode( treenode *node ) 
  {
    static string sequence = "";
    if( node->left )
    {
      sequence += node->lcode;
      GenHuffCode( node->left );
    }

    if( node->right )
    {
      sequence += node->rcode;
      GenHuffCode( node->right );
    }

    if( !node->left && !node->right )
      huff_code[node->ch] = sequence;

    int l = (int)sequence.length();
    if( l > 1 ) sequence = sequence.substr( 0, l-1 );
    else sequence = "";
  }
  // recursively destroy the huffman tree
  void DestroyTree( treenode *node ) 
  {
    if( node->left )
    {
      DestroyTree( node->left );
      delete node->left;
      node->left = NULL;
    }

    if( node->right )
    {
      DestroyTree( node->right );
      delete node->right;
      node->right = NULL;
    }
  }
};

int main(int argc, char *argv[])
{
	
  Huffman *h=new Huffman;
  assert(h);
  h->Encode( "Aesop_Fables.txt", "Aesop_Fables-en.txt" );
  h->Decode( "Aesop_Fables-en.txt", "Aesop_Fables-de.txt" );
  coder->Encode( "graph.txt", "graph-en.txt" );
  coder->Decode( "graph-en.txt", "graph-de.txt" );
  delete h;

  return 0;
}

