/*
	Name: Strassen
	Copyright: 
	Author: Json Lee
	Date: 26/09/16 16:10
	Description: 
	Divide and Conquer,
	P1=A11*(B12-B22)
	P2=(A11+A12)*B22
	P3=(A21+A22)*B11
	P4=A22*(B21-B11)
	P5=(A11+A22)*(B11+B22)
	P6=(A12-A22)*(B21+B22)
	P7=(A11-A21)*(B11+B12)
	
	C11=P4+P5+P6-P2
	C12=P1+P2
	C21=P3+P4
	C22=P1+P5-P3-P7
*/

#include<iostream>
using namespace std;


int main()
{
	return 0;
} 
