#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

//we can theoratically prevent a call if the string is all '
//still 'unlikely' so idc for now
int filter(wrd *word, wrd *buf, int *offset)
{

	int off = *offset;
	if (word->len+off > buf->len)
	{
		int newlength = buf->len;
		while(word->len + off > newlength)newlength*=4;
		buf->str = realloc(buf->str, newlength * sizeof(char));
		buf->len = newlength;
	}

	int i=0, ii=0, legalchcnt = 0;//legal chracter count
	char *tmp;
	//ii is the shift and i is the write index
	//their sum is the read index
	for(;(i+ii)<(word->len);i++)
	{
		if (word->str[i+ii]=='\''){ii++;i--;}
		else{
			buf->str[off+i] = word->str[i+ii];
			legalchcnt++;
		}
	}
	
	if (legalchcnt){
		word->str = &buf->str[off];
		word->len = i;
		*offset+=i;
		//printf("filtered word: %.*s\n", i, &buf->str[off]);
		//printf("%d\n", buf->len);
	}

	//printf("%d\n", buf->len);

	return legalchcnt;
}

void locate(locateargs *pointers, wrd *buf, int *wordcnt, int *charcnt, byte ignorequote)
{
	wrd *words = pointers->words;
	wrd *filterbuf = &pointers->filterbuf;//

	int len = buf->len;
	char *str = buf->str;

	char *tmp;
	int offset = 0;
	byte shouldfilter = 0;//a flag to call filter once per "unfiltered" word
	char islastlegal = 0;//a flag to check wether this is a new word or not//
	int wordcounter = 0, chcnter = 0;//charcount-er
	//filter and tracker loop
	for (;chcnter<len;chcnter++)
	{
		if (str[chcnter]>='a'&&str[chcnter]<='z');
		else if (str[chcnter]>='A'&&str[chcnter]<='Z'){
			//str[chcnter]+='a'-'A';
			;
		}
		else if (str[chcnter]=='\'')shouldfilter = 1;
		else{
			//hacks can suck a lot..the hack is now more complicated than
			//the straightforward option
			if (shouldfilter&&ignorequote) {

				if(!filter(&words[wordcounter-1], filterbuf, &offset)){
					wordcounter--;
				}
				shouldfilter = 0;
			}
			//constructing from word prototypes(see below for context)
			else if(islastlegal){
			}
			
			islastlegal = 0;
			continue;
		}
		//constructing a wrd prototype
		//(wrd has two uses in this function)
		if (!islastlegal){
			words[wordcounter].str=&str[chcnter];
			words[wordcounter].len = 1;
			wordcounter++;
		}
		else
			words[wordcounter-1].len++;

		islastlegal = 1;
	}
	
	//ignore a possibly incomplete word
	if (islastlegal)wordcounter--;

	//free(filterbuf);

	//set "requested" values
	*charcnt = chcnter;
	*wordcnt = wordcounter;

}

void locatepre(locateargs *args, int len)
{
	args->words = calloc((len/2),  sizeof(wrd));//maximum word entries possible
	args->filterbuf.len = 256;//temporary size?
	args->filterbuf.str = malloc(args->filterbuf.len * sizeof(char));
	//^^ resize when needed
}

void locatefree(locateargs *args)
{
	free(args->filterbuf.str);
}

/*
int main(int argc, char **argv)
{
	int len = strlen(argv[1]);
	wrd *word = makewrd(argv[1], len);
	int wrdcnt=0,charcnt=0;
	byte ignorequote = 1;

	wrd *words = locate(word, &wrdcnt,&charcnt, ignorequote);
	
	printf("word candidates:\n");
	for (int i=0;i<wrdcnt;i++)
	{
		printf("%.*s\n", words[i].len, words[i].str);
	}

	freewrd(word, 1);//set to null when done
	freewrd(words, wrdcnt);

	return 0;
}
*/
