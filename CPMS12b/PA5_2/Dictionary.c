#include "dictionary.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

//-----------------------------------------------------------------------------
// Dictionary.c
// source file for the Dictionary ADT
//-----------------------------------------------------------------------------

// Dictionary
// Exported reference type
//typedef struct DictionaryObj* Dictionary;

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

// hasgObj
typedef struct DictionaryObj{
	Node *table;
	int numItems;
}  DictionaryObj;

// Private Hash Functions -------------------------------------------------------

const int tableSize = 101;

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
   if ( shift == 0 )
      return value;
   return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
   unsigned int result = 0xBAE86554;
   while (*input) { 
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
   return pre_hash(key)%tableSize;
}

// showBits()
// print out the bits in an unsigned int
void showBits(unsigned int x) {
   int i;
   int sizeInBits = 8*sizeof(unsigned int);
   char symbol[2] = {'0','1'};
   char* binary = malloc(sizeInBits + 1);

   memset(binary, 0, sizeInBits + 1);

   for (i=0; i<sizeInBits; i++) {
       binary[sizeInBits-i-1] = symbol[(x>>i) & 0x01];
   }
   
   printf("%s\n", binary);
   free(binary);
}


// Public -----------------------------------------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void)
{
	Dictionary thisDict = (Dictionary)malloc(sizeof(DictionaryObj));
	thisDict->table = (Node*)calloc(tableSize, sizeof(NodeObj));
	assert(thisDict!=NULL);
	int i = 0;
	for(i=0; i < tableSize; i++)
		assert(thisDict->table[i]!=NULL);
	thisDict->numItems = 0;
	return thisDict;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD)
{
	makeEmpty(pD);
	free(pD);
}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D)
{
	if(D->numItems == 0) return 1;
	return 0;
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D)
{
	return D->numItems;
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no 
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k)
{
	int index = hash(k);
	Node pN = D->table[index];
	while(pN!=NULL){
		if(strcmp(pN->key, k) == 0){
			return pN->value;
		} else {
			pN = pN->next;
		}
	}
	return NULL;
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v)
{
	int index = hash(k);
	Node pN = D->table[index];
	while(pN!=NULL){
		pN = pN->next;
	}
	pN = newNode(k, v);
	D->numItems++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k)
{
	int index = hash(k);
	Node pN = D->table[index];
	if(strcmp(pN->key, k) == 0){
		D->table[index] = D->table[index]->next;
		free(pN);
		D->numItems--;
	}
	while(pN->next!=NULL){
		if(strcmp(pN->next->key, k) == 0){
			Node temp = pN->next;
			pN->next = pN->next->next;
			free(temp);
			D->numItems--;
		} else {
			pN = pN->next;
		}
	}
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D)
{
	int i = 0;
	for(i=0; i<tableSize; i++){
		Node pD = D->table[i];
		while(pD!=NULL){
			Node pN = pD->next;
			free(pD);
			pD = pN;
		}
	}
	D->numItems = 0;
}

// printDictionary()
// pre: none
// prints a text representation of D to the file pointed to by out
void printDictionary(FILE* out, Dictionary D)
{
	int i = 0;
	for(i=0; i<tableSize; i++){
		Node pN = D->table[i];
		while(pN!=NULL){
			fprintf(out, "key: %s value: %s", D->table[i]->key, D->table[i]->value);
			pN = pN->next;
		}
	}
}

