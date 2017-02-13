tree grammar Compiler;

options {
	tokenVocab=Expr;  
	ASTLabelType=CommonTree;
	output = template;	
}

@header {
	package interpreter;
	import java.util.Random;
	import java.util.Map;
	import java.util.HashMap;	
}
@members{
	Random rand = new Random() ; 
	Map<String, Integer> valueMap = new HashMap<String, Integer>();
}

prog : ^(PROG s=stat) {System.out.println("Compute result : " + s.value);};

stat returns[Integer value]
: ^(STAT e=expr) {$value = e.value;}
;

expr returns[Integer value]
:     ^('+' e1=expr e2=expr) {$value = e1.value + e2.value;}
	| ^('-' e1=expr e2=expr) {$value = e1.value - e2.value;}
    | ^('*' e1=expr e2=expr) {$value = e1.value * e2.value;}
	| ^('/' e1=expr e2=expr) {$value = e1.value / e2.value;}
	| a=atom {$value = a.value;}
;

atom returns[Integer value]
:      ^(NUM i=INT) {$value = Integer.parseInt(i.getText());}
 	|  ^(VAR v=ID){String name=v.getText(); if(valueMap.get(name)==null){int t = rand.nextInt(10);valueMap.put(name,t); System.out.println(name + ":" + t); $value = t;}else{$value = valueMap.get(name);}} 
;