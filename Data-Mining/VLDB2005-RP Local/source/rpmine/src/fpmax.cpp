/*
   Author:  Jianfei Zhu  
            Concordia University
   Date:    Sep. 26, 2003

Copyright (c) 2003, Concordia University, Montreal, Canada
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

   - Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
   - Neither the name of Concordia University nor the names of its
       contributors may be used to endorse or promote products derived from
       this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.

*/

/* This is an implementation of FP-growth* / FPmax* /FPclose algorithm.
 *
 * last updated Sep. 26, 2003
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include "common.h"
#include "buffer.h"

using namespace std;

#define LINT sizeof(int)

int *ITlen;
int* bran;
int* prefix;

int* order_item;		// given order i, order_item[i] gives itemname
int* item_order;		// given item i, item_order[i] gives its new order 
						//	order_item[item_order[i]]=i; item_order[order_item[i]]=i;
bool* current_fi;
int* compact;
int* supp;

MFI_tree** mfitrees;
CFI_tree** cfitrees;

stack* list;
int TRANSACTION_NO=0;
int ITEM_NO=100;
int THRESHOLD;

memory* fp_buf;

#ifdef FIM_PS
float delta;
int TH;
float MINSUP;
float delta1;
#endif


int CM_NO=0; //close measure number
int CM_SIZE=0;
int * item_cm_id; //id of the closed meausre
unsigned int * item_cm_mask; //mask of the closed measure
unsigned int * item_hash_mask;

int total=0;
int miss=0;
int skip=0;
int ccheck=0;
void printLen()
{
	int i, j;
	for(i=ITEM_NO-1; i>=0&&ITlen[i]==0; i--);
	int total=0;
	for(j=0; j<=i; j++) {
		printf("%d\n", ITlen[j]);
		total+=ITlen[j];
	}
	printf("%d\n",total);
}

void assignmask(FI_tree * ft){

	//cout<<"frequent item num "<<ft->itemno<<endl;
	item_cm_id=new int[ft->itemno];
	item_cm_mask=new unsigned int[ft->itemno];
	item_hash_mask=new unsigned int[ft->itemno];

	int id=0;
	unsigned int m=1;
	int num=0;

	//int i=ft->itemno-1;
	//for (;i>=0;i--){
	int i=0;
	for (;i<ft->itemno;i++){
		item_cm_id[i]=id;
		item_cm_mask[i]=m;
		m=m<<1;
		num++;
		if(num==33){
			id++;
			m=1;
			num=0;
			if (id==2) break;
		}
	}

	//for (;i>=0;i--){
	for (;i<ft->itemno;i++){
		item_cm_id[i]=0;
		item_cm_mask[i]=0;
	}
	
	m=1;
	num=0;
	for (i=ft->itemno-1;i>=0;i--){
		item_hash_mask[i]=m;
		m=m<<1;
		num++;
		if (num==33){
			m=1;num=0;
		}
	}
/*
	int bits=0;
	int * temp=new int[ft->itemno];
	bool * assigned=new bool[ft->itemno];

	int i;
	for (i=0;i<ft->itemno;i++) assigned[i]=false;

	int assign_num=-1;
	int temp_num=0;
	for (i=ft->itemno-1;i>=0;i--){
		if (assigned[i]) continue;
		assigned[i]=true;
		item_cm_id[i]=id;
		item_cm_mask[i]=m;
		m=m<<1;
		cout<<"new bits\t"<<i;
		temp_num=0;
		for (int j=i-1;j>=0;j--){
			if (j>=ft->itemno-1-SUDDEN) continue;
			if (assigned[j]) continue;
			if (ft->array[j][i-j-1]>=THRESHOLD) continue;
			bool conflict=false;
			for (int k=0;k<temp_num;k++){
				if (ft->array[j][temp[k]-j-1]>=THRESHOLD){
					conflict=true; break;
				}
			}

			if(!conflict){
				temp[temp_num++]=j;
				assigned[j]=true;
				item_cm_id[j]=id;
				item_cm_mask[i]=m;
				cout<<" "<<j;
			}
		}
		cout<<endl;
		assign_num++;
		bits++;
		if ((assign_num>0) && (assign_num %32 ==0)){
			assign_num=-1;id++;m=1;
		}

	}
*/
	CM_NO=id+1;
	CM_SIZE=CM_NO*sizeof(unsigned int);
//	cout<<"assigned bits "<<bits<<endl;
}

