#ifndef __PILA__
#define	__PILA__

#include <stdio.h>
#include <stdbool.h>
#include "validation.h"

// lista enlazada :
typedef struct node{
	float value ;
	struct node* next;
}Node;

// pila :
typedef struct pila{
	Node *first;
	unsigned int size;  // saber la cantidad de nodos
}Pila ;


Node* buildNode(float  value);
bool destrucNode(Node *node);
bool push(Pila *pila, float value);
bool pop(Pila *pila);
Pila*  buildPila(Pila *pila);
void destructPila(Pila* pila);
float sumPila(Pila* pila) ;
double prodPila(Pila* pila);



#endif
