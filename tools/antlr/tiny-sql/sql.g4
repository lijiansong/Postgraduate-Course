grammar sql;
root 
    : 'select' select_list 
    'from' table_sources
    'where' search_condition
    ('group' 'by' group_by_item (',' group_by_item)*)?
    ('having' search_condition)?
    ('within' within_time)?
    ;

select_list
    : select_list_elem (',' select_list_elem)*
    ;

select_list_elem
    : /*(table_name=ID '.' column_name=ID)*/
    expression
    | aggregate_function'(' expression ')'
    ;

ID
    : [a-zA-Z_][a-zA-Z_0-9]*
    ;

table_sources
    : table_source (',' table_source)*
    ;

table_source
    : ID
    ;

expression
    : aggregate_function
    | (table_name '.' column_name)
    | NUM
    ;

NUM
    : '-'[1-9][0-9]*
    | '0'
    | [1-9][0-9]*
    ;

table_name
    : ID
    ;

column_name
    : ID
    ;

aggregate_function
    : 'avg' | 'max' | 'min' | 'sum'
    ;

search_condition
    : search_condition_and ('and' search_condition_and)*
    ;

search_condition_and
    : expression comparison_operator expression
    | '(' search_condition ')'
    ;

comparison_operator
    : '=' | '>' | '<' | '<=' | '>=' | '!='
    ;

group_by_item
    : expression
    ;

within_time
    : (NUM)
    ;

WS  : [ \t\r\n]+ -> skip ; // Define whitespace rule, toss it out
