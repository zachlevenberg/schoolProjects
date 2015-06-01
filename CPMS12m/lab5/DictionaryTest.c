//-----------------------------------------------------------------------------
//Zachary Levenberg
//ID: 1049451
//12m
//5/7/15
//This file tests the Dictionary key-value abstract data type 
//DictionaryTest.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 180

int main(int argc, char* argv[]){

	//printf("HelloWorld");//debug
	Dictionary A = newDictionary();
	//printf("Dictionary added\n");//debug
	char* k;
	char* v;
	char* word1[] = {"one","two","three","four","five","six","seven"};
	char* word2[] = {"foo","bar","blah","galumph","happy","sad","blue"};
	int i;
	
	insert(A, word1[0], word2[0]);
	printDictionary(stdout, A);
	delete(A, "one");
	printDictionary(stdout, A);
	printf("size: %d", size(A));
	makeEmpty(A);

	insert(A, word1[0], word2[0]);
	printDictionary(stdout, A);
	freeDictionary(&A);
	A = newDictionary();



	for(i=0; i<7; i++){
		insert(A, word1[i], word2[i]);
	}
	//printf("keys inserted\n");//debug
	printDictionary(stdout, A);
	

	for(i=0; i<7; i++){
		k = word1[i];
		v = lookup(A, k);
		printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
	}
	
	// insert(A, "five", "glow"); // error: key collision

	delete(A, "one");
	delete(A, "three");
	delete(A, "seven");

	printDictionary(stdout, A);
	
	for(i=0; i<7; i++){
		k = word1[i];
		v = lookup(A, k);
		printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
	}
	//return(EXIT_SUCCESS);
	 //delete(A, "one");  // error: key not found

	printf("%s\n", (isEmpty(A)?"true":"false"));
	printf("%d\n", size(A));
	makeEmpty(A);
	printf("%s\n", (isEmpty(A)?"true":"false"));

	freeDictionary(&A);

	return(EXIT_SUCCESS);
}
