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

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "buffer.h"
#include "common.h"

Fnode::Fnode(Fnode* parent, int itemno, int number)
{
	itemname = itemno;
	par = parent;
	leftchild = NULL;
	rightsibling = NULL;
	count = number;
	next = NULL;
	ch[0]=0;
	ch[1]=0;
}

void Fnode::init(Fnode* parent, int Itemname, int Count, unsigned int Ch1, unsigned int Ch2)
{
	itemname = Itemname;
	par = parent;
	leftchild = NULL;
	rightsibling = NULL;
	count = Count;
	next = NULL;
	ch[0]=Ch1;
	ch[1]=Ch2;
}

Fnode::~Fnode()
{
	Fnode* temp, *temp1;;
	if(this->leftchild!=NULL)
	{
		temp=this->leftchild;
		temp1=temp->rightsibling;
		while(temp1!=NULL)
		{
			temp=temp1->rightsibling;;
			delete temp1;
			temp1=temp;
		}
		delete this->leftchild;
	}
}

Fnode* Fnode::append(FI_tree* fptree, Fnode* sib, int itemno, int counts, unsigned int Ch1, unsigned int Ch2)
{
	Fnode* child;

	child = (Fnode*)fp_buf->newbuf(1, sizeof(Fnode));
	child->init(this, itemno, counts, Ch1, Ch2);
	
	if(this->leftchild==NULL)this->leftchild=child;
	else
		sib->rightsibling = child;

//	if(fptree->head[fptree->order[itemno]]==NULL)
//		fptree->head[fptree->order[itemno]]=child; 
//	else{
		child->next = fptree->head[fptree->order[itemno]]->next;
		fptree->head[fptree->order[itemno]]->next = child;
//	}
	
	return child;
}

void Mnode::init(Mnode* parent, int Itemname, int Level)
{
	itemname = Itemname;
	par = parent;
	leftchild = NULL;
	rightsibling = NULL;
	next = NULL;
	level = Level;
}

Mnode::~Mnode()
{
}

Mnode* Mnode::append(MFI_tree* LMFI, Mnode* sib, int itemno, int Level)
{
	Mnode* child;

	child = (Mnode*)LMFI->Max_buf->newbuf(1, sizeof(Mnode));
	child ->init(this, itemno, Level);

	if(this->leftchild==NULL)this->leftchild=child;
	else
		sib->rightsibling = child;

	if(LMFI->head[LMFI->order[itemno]]==NULL)
		LMFI->head[LMFI->order[itemno]]=child; 
	else{
		child->next = LMFI->head[LMFI->order[itemno]];
		LMFI->head[LMFI->order[itemno]] = child;
	}
	return child;
}

void Cnode::init(Cnode* parent, int Itemname, int Count, int Level)
{
	itemname = Itemname;
	par = parent;
	leftchild = NULL;
	rightsibling = NULL;
	next = NULL;
	level = Level;
    count= Count;
	value_hash=0;
}

Cnode::~Cnode()
{
}

Cnode* Cnode::append(CFI_tree* LCFI, Cnode* sib, int itemno, int Level, int Count)
{
	Cnode* child;

	child = (Cnode*)LCFI->Close_buf->newbuf(1, sizeof(Cnode));
	child ->init(this, itemno, Count, Level);

	if(this->leftchild==NULL){
		this->leftchild=child;
		child->value_hash= (this->value_hash) | (item_hash_mask[itemno]);
	}
	else{		
		sib->rightsibling = child;
		child->value_hash = (sib->par->value_hash) | (item_hash_mask[itemno]);
	}

	if(LCFI->head[LCFI->order[itemno]]==NULL)
		LCFI->head[LCFI->order[itemno]]=child; 
	else{
		child->next = LCFI->head[LCFI->order[itemno]];
		LCFI->head[LCFI->order[itemno]] = child;
	}
	return child;
}

/*
closeHelper::closeHelper(){
}	

void closeHelper::init(){
	assert(CM_NO>0);
	measure=(unsigned int*)fp_buf->newbuf(1, CM_SIZE);
}

closeHelper::~closeHelper(){
}

void closeHelper::merge(closeHelper * ch){
	for (int i=0;i<CM_NO;i++) measure[i] &= (ch->measure[i]);
}

bool closeHelper::isclosed(closeHelper * ch){
	for (int i=0;i<CM_NO;i++) if ((measure[i]) & (ch->measure[i])) return false;
	return true;
}

bool closeHelper::isclosed(){
	for (int i=0;i<CM_NO;i++) if (measure[i]) return false;
	return true;
}

bool closeHelper::issubsumed(closeHelper * ch){
	for (int i=0;i<CM_NO;i++) if (((measure[i]) & (ch->measure[i])) != (measure[i])) return false;
	return true;		
}	

void closeHelper::copy(closeHelper * ch){
	for (int i=0;i<CM_NO;i++) measure[i]=ch->measure[i];
}

void closeHelper::set(int id, unsigned int mask){
	measure[id] |= mask;
}

void closeHelper::clear(){
	memset(measure,0,CM_SIZE);
	//for (int i=0;i<CM_NO;i++) measure[i]=0;
}
*/
