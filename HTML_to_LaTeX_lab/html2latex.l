%{
/*
 * Definitions Section
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int list_type;
%}

%option       noyywrap nounput yylineno
%x            COMMENT PARA PRE OL UL LIO LIU
ws		[ \t\n]
%%

"<h1>"[^<]*"</h1>" {
	/**************************************************************************
	 * Matched an HTML H1 header so print it out as a LateX section title.
	 * The beginning and ending tags need to be stripped off before the
	 * title can be formatted in LateX.
	 *************************************************************************/
	yytext[yyleng-5] = 0;
	printf( "\n\\section{%s}", yytext+4 );
}

"<h2>"[^<]*"</h2>" {
	/**************************************************************************
	 * Matched an HTML H2 header so print it out as a LateX section title.
	 * The beginning and ending tags need to be stripped off before the
	 * title can be formatted in LateX.
	 *************************************************************************/
	yytext[yyleng-5] = 0;
	printf( "\n\\subsection{%s}", yytext+4 );

}

"<h3>"[^<]*"</h3>" {
	/**************************************************************************
	 * Matched an HTML H3 header so print it out as a LateX section title.
	 * The beginning and ending tags need to be stripped off before the
	 * title can be formatted in LateX.
	 *************************************************************************/
	yytext[yyleng-5] = 0;
	printf( "\n\\subsubsection{%s}", yytext+4 );

}

"<pre>"[^<]*"</pre>" {
	/*
	 * Matched a preformatted text block.  Everything here will be printed
	 * verbatim.  Thankfully, LaTeX has a great control called verbatim
	 * for this purpose...
	 */
	yytext[yyleng-6] = 0;
	printf("\\begin{verbatim}%s \\end{verbatim}", yytext+5);
}


"<!--" {
	/**************************************************************************
	 * Matched an HTML comment so print it out as a LateX comment. The
	 * beginning and ending tags are stripped off before the LateX comment
	 * is emitted.
	 *************************************************************************/
	printf( "%% " );
	BEGIN COMMENT;
}

[ \t\n\r]+ {
	/**************************************************************************
	 * Matched some whitespace that is not inside of an HTML tag. We
	 * just ignore the whitespace.
	 *************************************************************************/
}

. {
	/**************************************************************************
	 * Matched something that we did not expect to see. Issue an error and
	 * exit the program with a failure message.
	 *************************************************************************/
	fprintf( stderr, "Unexpected input at line %d: '%s'\n", yylineno, yytext );
	exit( 1 );
}

<COMMENT>"-->" {
	/**************************************************************************
	 * Matched an HTML end comment while parsing an HTML comment. Print out
	 * a new line and resume normal parsing.
	 *************************************************************************/
	printf( "\n" );
	BEGIN 0;
}

<COMMENT>[\n](\r)? {
	/**************************************************************************
	 * Matched a newline and possible carriage return while parsing an HTML
	 * comment. Print out a new line making sure to mark the next line as a
	 * comment as well.
	 *************************************************************************/
	printf( "\n%% " );
}

<COMMENT>[ \t] {
	/**************************************************************************
	 * Matched some white space while parsing an HTML comment. Print out
	 * the white space as is.
	 *************************************************************************/
	printf( "%s", yytext );
}

<COMMENT>. {
	/**************************************************************************
	 * Matched any other text while parsing an HTML comment. Print out
	 * the text as is.
	 *************************************************************************/
	printf( "%s", yytext );
}

"<p>" {
	/*
	 * Matched a paragraph tag.  Print a newline to cue Latex to a new
	 * paragraph, and begin the PARA state.
	 */
	printf("\n");
	BEGIN PARA;	
}

<PARA>"</p>" {
	/*
	 * Matched the end of our paragraph.
	 */
	printf("\n\n");
	BEGIN 0;	// Return to normal parsing
}

<PARA>[^<]* {
	/*
	 * Catchall: if we can't match any tags within our paragraph, we have
	 * a section of plain text to print.  print it.  TODO make sure we
	 * don't need to account for HTML skipping newlines/returns.
	 */
	printf("%s", yytext);
}

<PARA,UL,OL,LIU,LIO>"<small>"[^<]*"</small>" {
	/*
	 * Matched a small tag within our paragraph.  Since we are not
	 * required to support nestings within this, and we can assume the
	 * contents are just plain text, simply print the matched text less
	 * the tags themselves between the LaTeX control sequences.
	 */
		yytext[yyleng-8] = 0;
		printf("{\\scriptsize{%s}}", yytext+7);
}

<PARA,UL,OL,LIU,LIO>"<big>"[^<]*"</big>" {
	/*
	 * Matched a big tag within our paragraph.  Since we are not
	 * required to support nestings within this, and we can assume the
	 * contents are just plain text, simply print the matched text less
	 * the tags themselves within the LaTex control sequences.
	 */
		yytext[yyleng-6] = 0;
		printf("{\\Large{%s}}", yytext+5);

}

<PARA,UL,OL,LIU,LIO>"<b>"[^<]*"</b>" {
	/*
	 * Matched a bold tag within our paragraph.  Since we are not
	 * required to support nestings within this, and we can assume the
	 * contents are just plain text, simply print the matched text less
	 * the tags themselves within the LaTex control sequences.
	 */
		yytext[yyleng-4] = 0;
		printf("{\\textbf{%s}}", yytext+3);
}

