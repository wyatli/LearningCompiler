/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>
/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */

%}

/*
 * Define names for regular expressions here.
 */
%x COMMENT1 COMMENT2 STRING
	int nested ;
	int str_counter;

DARROW          =>
LE <=
ASSIGN =

CLASS [cC][lL][aA][sS][sS]
ELSE [eE][lL][sS][eE]
FI [fF][iI]
IF [iI][fF]
IN [iI][nN]
INHERITS [iI][nN][hH][eE][rR][iI][tT][sS]
ISVOID [iI][sS][vV][oO][iI][dD]
LET [lL][eE][tT]
LOOP [lL][oO][oO][pP]
POOL [pP][oO][oO][lL]
THEN [tT][hH][eE][nN]
WHILE [wW][hH][iI][lL][eE]
CASE [cC][aA][sS][eE]
ESAC [eE][sS][aA][cC]
NEW [nN][eE][wW]
OF [oO][fF]
NOT [nN][oO][tT]
TRUE t[rR][uU][eE]
FALSE f[aA][lL][sS][eE]

%%

 /*
  *  Nested comments
  */

"(*" { BEGIN(COMMENT1); nested = 1; }
"*)" { cool_yylval.error_msg = "Unmatched *)"; return ERROR; }
<COMMENT1>"(*" {nested++;}
<COMMENT1>"*)" {if (--nested==0) BEGIN (INITIAL);}

<COMMENT1>. { }
<COMMENT1><<EOF>> {
	BEGIN(INITIAL);
	cool_yylval.error_msg = "EOF in comment";
	return ERROR;
}
--	BEGIN(COMMENT2);
<COMMENT2>\n {
	curr_lineno ++;
	BEGIN(INITIAL);
}


 /*
  *  The multiple-character operators.
  */
{DARROW}		{ return (DARROW); }
{LE} 			{return(LE);}
{ASSIGN}		{return(ASSIGN);}

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */
{CLASS}		{ return CLASS; }
{ELSE} 		{ return ELSE; }
{FI} 		{ return FI; }
{IF} 		{ return IF; }
{IN} 		{ return IN; }
{INHERITS}	{ return INHERITS; }
{ISVOID} 	{ return ISVOID; }
{LET} 		{ return LET; }
{LOOP} 		{ return LOOP; }
{POOL} 		{ return POOL; }
{THEN} 		{ return THEN; }
{WHILE} 	{ return WHILE; }
{CASE} 		{ return CASE; }
{ESAC} 		{ return ESAC; }
{NEW} 		{ return NEW; }
{OF} 		{ return OF; }
{NOT} 		{ return NOT; }

 {TRUE}		{cool_yylval.boolean = true; return BOOL_CONST;}
{FALSE}		{cool_yylval.boolean = false;return BOOL_CONST;}

 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */
  "\""	{
  	BEGIN(STRING);
  	str_counter = 0;
  	string_buf_ptr = string_buf;
  }
<STRING>\\. {
  	if (str_counter + 1 == MAX_STR_CONST)
  	{
  		BEGIN(INITIAL);
  		cool_yylval.error_msg = "String constant too long";
  		return ERROR;
  	}
  	char c;
  	
  	switch((c = yytext[1]) ) {
  		case 'b':
			string_buf[str_counter++] = '\b';
			break;
		case 't':
			string_buf[str_counter++]  = '\t';
			break;
		case 'n':
			string_buf[str_counter++] = '\n';
			break;
		case 'f':
			string_buf[str_counter++] = '\f';
			break;
		case '\0':
			BEGIN(INITIAL);
  			cool_yylval.error_msg = "String contains null character";
  			return ERROR;
		default:
			string_buf[str_counter++] = c;
			break;
  	}
  }
<STRING><<EOF>> {
  	BEGIN(INITIAL);
  	cool_yylval.error_msg = "EOF in string";
  	return ERROR;
 }


<STRING>\n {
	BEGIN INITIAL;
	curr_lineno++;
	cool_yylval.error_msg = "Unterminated string constant";
	return ERROR;
}
<STRING>. {
  	if (str_counter + 1 == MAX_STR_CONST)
  	{
  		BEGIN(INITIAL);
  		cool_yylval.error_msg = "String constant too long";
  		return ERROR;
  	}
  	string_buf[str_counter++] = yytext[0];
  }
<STRING>"\"" {
	BEGIN(INITIAL);
	cool_yylval.symbol = stringtable.add_string(string_buf);
	return STR_CONST;
}
[0-9]+ {
    cool_yylval.symbol = inttable.add_string(yytext);
    return INT_CONST;
}
[a-z][a-zA-Z0-9_]* {
	cool_yylval.symbol = idtable.add_string(yytext);
	return OBJECTID;
}
[A-Z][a-zA-Z0-9_]* {
	cool_yylval.symbol = idtable.add_string(yytext);
	return TYPEID;
}
\n {
	curr_lineno ++;
}
[ \f\r\t\v] ;
[-+*/~<\(\){}@=\.,:;] { return yytext[0]; }

%%
