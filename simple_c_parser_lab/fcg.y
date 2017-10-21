%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
int yydebug = 1;
char* lastFunction = "";
extern void yyerror( char* );
extern int yylex();
%}

/*********************************************************
* Note: %token is similar to %token
* 
********************************************************/
%union {
    char* id;
}

/*
 * Only ID will capture text in this case.  Otherwise, we let Yacc assign
 * values to our tokens and handle them internally.  Their defintions will be
 * included by our scanner, so the values and definitions have been removed.
 */
%token <id> ID
%token INTVAL
%token FLTVAL
%token DBLVAL
%token STRVAL
%token CHARVAL
%token VOID
%token CHAR
%token SHORT
%token INT
%token LONG
%token FLOAT
%token DOUBLE
%token EQ
%token NE
%token GE 
%token LE
%token GT
%token LT
%token ADD 
%token SUB
%token MUL
%token DIV
%token MOD
%token OR
%token AND
%token BITOR
%token BITAND
%token BITXOR
%token NOT
%token COM
%token LSH
%token RSH
%token SET
%token SETADD
%token SETSUB
%token SETMUL
%token SETDIV
%token SETMOD
%token SETOR
%token SETAND
%token SETXOR
%token SETLSH
%token SETRSH 
%token RETURN
%token DO
%token WHILE
%token FOR
%token SWITCH
%token CASE
%token DEFAULT
%token IF
%token ELSE
%token CONTINUE
%token BREAK
%token GOTO
%token UNSIGNED
%token TYPEDEF
%token STRUCT
%token UNION
%token CONST
%token STATIC
%token EXTERN
%token AUTO
%token REGISTER
%token SIZEOF


%start top

%%



/*********************************************************
 * The top level parsing rule, as set using the %start
 * directive above.
 ********************************************************/
top : 
	|function top


/*
 * Function definition
 */
function 	: func_signature '{' func_body '}'


/*
 * Function signature
 */
func_signature 	: type ID '(' args ')' { printf("%s", $2); printf(";\n"); lastFunction = $2;}


/*
 * Function bodies are arbitrary numbers of statements
 */
func_body	: blockbody


/*
 * Function arguments
 */
args 	: /* empty rule */
	| expr
	| expr ',' args


/*
 * Function calls
 */
func_call	: ID '(' args ')' { printf("%s -> %s;\n", lastFunction, $1);}


/*
 * Declarations
 */
decl		: type ID ';'
		| type ID '[' expr ']' ';'
		| type ptrtail ID ';'
		| type ptrtail ID '[' expr ']';

/*
 * Arbitrary depth of pointer stars
 */
ptrtail		: ptrtail MUL
		| MUL


/*
 * Arbitrary length of block body
 */
blockbody	: /* Nothing */
		| statement blockbody
		| decl blockbody


/*
 * Statements
 *
 * Credit to the Parsifal Software AnaGram page for helping me work this out.
 * C resolves the 'dangling else' problem by binding the else to the nearest
 * if clause.  Here, we do so by defining a closed and an open statement,
 * referring to whether there can still be an unresolved else (open) or there
 * are no unresolved elses (closed).  Closed enforces its task by only
 * allowing complete statements (thereby recursing) or paired if-else clauses.
 * The open state allows only closed states between the first if and the last
 * else, and then lets another open state resolve itself thereafter.
 *
 * Accessed Oct. 2017
 * http://parsifalsoft.com/ifelse.html
 */
statement	: openstatem
		| closedstatem

simstatement	: ID SET expr ';'
		| RETURN expr ';'
		| func_call
		| '{' blockbody '}'
		| BREAK ';'
		| CONTINUE ';'
		| ';'

closedstatem	: simstatement
		| IF '(' expr ')' closedstatem ELSE closedstatem
		| loop closedstatem

openstatem	: IF '(' expr ')' statement
		| IF '(' expr ')' closedstatem ELSE openstatem
		| loop openstatem

loop		: WHILE '(' expr ')'


/*
 * This part was hard to wrap my head around, so I referenced an
 * EBNF for C, written by Jeff Lee in (the year that i was born) 1985.
 * The operators with the highest precedence are bound more closely to
 * the most primitive constructs: mutables and immutables.  From there,
 * each level of precedence moves further from the primitives, referencing
 * only the expressions immediately above it in the precedence hierarchy.
 *
 * For right-associative operators, this process is sort of inverted; the left
 * side of the operator is set to a mutable, and the right side is then
 * expanded from the furthest expression from mutables.
 *
 * Accessed Oct 2017
 * https://www.lysator.liu.se/c/ANSI-C-grammar-y.html
 *
 *
 * E -> E + T | T
 * T -> T * F | F
 * F -> (E) | D
 * D -> 1 | 2 | 3 | 4 
 *
 */


/*
 * General expressions
 */
expr		: type ID
		| type ID '[' ']'
		| type ptrtail ID
		| type ptrtail ID '[' ']'
		| assignex

/*
 * Assignment expressions, right-associative
 */
assignex	: mutable SETADD assignex
		| mutable SETSUB assignex
		| mutable SETMUL assignex
		| mutable SETDIV assignex
		| mutable SETMOD assignex
		| mutable '+' '+'
		| mutable '-' '-'
		| orex

/*
 * Logicl or expressions
 */
orex		: orex OR andex
		| andex


/*
 * Logical and expressions
 */
andex		: andex AND bitex
		| bitex

/*
 * Bitwise expressions
 */
bitex		: bitex BITAND relex
		| bitex BITXOR relex
		| bitex BITOR relex
		| relex

/*
 * Relational expressions
 */
relex		: relex LT shiftex
		| relex GT shiftex
		| relex LE shiftex
		| relex GE shiftex
		| relex EQ shiftex
		| relex NE shiftex
		| shiftex

/*
 * Shift expressions
 */
shiftex		: shiftex RSH addex
		| shiftex LSH addex
		| addex

/*
 * Addition expressions
 */
addex		: addex ADD mulex
		| addex SUB mulex
		| mulex

/*
 * Multiplication expressions
 */
mulex		: mulex MUL unaryex
		| mulex DIV unaryex
		| mulex MOD unaryex
		| unaryex

/*
 * Unary expressions (1 or less operators)
 */
unaryex		: '-' unaryex
		| '+' unaryex
		| NOT unaryex
		| COM unaryex
		| MUL unaryex
		| '(' type ')' unaryex
		| SIZEOF unaryex
		| mutable

/*
 * These compose LHS (address) contructs
 */
mutable		: ID
		| arrex
		| immutable


/*
 * These compose RHS (value and constant) constructs
 */
immutable	: CONST ID
		|'(' expr ')'
		| func_call
		| primex

/*
 * Array access via brackets or pointer math
 */
arrex		: ID '[' expr ']'


/*
 * Primitive expressions are literals
 */
primex		: INTVAL
		| STRVAL
		| CHARVAL
		| DBLVAL
		| FLTVAL


type 		: VOID
		| CHAR
		| SHORT
		| INT
		| LONG
		| FLOAT
		| DOUBLE
		| MUL type

%%

/*********************************************************
 * This method is invoked by the parser whenever an
 * error is encountered during parsing; just print
 * the error to stderr.
 ********************************************************/
void yyerror( char *err ) {
    fprintf( stderr, "at line %d: %s\n", yylineno, err );
}

/*********************************************************
 * This is the main function for the function call
 * graph program. We invoke the parser and return the
 * error/success code generated by it.
 ********************************************************/
int main( int argc, const char *argv[] ) {
    printf( "digraph funcgraph {\n" );
    int res = yyparse();
    printf( "}\n" );

    return res;
}
