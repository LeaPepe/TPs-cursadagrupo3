#include "pila.h"


Node* buildNode(float  value){
	Node *node = (Node *)malloc(sizeof(Node)) ;
	node->value = value ;
	node->next = NULL;
	return node;
}

// destruct node
bool destructNode(Node *node){
	node->next = NULL;
	free(node) ;
	return true;
}

//to push 
bool push(Pila *pila, float value){
	Node *node = buildNode(value);
	node->next = pila->first ; 	// apilo
	pila->first = node ;       	// puntero al ultimo
	pila->size ++ ;	 	   	// agredo un nodo +
	return true;
}

//to pop - eliminar un nodo -
bool pop(Pila *pila){
	if(pila->first !=NULL){
		Node *freeNode = pila->first ;  // desengancho el nodo a eliminar
		pila->first = pila->first->next ; // apunto al siguiente
		destructNode(freeNode) ;    //borro el nodo
	}

	pila->size -- ;  // decremento un node
	return true;
}
// constructor de la pila
Pila*  buildPila(Pila *pila){
	pila= (Pila *)malloc(sizeof(Pila)) ;
	if(pila!=NULL){
		pila->first = NULL ;
		pila->size = 0 ;
	}
	return pila;  // una pila vacia, sin nodo
}

// destructor de la pila
void destructPila(Pila* pila){
	while(pila->first != NULL ){ pop(pila); }
	free(pila) ;  // elimino la pila vacia !
}

float sumPila(Pila* pila){
	float sum = 0 ;
	Node *node = pila->first ;    // nodo auxiliar para moverme por la pila
		//printf("%.6f \n ",nodo->value) ;
	while(node->next != NULL ){
		sum = sum + node->value  ;
		node = node->next ;
	}
	return sum + node->value ; // me flato el ulimo nodo
}

double prodPila(Pila* pila){
	double prod = 1 ;
	Node *node = pila->first ;
	while(node->next != NULL ){
		prod = prod*node->value  ;
		node = node->next ;
	}
	return prod*node->value ; // me falto el ulimo nodo.
}