<PARA,UL,OL,LIU,LIO>"<i>"[^<]*"</i>" {
	/*
	 * Matched an italics tag within our paragraph.  Since we are not
	 * required to support nestings within this, and we can assume the
	 * contents are just plain text, simply print the matched text less
	 * the tags themselves within the LaTex control sequences.
	 */
		yytext[yyleng-4] = 0;
		printf("{\\textit{%s}}", yytext+3);
}

<PARA,UL,OL,LIU,LIO>"<strong>"[^<]*"</strong>" {
	/*
	 * Matched a strong tag within our paragraph.  Since we are not
	 * required to support nestings within this, and we can assume the
	 * contents are just plain text, simply print the matched text less
	 * the tags themselves within the LaTex control sequences.
	 */
		yytext[yyleng-9] = 0;
		printf("{\\textmd{%s}}", yytext+8);
}

<PARA,UL,OL,LIU,LIO>"<em>"[^<]*"</em>" {
	/*
	 * Matched an emphasis tag within our paragraph.  Since we are not
	 * required to support nestings within this, and we can assume the
	 * contents are just plain text, simply print the matched text less
	 * the tags themselves within the LaTex control sequences.
	 */
		yytext[yyleng-5] = 0;
		printf("{\\emph{%s}}", yytext+4);
}

<PARA,UL,OL,LIU,LIO>"<sup>"[^<]*"</sup>" {
	/*
	 * Matched a superscript tag within our paragraph.  Since we are not
	 * required to support nestings within this, and we can assume the
	 * contents are just plain text, simply print the matched text less
	 * the tags themselves within the LaTex control sequences.
	 */
		yytext[yyleng-6] = 0;
		printf("{\\textsuperscript{%s}}", yytext+5);	
}

<PARA,UL,OL,LIU,LIO>"<sub>"[^<]*"</sub>" {
	/*
	 * Matched a subscript tag within our paragraph.  Since we are not
	 * required to support nestings within this, and we can assume the
	 * contents are just plain text, simply print the matched text less
	 * the tags themselves within the LaTex control sequences.
	 */
		yytext[yyleng-6] = 0;
		printf("{\\textsubscript{%s}}", yytext+5);
}

"<ol>" {
	/*
	 * Matched an ordered list tag.  Enter the OL state.  Begin
	 * enumeration in LaTeX.
	 */
	printf("\\begin{enumerate}\n");
	BEGIN OL;
}

"<ul>" {
	/*
	 * Mathched an unordered list tag.  Enter the UL state.  Begin
	 * itemization in LaTeX.
	 */
	printf("\\begin{itemize}\n");
	BEGIN UL;
}

<UL>"</ul>" {
	/*
	 * Matched an end of unordered list tag.  Close the itemization.
	*/
	printf("\\end{itemize}\n");
	BEGIN 0;
}

<UL>"<li>" {
	/*
	 * Matched a list item, begin unordered list item block.
	 */
	printf("\\item ");
	BEGIN LIU;
}

<OL>"</ol>" {
	/*
	 * Matched an end of ordered list tag.  Close the enumration.
	 */
	printf("\\end{enumerate}\n");
	BEGIN 0;	// Return to normal parsing.
}

<OL>"<li>" {
	/*
	 * Matched a list item, begin ordered list item block
	 */
	printf("\\item ");
	BEGIN LIO;
}

<LIO>"</li>" {
	/*
	 * Matched end of this list item.  Return to OL.
	 * Since LaTeX doesn't have a great way to delimit items beyond
	 * declaring a new item or ending the list structure, we just hope the
	 * input HTML isn't too tricky (for example, raw text is allowed
	 * within an <ol> structure outside of an <li> clause)  
	 */
	printf("\n");
	BEGIN OL;
}

<LIU>"</li>" {
	/*
	 * Matched end of this list item.  Return to UL.
	 * Since LaTeX doesn't have a great way to delimit items beyond
	 * declaring a new item or ending the list structure, we just hope the
	 * input HTML isn't too tricky (for example, raw text is allowed
	 * within an <ul> structure outside of an <li> clause)  
	 */
	printf("\n");
	BEGIN UL;
	
}

%%

/**************************************************************************
 * The main function for the HTML to LateX converter. Here we do three
 * things:
 *  1. Print out the LateX document header.
 *  2. Invoke the lexer to print out the LateX document
 *  3. Print out the LateX footer.
 *************************************************************************/
int main( int argc, const char *argv[] ) {
// Document preamble
	printf( "\\documentclass[12pt]{article}\n" );
	printf( "\\usepackage{fixltx2e}\n" );
	printf( "\n" );
	printf( "\\setlength{\\parindent}{0.0in}\n" );
	printf( "\\setlength{\\parskip}{0.125in}\n" );
	printf( "\n\n" );
	printf( "\\begin{document}\n" );
// Document Begin
// Call lexer
	yylex();
// Document End
	printf( "\\end{document}\n" );
	return 0;
}
