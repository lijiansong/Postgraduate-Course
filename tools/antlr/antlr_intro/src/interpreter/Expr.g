grammar Expr;

options{
	output = AST;
	ASTLabelType = CommonTree;
}

tokens{
	PROG; STAT; NUM; VAR;
}

@header {package interpreter;}
@lexer::header{package interpreter;}

prog : stat -> ^(PROG stat);

stat : expr EOF  -> ^(STAT expr)
;

expr : multExpr (('+'|'-')^ multExpr)*
;

multExpr : atom (('*'|'/')^ atom)*
;

atom :   '(' expr ')' -> expr
	   | INT -> ^(NUM INT)
	   | ID  -> ^(VAR ID)	
;


ID : ('a'..'z' |'A'..'Z')+ ;
INT : '0'..'9' + ;
NEWLINE:'\r' ? '\n' ;
WS : (' ' |'\t' |'\n' |'\r' )+ {skip();} ;

