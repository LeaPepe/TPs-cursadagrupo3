#include "functions.h"

// funciones matematicas 

float sum(float *var1,float *var2)
{
	return *var1 + *var2;
}

float prod(float *var1, float *var2)
{
	return (*var1)*(*var2);
}

//typedef enum{false,true}bool ;
//typedef enum{sum,prod}option_t ;

// validaciones

// retorna un TRUE cundo el str es un numero y considera el signo, usar atof ????

bool validate_number(char *str)
{
    bool condition = true ;
    unsigned int index = 0 ;

    if( isdigit(str[index]) == 0 )   // no es un numero ??
    {
    	if( str[index]!='-' ) { return false ;}        // no es el signo negativo ?
    }
    while( str[++index] != '\0')
    {
        if( isdigit(str[index])==0 )
        {
            if( str[index]!='.' ){ condition=false ; break ;}
        }
    }

    return condition ;
}

// valida si es un string de char 
bool validate_alphabet(char *str)
{
    bool condition = true ;
    unsigned int index =0 ;

    while( str[index] != '\0')
    {
        if(isalpha(str[index])!=0 ) ++index ;
        else {condition= false ; break ;}
    }

    return condition ;
}

// retorna un true cuando el str es  "sum" o "prod" las dos unicas opciones validas
bool validate_option(char *str){

    bool condition = false ;

    if(strcmp(str,MENU_OPTION_SUM) != 0){
        if(strcmp(str,MENU_OPTION_PRODUCT) != 0 ){condition = false ;}
        else condition=true ;
    }
    else condition = true ;

    return condition;
}
