#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

//we can theoratically prevent a call if the string is all '
//still 'unlikely' so idc for now
int filter(wrd *word)
{
	char *buf = malloc(word->len * sizeof(char));

	int i=0, ii=0, legalchcnt = 0;//legal chracter count
	//ii is the shift and i is the write index
	//their sum is the read index
	for(;(i+ii)<(word->len);i++)
	{
		if (word->str[i+ii]=='\''){ii++;i--;}
		else{
			buf[i] = word->str[i+ii];
			legalchcnt++;
		}
	}
	//if (word->assigned)free(word->str);//untested and unnecessary in this case
	//word->assigned = 0;unnecessary becaue of the lines below
	//word->assigned = 1;
	
	if (legalchcnt){
		word->len = i;
		word->str = buf;
	}
	else {
		free(buf);
	}

	return legalchcnt;
}

wrd *locate(wrd *buf, int *wordcnt, int *charcnt, byte ignorequote)
{
	int len = buf->len;
	char *str = buf->str;
	wrd *words = malloc((len/2) * sizeof(wrd));//maximum word entries possible
	//for(int i=0;i<(len/2);i++)words[i].assigned = 0;

	char *tmp;
	unsigned char shouldfilter = 0;//a flag to call filter once per "unfiltered" word
	char islastlegal = 0;//a flag to check wether this is a new word or not//
	int wordcounter = 0, chcnter = 0;//charcount-er
	//filter and tracker loop
	for (;chcnter<len;chcnter++)
	{
		if (str[chcnter]>='a'&&str[chcnter]<='z');
		//else if (str[chcnter]>='A'&&str[chcnter]<='Z'){
		//	str[chcnter]+='a'-'A';
		//}
		else if (str[chcnter]=='\'')shouldfilter = 1;
		else{
			//hacks can suck a lot..the hack is now more complicated than
			//the straightforward option
			if (shouldfilter&&ignorequote) {
				if(!filter(&words[wordcounter-1])){
					wordcounter--;
				}
				//shouldfilter = 0;
			}
			//constructing from word prototypes(see below for context)
			else if(islastlegal){
				tmp = malloc(words[wordcounter-1].len * sizeof(char));
				memcpy(tmp, words[wordcounter-1].str, words[wordcounter-1].len);
				words[wordcounter-1].str = tmp;
				//words[wordcounter-1].assigned = 1;
			}
			
			islastlegal = 0;
			continue;
		}
		//constructing a wrd prototype
		//(wrd has two uses in this function)
		if (!islastlegal){
			shouldfilter = 0;
			words[wordcounter].str=&str[chcnter];
			words[wordcounter].len = 1;
			wordcounter++;
		}
		else
			words[wordcounter-1].len++;//

		islastlegal = 1;
	}

	//ignore a possibly incomplete word
	if (islastlegal)wordcounter--;
	//set "requested" values
	*charcnt = chcnter;
	*wordcnt = wordcounter;
	//realloc might move the memory
	wrd *res = realloc(words, sizeof(wrd) * wordcounter);
	return res;
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
