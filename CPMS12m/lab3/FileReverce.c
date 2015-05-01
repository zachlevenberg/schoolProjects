#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StringReverse(char* w);

int main(int argc, char*argv[]){
	FILE* in;
	FILE* out;
	char word[256];

	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	in = fopen(argv[1], "r");
	if(in == NULL){
		printf("Unable to read from file %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	out = fopen(argv[2], "w");
	if(out == NULL){
		printf("Unable to write to file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while(fscanf(in, " %s", word) != EOF){
		StringReverse(word);
		fprintf(out, "%s\n", word);
		}

	fclose(in);
	fclose(out);

	return(EXIT_SUCCESS);
}

void StringReverse(char* w)
{
	int length = strlen(w);
	char temp[length];
	int i = 0;
	for(i = 0; i < length; i++){
		temp[i] =w[length - 1 - i];
	}
	for(i = 0; i < length; i++){
		w[i] = temp[i];
	}
}
