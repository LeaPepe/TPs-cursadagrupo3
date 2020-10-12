#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../inc/validation.h"

#define MENU_OPTION_SUM "sum"
#define MENU_OPTION_PRODUCT "prod"


//typedef enum{false,true}bool_t ;

// Validaciones !!

bool_t isNumber(char *str){
    
    bool_t condition = true ;
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

bool_t isAlphabet(char *str){

    bool_t condition = true ;
    unsigned int index =0 ;

    while( str[index] != '\0')
    {
        if(isalpha(str[index])!=0 ) ++index ;
        else {condition= false ; break ;}
    }

    return condition ;
}


bool_t isOption(char *str){

    bool_t condition = false ;

    if(strcmp(str,MENU_OPTION_SUM) != 0){
        if(strcmp(str,MENU_OPTION_PRODUCT) != 0 ){condition = false ;}
        else condition=true ;
    }
    else condition = true ;

    return condition;
}

