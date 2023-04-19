%option noyywrap
%{
#include "y.tab.h"
extern int yylval;
%}
%%
[0-9]+ {yylval=atoi(yytext); return ID;}
\n         { return 0;}
[ \t\r]     ;
. r