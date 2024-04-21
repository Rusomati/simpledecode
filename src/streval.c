#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"
//implement a faster power function
unsigned long long streval(wrd *words, int cnt, int chars)
{
	long long res = 0;

	for (int i=0;i<cnt;i++)
	{
		if(words[i].len<2);
		else if (words[i].len<4)res+=1;
		else
			res+=(1 << words[i].len);
	}

	return res * 20 /chars;
}

/*
int main(int argc, char **argv)
{
	int cnt = argc - 1;
	wrd* words = malloc(cnt * sizeof(wrd));

	for (int i=0;i<cnt;i++)
	{
		words[i].len = strlen(argv[i+1]);
		words[i].str = malloc(words[i].len * sizeof(char));
		memcpy(words[i].str, argv[i+1], words[i].len);
	}

	printf("%d\n", streval(words, cnt));

	freewrd(words, cnt);
	return 0;
}
*/
