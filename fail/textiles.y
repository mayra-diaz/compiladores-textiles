%{
#include <stdio.h>

int yylex();
int yyerror(char *s);

%}

%token a sh1 sh2 sh3 sh4 sh5 sv1 sv2 sv3 sv4 sv5 n1 n2 n3 n4 n5 ac1 ac2 ac3 ac4 c1 c2 c3 c4 af

%%

I:
        | S
;

S:
        | a A
;

A: 	
 	sh1 SH1
 	| sh2 SH2
	| sh3 SH3
	| sh4 SH4
	| sh5 SH5
;

SH1:	
  	 sv1 SV1
   	| sv2 SV2
	| sv3 SV3
;

SH2: 	
   	sv1 SV1
   	| sv2 SV2
;

SH3: 	
   	sv1 SV1
   	| sv2 SV2
	| sv3 SV3

;

SH4: 	
   	sv3 SV3
   	| sv4 SV4
	| sv5 SV5
;

SH5: 	
   	sv3 SV3 
   	| sv5 SV5
;

SV1: 	
   	n1 N1
   	| n2 N2
   	| n3 N3
;

SV2: 	
   	n1 N1
   	| n2 N2
   	| n3 N3
;

SV3: 	
   	n4 N4
   	| n5 N5
;

SV4: 	
   	n4 N4
   	| n5 N5
;

SV5: 	
   	| n5 N5
;

N1: 	
  	ac1 AC1
	| ac2 AC2

;

N2: 	
  	ac1 AC1
	| ac2 AC2 
	| ac3 AC3
;

N3: 	
  	ac2 AC2
	| ac3 AC3
	| ac4 AC4
;

N4: 	
  	ac2 AC2
  	| ac3 AC3
	| ac4 AC4
;

N5: 
  	| ac4 AC4

;

AC1: 
   	c1 C1
   	| c2 C2
	| c3 C3

;

AC2: 	
   	c1 C1
	| c2 C2
   	| c3 C3
;

AC3: 
   	c1 C1
	| c2 C2
	| c3 C3
;

AC4: 
   	| c4 C4
;

C1: 
  	| c2 C2
;

C2: 
  	| c4 C4
;

C3: 
	| af
;

C4:
    	| af
;

%%

int yyerror(char *s) {
	printf("Error: %s\n", s);
	return 0;
}

int main() {
    yyparse();
    return 0;
}
