%{
#include "y.tab.h"
int etapas = 0;
%}

a           "A"

sh1         "Sh1"
sh2         "Sh2"
sh3         "Sh3"
sh4         "Sh4"
sh5         "Sh5"

sv1 	    "Sv1"
sv2	        "Sv2"
sv3 	    "Sv3"
sv4	        "Sv4"
sv5	        "Sv5"

n1          "N1"
n2          "N2"
n3		    "N3"
n4		    "N4"
n5          "N5"

ac1 	    "Ac1"
ac2 	    "Ac2"
ac3 	    "Ac3"
ac4         "Ac4"

c1          "C1"
c2          "C2"
c3		    "C3"
c4		    "C4"

%%

{a}		    {
                ++etapas; 
                if (etapas > 1)
                    return a;
                return AF;    
            }

{sh1}       {++etapas; return sh1;}
{sh2}       {++etapas; return sh2;}
{sh3}       {++etapas; return sh3;}
{sh4}       {++etapas; return sh4;}
{sh5}       {++etapas; return sh5;}

{sv1}       {++etapas; return sv1;}
{sv2}       {++etapas; return sv2;}
{sv3}       {++etapas; return sv3;}
{sv4}       {++etapas; return sv4;}
{sv5}       {++etapas; return sv5;}

{n1}        {++etapas; return n1;}
{n2}        {++etapas; return n2;}
{n3}        {++etapas; return n3;}
{n4}        {++etapas; return n4;}
{n5}        {++etapas; return n5;}

{ac1}       {++etapas; return ac1;}
{ac2}       {++etapas; return ac2;}
{ac3}       {++etapas; return ac3;}
{ac4}       {++etapas; return ac4;}

{c1}        {++etapas; return c1;}
{c2}        {++etapas; return c2;}
{c3}        {++etapas; return c3;}
{c4}        {++etapas; return c4;}

.    		{return OTHER;}

%%

int yywrap(void){
    return 1;
}