int main(int argc, char **argv)
{
/*
	if (argc < 5)
	{
	  cout << "usage: fmi <infile> <MINSUP> <delta1> <delta> <outfile>\n";
	  cout << "TRANSCATION_NO * MINSUP = FINAL OUTPUT THRESHOLD"<<endl;
	  cout<< "FINAL OUTPUT THRESHOLD * (1-delta1) = PSEUDO THRESHOLD "<<endl;
	  cout<<" PESUDO THRESHOLD /(1-delta) = SAMPLING THRESHOLD"<<endl;
	  cout << "delta: SAMPLING TOR"<<endl;
	  exit(1);
	}

	MINSUP=(float)atof(argv[2]);
	delta1=(float)atof(argv[3]);
	//THRESHOLD = atoi(argv[2]);

#ifdef FIM_PS
	delta=(float)atof(argv[4]);
	//TH=THRESHOLD;
	//THRESHOLD = (int) ((float)TH*(1-delta));
#endif
*/



	if (argc <=4)
	{
	  cout << "usage: rpmine <infile> <MINSUP> <delta> <outfile>\n";
	  cout << "TRANSCATION_NO * MINSUP = REAL THRESHOLD"<<endl;
	  cout<< "REAL THRESHOLD * (1-delta) = PSEUDO THRESHOLD "<<endl;
	  exit(1);
	}

	MINSUP=(float)atof(argv[2]);
	delta1=(float)atof(argv[3]);

#ifdef FIM_PS
	delta=delta1;
#endif

	clock_t start=clock();
	int i;
	FI_tree* fptree;

	Data* fdat=new Data(argv[1]);

	if(!fdat->isOpen()) {
		cerr << argv[1] << " could not be opened!" << endl;
		exit(2);
	}

	fp_buf=new memory(60, 4194304L, 8388608L, 2);
	fptree = (FI_tree*)fp_buf->newbuf(1, sizeof(FI_tree));
	fptree->init(-1, 0);
	fptree -> scan1_DB(fdat);
	ITlen = new int[fptree->itemno];
	bran = new int[fptree->itemno];
	compact = new int[fptree->itemno];
	prefix = new int[fptree->itemno];

#ifdef CFI
		list=new stack(fptree->itemno, true); 
#else
		list=new stack(fptree->itemno); 
#endif
	
	//cout<<"number of item no "<<fptree->itemno<<endl;


	assert(list!=NULL && bran!=NULL && compact!=NULL && ITlen!=NULL && prefix!=NULL);

	for(i =0; i < fptree->itemno; i++)
	{
		ITlen[i] = 0L;
		bran[i] = 0;
	}

	//fptree->fill_array(fdat);
	assignmask(fptree);

	//cout<<"number of bits "<<CM_NO<<endl;

	//CM_NO=1;
	fptree->scan2_DB(fdat);
    fdat->close();
	//delete fdat;
#ifdef CH	
	fptree->setmask(0,0);
#endif
	//cout<<"initialized "<<(clock()-start)*1.0/CLOCKS_PER_SEC<<endl;
/*
	int j;
	for(i=0; i<fptree->itemno-1-SUDDEN; i++)
	{
		cout<<i<<"\t";
		for (j=0;j<i;j++)
			cout<<"  ";
		for(j=0; j<fptree->itemno-1-i; j++)
			if (fptree->array[i][j]>=THRESHOLD)
				cout<<"1 ";
			else
				cout<<"0 ";
		cout<<endl;
	}
*/
	FSout* fout;
	//if(argc>=5)
	if(argc>=4)
	{
		fout = new FSout(argv[4]);

		//print the count of emptyset
#ifdef FI
		fout->printSet(0, NULL, TRANSACTION_NO);
#endif

#ifndef FIM_PS
#ifdef CFI
		if(TRANSACTION_NO != fptree->count[0])
			fout->printSet(0, NULL, TRANSACTION_NO);
#endif		
#endif		
	}else
		fout = NULL;


	if(fptree->Single_path())
	{
		Fnode* node;
		int i=0;
		for(node=fptree->Root->leftchild; node!=NULL; node=node->leftchild)
		{
			list->FS[i++]=node->itemname;
#ifdef CFI
				list->counts[i-1] = node->count;
#endif
		}

#ifdef FI
			fptree->generate_all(fptree->itemno, fout);
#endif

#ifdef CFI
			int Count;
			i=0;
			while(i<fptree->itemno)
			{
				Count = list->counts[i];
				for(; i<fptree->itemno && list->counts[i]==Count; i++);
				ITlen[i-1]++;
				fout->printSet(i, list->FS, Count);
			}
#endif
		
#ifdef MFI
			fout->printSet(fptree->itemno, list->FS, fptree->head[fptree->itemno-1]->count);
			ITlen[i-1]=1;
#endif
		printLen();
		return 0;
	}

	current_fi = new bool[fptree->itemno];
	supp=new int[fptree->itemno];		//for keeping support of items
	assert(supp!=NULL&&current_fi!=NULL);

	for(i = 0; i<fptree->itemno; i++)
	{
		current_fi[i] = false;
		supp[i]=0;
	}

#ifdef MFI
	MFI_tree* LMFI;
		mfitrees = (MFI_tree**)new MFI_tree*[fptree->itemno];
		memory* Max_buf=new memory(40, 1048576L, 5242880, 2);
		LMFI = (MFI_tree*)Max_buf->newbuf(1, sizeof(MFI_tree));
		LMFI->init(Max_buf, fptree, NULL, NULL, -1);
		fptree->set_max_tree(LMFI);
		mfitrees[0] = LMFI;
		fptree->FPmax(fout);
#endif

#ifdef CFI
	CFI_tree* LClose;
		cfitrees = (CFI_tree**)new CFI_tree*[fptree->itemno];
		memory* Close_buf=new memory(40, 1048576L, 5242880, 2);
		LClose = (CFI_tree*)Close_buf->newbuf(1, sizeof(CFI_tree));
		LClose->init(Close_buf, fptree, NULL, NULL, -1);
		fptree->set_close_tree(LClose);
		cfitrees[0] = LClose;
		fptree->FPclose(fout);
#endif

#ifdef FI
		fptree->FP_growth(fout);
#endif

	//printLen();
	if(fout)
		fout->close();

//	delete fp_buf;
	delete list;
	delete []current_fi;
	delete []supp;
	
	cout<<"Running Time "<<(clock()-start)*1.0/CLOCKS_PER_SEC<<endl;
	//cout<<"total "<<total<<"\tmiss "<<miss<<"\tskip "<<skip<<endl;
	//cout<<"THRESHOLD "<<(int)((float)TRANSACTION_NO*MINSUP)<<endl;
	//cout<<"ccheck "<<ccheck<<endl;
	return 0;
}
