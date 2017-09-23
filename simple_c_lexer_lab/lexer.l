%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>	// toupper()

//Define the tokens that you want to return from your lex as follows
#define ID 256
#define INTVAL 257
#define NONZERO 1

%}

%option noyywrap nounput yylineno
%x COMMENT BLOCKCOMMENT INSTRING

ID  		[a-zA-Z][a-zA-Z0-9_]*
INT 		[0-9][0-9]*
OCT 		"0"[0-9][0-9]*
HEX 		"0x"[0-9a-fA-F]+
FLT 		[0-9][0-9]*\.[0-9]+f
DBL 		[0-9][0-9]*\.[0-9]+
CHR 		"'"(\\)?."'"
WS  		[ \t\n]
CFLOWORKEY 	"return"|"while"|"switch"|"default"|"else"|"break"|"do"|"for"|"case"|"if"|"continue"|"goto"|"unsigned"|"struct"|"const"|"extern"|"register"|"typedef"|"union"|"static"|"auto"|"sizeof"

%%

"//" {
	/****************************************
	* Matching with Single line comments in our
	* C code
	******************************************/
	BEGIN COMMENT;
}

"/*" {
	BEGIN BLOCKCOMMENT;
}

<BLOCKCOMMENT>"*/" {
	BEGIN 0;
}

<BLOCKCOMMENT>. {
	// Do nothing, don't care about stuff in comments	
}

<COMMENT>[\n](\r)? {
	/****************************************
	* A new line indicates end of a single
	* line comment in C
	****************************************/

	BEGIN 0;
}

<COMMENT>[ \t] {
	/****************************************
	* Lexer ignores the comments section
	* by Ignoring anything inside a comment
	*****************************************/
}

<COMMENT>. {
}

[ \t\n\r]+ {
	// C ignores whitespace	
}

^#.*"\n" {
	printf("PREPROC\n");
	return NONZERO;
}

"(" {
	printf("(\n");
	//return NONZERO; 
}

")" {
	printf(")\n");
	//return NONZERO; 
}

"{" {
	printf("{\n");
	//return NONZERO; 
}

"}" {
	printf("}\n");
	//return NONZERO; 
}

"[" {
	printf("[\n");
	//return NONZERO; 
}

"]" {
	printf("]\n");
	//return NONZERO; 
}

"," {
	printf(",\n");
	//return NONZERO; 
}

";" {
	printf(";\n");
	//return NONZERO; 
}

{INT}|{OCT}|{HEX} {
/*({INT}|{OCT}|{HEX})[;\]\)]? { */
	printf("INTVAL\n");
/*	switch(*(yytext + yyleng -1)){
		case ';':	printf(";\n"); break;
		case ')':	printf(")\n"); break;
		case ']':	printf("]\n"); break;
		default:	break;
	}
*/
	return NONZERO;
}

{DBL} {
	printf("DBLVAL\n");
	return NONZERO;
}

{FLT} {
	printf("FLTVAL\n");
	return NONZERO;
}

{CHR} {
	printf("CHARVAL\n");
	return NONZERO;
}

\".*\" {
	// Relying on greediness to match the longest enclosed string possible
	printf("STRVAL\n");
	return NONZERO;
}

"void" {
	printf("VOID\n");
	return NONZERO;
}

"short" {
	printf("SHORT\n");
	return NONZERO;
}

"long" {
	printf("LONG\n");
	return NONZERO;
}

"double" {
	printf("DOUBLE\n");
	return NONZERO;
}

"char" {
	printf("CHAR\n");
	return NONZERO;
}

"int" {
	printf("INT\n");
	return NONZERO;
}

"float" {
	printf("FLOAT\n");
	return NONZERO;
}

">=" {
	printf("GE\n");
	return NONZERO;
}

">>" {
	printf("RSH\n");
	return NONZERO;
}

"<<" {
	printf("LSH\n");
	return NONZERO;
}

"<=" {
	printf("LE\n");
	return NONZERO;
}

"%=" {
	printf("SETMOD\n");
	return NONZERO;
}

"!=" {
	printf("NE\n");
	return NONZERO;
}

"!" {
	printf("NOT\n");
	return NONZERO;
}

"%" {
	printf("MOD\n");
	return NONZERO;
}

"^=" {
	printf("SETXOR\n");
	return NONZERO;
}

"<<=" {
	printf("SETLSH\n");
	return NONZERO;
}

"&" {
	printf("BITAND\n");
	return NONZERO;
}

"+" {
	printf("ADD\n");
	return NONZERO;
}

"\*" {
	printf("MUL\n");
	return NONZERO;
}

"-" {
	printf("SUB\n");
	return NONZERO;
}

"<" {
	printf("LT\n");
	return NONZERO;
}

"/" {
	printf("DIV\n");
	return NONZERO;
}

">>=" {
	printf("SETRSH\n");
	return NONZERO;
}

"=" {
	printf("SET\n");
	return NONZERO;
}

"||" {
	printf("OR\n");
	return NONZERO;
}

">" {
	printf("GT\n");
	return NONZERO;
}

"*=" {
	printf("SETMUL\n");
	return NONZERO;
}

"==" {
	printf("EQ\n");
	return NONZERO;
}

"|=" {
	printf("SETOR\n");
	return NONZERO;
}

"&=" {
	printf("SETAND\n");
	return NONZERO;
}

"&&" {
	printf("AND\n");
	return NONZERO;
}

"^" {
	printf("BITXOR\n");
	return NONZERO;
}

"/=" {
	printf("SETDIV\n");
	return NONZERO;
}

"-=" {
	printf("SETSUB\n");
	return NONZERO;
}

"|" {
	printf("BITOR\n");
	return NONZERO;
}

"+=" {
	printf("SETADD\n");
	return NONZERO;
}

"~" {
	printf("COM\n");
	return NONZERO;
}


{CFLOWORKEY} {
	int i = 0;
	while(*(yytext+i)){
		putchar(toupper(*(yytext+i)));
		i++;
	}
	putchar('\n');
	return NONZERO;
}

{ID} {
	/**************************************
	* If an identifier is matched, then
	* print ID and return a token ID
	**************************************/

	printf("ID\n");
	return ID;
}

%%
int main(int argc, const char* argv[]) {
	/*Make a call to yylex() recursively. Whenever yylex() is called, it scans
	tokens from the global input file yyin (which defaults to stdin). It
	continues until it either reaches an end-of-file (at which point it returns
	the value 0) or one of its actions executes a return statement.*/
	while(yylex());
	return 0;
}
