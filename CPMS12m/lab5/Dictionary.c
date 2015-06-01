//-----------------------------------------------------------------------------
//Zachary Levenberg
//ID: 1049451
//12m
//5/7/15
//This file implements a Dictionary key-value abstract data type 
//Dictionary.c
// Dictionary ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "Dictionary.h"


// Private --------------------------------------------------------------------

// NodeObj
typedef struct NodeObj{
	char* key;
	char* value;
	struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(char* key, char* value) {
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->key = key;
	N->value = value;
	N->next = NULL;
	return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node *pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}

// StackObj
typedef struct DictionaryObj{
	Node top;
	int numItems;
}  DictionaryObj;


// Public -----------------------------------------------------------------------



// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void){
	//printf("\nNew Dictionary....\n");
	Dictionary D = (Dictionary)(malloc(sizeof(DictionaryObj)));
	assert(D!=NULL);
	D->top = NULL;
	D->numItems = 0;
	return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD){
	if(pD!=NULL && *pD!=NULL){
		makeEmpty(*pD);
		free(*pD);
	} else {
		printf("Dictionary Error: freeDictionary() called on NULL dictionary \n");
		exit(EXIT_FAILURE);
	}

}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
	if(D == NULL){
		printf("Dictionary Error: isEmpty() called on NULL dictionary \n");
		exit(EXIT_FAILURE);
	}
	if(D->numItems == 0){
		return 1;
	} else {
		return 0;
	}
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D){
	if(D == NULL){
		printf("Dictionary Error: size() called on NULL dictionary \n");
		exit(EXIT_FAILURE);
	}
	return D->numItems;
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no 
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k){
	if(D == NULL){
		printf("Dictionary Error: lookup() called on NULL dictionary \n");
		exit(EXIT_FAILURE);
	}
	assert(D!=NULL);
	Node S = D->top;
	if(S == NULL){
		return NULL;
	}
	do {
		if(strcmp(S->key, k) == 0){
			return S->value;
		}
		S = S->next;
	} while(S!= NULL);
	return NULL;
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v){
	if(D == NULL){
		printf("Dictionary Error: insert() called on NULL dictionary \n");
		exit(EXIT_FAILURE);
	}
	if(lookup(D, k) == NULL){
		if(D->top == NULL){
			D->top = newNode(k, v);
			D->numItems++;
		} else {
			Node S = D->top;
			while(S->next != NULL){
				S = S->next;
			}
			S->next = newNode(k, v);
			D->numItems++;
		}
	} else{
		printf("Dictionary Error: Key collision detected\n");
		exit(EXIT_FAILURE);
	}
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k){
	if(D == NULL){
		printf("Dictionary Error: delete() called on NULL dictionary \n");
		exit(EXIT_FAILURE);
	}
	if(lookup(D, k)!= NULL){
		Node P = D->top;
		if(strcmp(P->key, k) == 0){
			D->top = P->next;
			freeNode(&P);
			D->numItems--;
		} else {
		Node S = P;
		P = P->next;
		while(strcmp(P->key, k)){
			S = P;
			P = P->next;
		}
		S->next = S->next->next;
		freeNode(&P);
		D->numItems--;
		}
	} else {
		printf("Dictionary Error: Key not found\n");
		exit(EXIT_FAILURE);
	}
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D){
	if(D == NULL){
		printf("Dictionary Error: makeEmpty() called on NULL dictionary \n");
		exit(EXIT_FAILURE);
	}
	if(D->top != NULL){
		Node S = D->top;
		D->top = NULL;
		while(S != NULL){
			Node P = S;
			S = S->next;
			freeNode(&P);
			D->numItems--;
		}
	}
}

// printDictionary()
// pre: none
// prints a text representation of D to the file pointed to by out
void printDictionary(FILE* out, Dictionary D){
	if(D == NULL){
		fprintf(stderr,"Dictionary Error: printDictionary() called on NULL dictionary \n");
		exit(EXIT_FAILURE);
	}
	Node S = D->top;
	while(S != NULL){
		fprintf(out, "%s %s\n", S->key, S->value);
		S = S->next;
	}
}
