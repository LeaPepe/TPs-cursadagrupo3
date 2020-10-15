//  ****** TP0 sistemas embebidos *****
#include "main.h"


void getString(char *str){
    char str2[MAX_SIZE_STRING] ;
    char ch ;
    unsigned int index = 0;

    while( (ch = getchar())!='\n' &&  index< MAX_SIZE_STRING ){ str2[index++]=ch;}
    str2[index]='\0';

    strcpy(str,str2) ;
}

float getResult(Pila *myPila, char *str)
{
    float result ;
    printf("option : %s \n",str) ;
    if(strcmp(str, MENU_OPTION_SUM) ==0 ) result = sumPila(myPila) ;
    else if(strcmp(str, MENU_OPTION_PRODUCT) ==0 ) result = prodPila(myPila) ;
    else
        result = 0 ;

    return result ;
}


void myApp(void){

	double result =0;
	char *str =  (char *)malloc(MAX_SIZE_STRING*sizeof(char)) ;

	Pila *myPila=NULL ; // Puntero a pila
	myPila = buildPila(myPila) ; // pila, instancias size = 0!

	do{
        	getString(str);
        	if(isNumber(str)!=false) push(myPila,atof(str)) ;
        	else{
            		if( isOption(str)!=false ) break ;
            		else printf("No es una opcion valida \n") ;
			}
    	}while(myPila->size < MAX_NODE) ;

    if(myPila->size > (MAX_NODE-1)){
    	printf("se ingresaron un maximo de N ( sum or prod)  :  \n") ;       
	do{
	   getString(str);
	   }while(isOption( str ) != true ) ;

    }
	result = getResult(myPila,str) ;
	printf("resultado: %.6f \n", result) ;
	// free memory 
	destructPila(myPila) ;
	free(str) ;

}

// main principal
int main(void){

	myApp() ;	
	return 0;
}