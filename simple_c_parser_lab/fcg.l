%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>	// toupper()
#include <fcg.yacc.h>

//Define the tokens that you want to return from your lex as follows
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

%%


"return" {
	return RETURN;
}

"while" {

	return WHILE;
}
"switch" {

	return SWITCH;
}
"default" {

	return DEFAULT;
}
"else" {

	return ELSE;
}
"break" {

	return BREAK;
}
"do" {

	return DO;
}
"for" {

	return FOR;
}
"case" {

	return CASE;
}
"if" {

	return IF;
}
"continue" {

	return CONTINUE;
}
"goto" {

	return GOTO;
}
"unsigned" {

	return UNSIGNED;
}
"struct" {

	return STRUCT;
}

"const" {

	return CONST;
}

"extern" {

	return EXTERN;
}
"register" {

	return REGISTER;
}
"typedef" {

	return TYPEDEF;
}
"union" {

	return UNION;
}
"static" {

	return STATIC;
}
"auto" {

	return AUTO;
}
"sizeof" {

	return SIZEOF;
}

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



<BLOCKCOMMENT>.|\n {
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

^#.*"\n"(\r)? {

	return ;
}

"(" {

	return '('; 
}

")" {

	return ')'; 
}

"{" {

	return '{'; 
}

"}" {

	return '}'; 
}

"[" {

	return '['; 
}

"]" {

	return ']'; 
}

"," {

	return ','; 
}

";" {

	return ';'; 
}

{INT}|{OCT}|{HEX} {
/*({INT}|{OCT}|{HEX})[;\]\)]? { */

/*	switch(*(yytext + yyleng -1)){
		case ';':	printf(";\n"); break;
		case ')':	printf(")\n"); break;
		case ']':	printf("]\n"); break;
		default:	break;
	}
*/
	return INTVAL;
}

{DBL} {

	return DBLVAL;
}

{FLT} {

	return FLTVAL;
}

{CHR} {

	return CHARVAL;
}

\"([^"]|\\\")*\" {
	/* We can't just match all quotes because we may encounter something
	* like this: "str1" "str\n number2"
	*
	* This would fail, so we need to match anything but a quote or a
	* escaped quote as the string contents.  So we build it as such:
	*
	* [^"] no quotes
	* \\\" escaped quote \"
	*
	* ([^"]|\\\")* any number combination of the above
	*
	* \"([^"]|\\\")*\" Wrapped in quotes on both ends.  Note that [^"] catches all
	* characters and ws
	*
	*/

	return STRVAL;
}

"void" {

	return VOID;
}

"short" {

	return SHORT;
}

"long" {

	return LONG;
}

"double" {

	return DOUBLE;
}

"char" {

	return CHAR;
}

"int" {

	return INT;
}

"float" {

	return FLOAT;
}

">=" {

	return GE;
}

">>" {

	return RSH;
}

"<<" {

	return LSH;
}

"<=" {

	return LE;
}

"%=" {

	return SETMOD;
}

"!=" {

	return NE;
}

"!" {

	return NOT;
}

"%" {

	return MOD;
}

"^=" {

	return SETXOR;
}

"<<=" {

	return SETLSH;
}

"&" {

	return BITAND;
}

"+" {

	return ADD;
}

"\*" {

	return MUL;
}

"-" {

	return SUB;
}

"<" {

	return LT;
}

"/" {

	return DIV;
}

">>=" {

	return SETRSH;
}

"=" {

	return SET;
}

"||" {

	return OR;
}

">" {

	return GT;
}

"*=" {

	return SETMUL;
}

"==" {

	return EQ;
}

"|=" {

	return SETOR;
}

"&=" {

	return SETAND;
}

"&&" {

	return AND;
}

"^" {

	return BITXOR;
}

"/=" {

	return SETDIV;
}

"-=" {

	return SETSUB;
}

"|" {

	return BITOR;
}

"+=" {

	return SETADD;
}

"~" {

	return COM;
}

{ID} {
	/**************************************
	* If an identifier is matched, then
	* print ID and return a token ID
	**************************************/

	yylval.id = strdup(yytext);

	return ID;
}

. {
	fprintf(stderr, "Unexpected input on line %d: '%s'\n", yylineno, yytext);
	exit(1);
}

%%
