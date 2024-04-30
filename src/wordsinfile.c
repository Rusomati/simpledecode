#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "common.h"

void wordsinfile(wifargs *args, wrd *words, int *count, int bufsize)
{
	wrd *res = args->words;
	wrd *fileword = args->fileword;
	char *buf = args->buf;

	FILE *fp = args->fp;
	int fsize = args->fsize;

	int cnt = *count;
	//initialising 'results'
	//wrd *res = malloc(cnt * sizeof(wrd));
	int writeindex = 0;

	//char *buf = malloc(bufsize * sizeof(char));
	//wrd *fileword = makewrd(NULL, bufsize/2);

	for(int i=0;i<cnt;i++)
	{
		//binary search stuff
		int delta = fsize/2, pos = delta;
		int tomove = -1, moved;//to check if the search would repeat forever
		int wordpos = 0;
		int charactertohit;//the index of the character that wouldvbeen hit 
				   //in the word got by the last getword call
				   //used to skip unnecessary getword calls
				   //probably not the best way but i dont care rn
		while(1)
		{
			moved = tomove;
			delta = (delta+1)/2;
			charactertohit = pos - wordpos;
			
			if (charactertohit>fileword->len || charactertohit<0)
			{
				wordpos = getword(pos, fp, fileword, buf, fsize, bufsize);
				tomove = comparewrd(&words[i], fileword) * delta;
				//^^ comparewrd returns -1 if a word 'should appear earlier'
			}
			
			pos += tomove;

			if(!tomove){
				res[writeindex].len = words[i].len;
				res[writeindex].str = words[i].str;
				writeindex++;
				break;
			}

			if(!(tomove+moved) || wordpos<0){
				//free(words[i].str);
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				break;
			}
		}
	}

	//free(buf);
	//freewrd(fileword, 1);
	//free(words);//does not free the strings

	*count = writeindex;
	//res = realloc(res, *count * sizeof (wrd));
	//return res;
}

void wordsinfilepre(wifargs *args, int bufsize, wrd *words, byte ignorequotes)
{	
	//(mostly) initialising stuff for getword
	char pathnq[] = "../newerdict.txt";
	char pathq[] = "../newdict.txt";
	char *path = (ignorequotes)?pathnq:pathq;

        int fd = open(path, O_RDONLY);
	struct stat filestat;
	fstat(fd, &filestat);
	args->fsize = filestat.st_size;

	wrd *tmp = malloc(sizeof(wrd));
	tmp->len = bufsize/2;
	args->fileword = tmp;
	args->buf = mmap(NULL, args->fsize, PROT_READ, MAP_SHARED, fd, 0);
	args->words = words;
}

void wordsinfilefree(wifargs *args)
{
	munmap(args->buf, args->fsize);
	free(args->fileword);
}

/*
int main(int argc, char **argv)
{
	int bufsize = 150;
	int count = argc - 1;//ignoring 'programs name'
	wrd *words = malloc(count * sizeof(wrd));

	for (int i=0;i<count;i++)
	{
		words[i].len = strlen(argv[i+1]);
		//words copied just in case..
		//also is this allocation efficient
		words[i].str = malloc(words[i].len * sizeof(char));
		memcpy(words[i].str, argv[i+1], words[i].len);
	}

	words = wordsinfile(words, &count, bufsize);

	for (int i=0;i<count;i++)
		printf("%.*s\n", words[i].len, words[i].str);

	freewrd(words, count);
	return 0;
}
*/
