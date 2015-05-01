//-----------------------------------------------------------------------------
//Zachary Levenberg
//ID: 1049451
//12m
//4/28/15
//This program parses a file line by line, and creates
//a file with the listed content of each character in the file.
// alphaNum.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>

#define MAX_STRING_LENGTH 100

// function prototype 
void extract_chars(char* s, char* a, char*d, char*p, char*w);

// function main which takes command line arguments 
int main(int argc, char* argv[]){
	FILE* in;        // handle for input file                  
	FILE* out;       // handle for output file                 
	char* line;      // string holding input line              
	char* alpha; // string holding all alphabetic chars 
	char* digits;	 // string holding all numberic chars
	char* punc;		 // sting holding all punctuation
	char* white; 	 // string holding all whitespace chars

	// check command line for correct number of arguments 
	if( argc != 3 ){
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// open input file for reading 
	if( (in=fopen(argv[1], "r"))==NULL ){
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// open output file for writing 
	if( (out=fopen(argv[2], "w"))==NULL ){
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	// allocate strings on the heap 
	line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	digits = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	punc = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
	white = calloc(MAX_STRING_LENGTH+1, sizeof(char) );

	assert( line!=NULL && alpha!=NULL && digits!=NULL && punc!=NULL && white!=NULL);

	// read each line in input file, extract characters 
	int i = 1;
	while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
		fprintf(out, "%s\n", line);
		extract_chars(line, alpha, digits, punc, white);
		fprintf(out, "line %d contains:\n", i);
		fprintf(out, "%d alphabetic character%s %s\n", strlen(alpha), (alpha[1] == '\0') ? ":" : "s:", alpha);
		fprintf(out, "%d numeric character%s %s\n", strlen(digits), (digits[1] == '\0') ? ":" : "s:", digits);
		fprintf(out, "%d puntuation character%s %s\n", strlen(punc), (punc[1] == '\0') ? ":" : "s:", punc);
		fprintf(out, "%d whitespace character%s %s\n", strlen(white), (white[1] == '\0') ? ":" : "s:", white);
		i++;
	}

	// free heap memory 
	free(line);
	free(alpha);
	free(digits);
	free(punc);
	free(white);

	// close input and output files 
	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}

// function definition 
void extract_chars(char* s, char* a, char* d, char* p, char* w){
	int i=0, j=0, k=0, l=0, m=0;
	for(i = 0; i < strlen(s); i++){
		if( isalpha( (int)s[i]) ) a[j++] = s[i];
		if( isdigit( (int)s[i]) ) d[k++] = s[i];
		if( ispunct( (int)s[i]) ) p[l++] = s[i];
		if( isspace( (int)s[i]) ) w[m++] = s[i];
	}
	a[j] = '\0';
	d[k] = '\0';
	p[l] = '\0';
	w[m] = '\0';

}
