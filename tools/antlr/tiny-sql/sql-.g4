grammar sql;

@header {
package storm_sql.parser;
}

root
    : 'select' select_list
    'from' table_sources
    'where' search_condition
    ('group' 'by' group_by_item (',' group_by_item)*)?
    ('having' search_condition)?
    ('within' within_time)?
    ;


select_list
    : select_list_elem (',' select_list_elem)*	#printSelectList
    ;

select_list_elem
    : /*(table_name=ID '.' column_name=ID)*/
    expression					#printSelectListElem
    | aggregate_function'(' expression ')'	#selectAggregateFunction
    ;

ID
    : [a-zA-Z_][a-zA-Z_0-9]*
    ;

table_sources
    : table_source (',' table_source)*		#tableSources
    ;

table_source
    : ID					#tableSource
    ;

expression
    : aggregate_function			#exprAggrFunc
    | (table_name '.' column_name)		#expr
    | NUM					#num
    ;

NUM
    : '-'[1-9][0-9]*
    | '0'
    | [1-9][0-9]*
    ;

table_name
    : ID					#tableName
    ;

column_name
    : ID					#columnName
    ;

aggregate_function
    : 'avg' | 'max' | 'min' | 'sum'  | 'count'
    ;

search_condition
    : search_condition_and ('and' search_condition_and)*	#printSearchCondition
    ;

search_condition_and
    : expression comparison_operator expression			#printSearchConditionAnd
    //| '(' search_condition ')'
    ;

comparison_operator
    : '=' | '>' | '<' | '<=' | '>=' | '!='
    ;

group_by_item
    : expression						#groupByItem
    ;

within_time
    : (NUM)							#withinTime
    ;

WS  : [ \t\r\n]+ -> skip ; // Define whitespace rule, toss it out
