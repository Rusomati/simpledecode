//theorise(assign bit...)
//then test
//add features as requested or remake

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/*typedef struct {
	int len;
	char *str;
//	unsigned char assigned;
}wrd;*/

//batch word creation isnt needed rn
wrd *makewrd(char *string, int len)
{
	wrd *word = calloc(1, sizeof(wrd));

	if (string==NULL&&!len){
		fprintf(stderr, "too little arguments\n");
		exit(-1);
	}
	if (!len)len = strlen(string);

	word->str = calloc(len, sizeof(char));
	//word->assigned = 1;
	if (string!=NULL) memcpy(word->str, string, len);
	word->len = len;

	return word;
}

//assigned ignored rn..
void freewrd(wrd *words, int count)
{
	for (int i=0;i<count;i++){
		free(words[i].str);
	}
	free(words);
}

//expandword()//unnecessary 

/*
int main(int argc, char **argv)
{
	wrd *arg_one = makewrd(argv[1], 0);
	printf("%.*s\n", arg_one->len, arg_one->str);
	freewrd(&arg_one, 1);
	arg_one = NULL;
	return 0;
}
*/
