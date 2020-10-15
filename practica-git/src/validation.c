#include "validation.h"

// Validaciones !!

bool isNumber(char *str){
    
    bool condition = true ;
   // unsigned int index = 0 ;

/*    if( isdigit(str[index]) == 0 )   // no es un numero ??
    {
    	if( str[index]!='-' ) { return false ;}        // no es el signo negativo ?
    }
    while( str[++index] != '\0')
    {
        if( isdigit(str[index])==0 )
        {
            if( str[index]!='.' ){ condition=false ; break ;}
        }
    } */
    if( atof(str)==0){ condition = false;}
   

    return condition ;
}

bool isAlphabet(char *str){

    bool condition = true ;
    unsigned int index =0 ;

    while( str[index] != '\0')
    {
        if(isalpha(str[index])!=0 ) ++index ;
        else {condition= false ; break ;}
    }

    return condition ;
}


bool isOption(char *str){

    bool condition = false ;

    if(strcmp(str,MENU_OPTION_SUM) != 0){
        if(strcmp(str,MENU_OPTION_PRODUCT) != 0 ){condition = false ;}
        else condition=true ;
    }
    else condition = true ;

    return condition;
}

