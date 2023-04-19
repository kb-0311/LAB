%{
int num_vowels = 0;
int num_consonants = 0;
int num_sentences = 0;
%}

%%
[aAeEiIoOuU]  { num_vowels++; }
[B-DF-HJ-NP-TV-Zb-df-hj-np-tv-z]  { num_consonants++; }
.  ;  /* Ignore all other characters */
%%
yywrap() {}
int main()
{
    yylex();
    printf("Number of vowels: %d\n", num_vowels);
    printf("Number of consonants: %d\n", num_consonants);
    printf("Number of sentences: %d\n", num_sentences);
    return 0;
}