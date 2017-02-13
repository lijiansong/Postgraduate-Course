tree grammar Compiler;

options {
	tokenVocab=Expr;  
	ASTLabelType=CommonTree;
	output = template;	
}

@header {
	package compiler; 
}
 

prog : ^(PROG s=stat) {System.out.println("RET");};

stat 
: ^(STAT e=expr)  
;

expr 
:     ^('+' e1=expr e2=expr) {System.out.println("ADD");}
	| ^('-' e1=expr e2=expr) {System.out.println("SUB");}
    | ^('*' e1=expr e2=expr) {System.out.println("MUL");}
	| ^('/' e1=expr e2=expr) {System.out.println("DIV");}
	| a=atom  
;

atom  
:      ^(NUM i=INT) {System.out.println("LDC "+i.getText());}
 	|  ^(VAR v=ID)  {System.out.println("LDV "+v.getText());}
;