/*----------------------------------------------------------------------
  File     : data.h
  Contents : data set management
----------------------------------------------------------------------*/
#ifndef _DATA_CLASS
#define _DATA_CLASS

#include <stdio.h>
#include <stdlib.h>
#include <vector>

//using namespace std;

#define TransLen 50

class Transaction
{
public:
	
	Transaction():maxlength(TransLen), length(0){ t = new int[maxlength];}
	void DoubleTrans(int);				// if current item is greater than current longest transaction, we change the length of t as 2*item
	~Transaction(){delete []t;}
  
	int maxlength;
	int length;
	int *t;
};

class Data
{
 public:
	
	Data(char *filename);
	~Data();
	int isOpen();
	void close(){if(in)fclose(in);}

	Transaction *getNextTransaction(Transaction* Trans);
	Transaction *getNextTransaction();
  
 private:
  
	FILE *in;
	Transaction ** trans;
	bool second;
	bool ready;
	int next;
};

#endif

