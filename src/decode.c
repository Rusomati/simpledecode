#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

//optimise
void decode(char * text, int len, int origlen, int offset, char *res, int *reslen)
{
	int rem = (len%offset)?(offset-(len%offset)):0;//
	int prevlen = len;
	len+=rem;
	int windex = 0;

	//for (int i=0;i<offset;i++)
	for(int i=0;windex<prevlen;i++)
		for (int ii=i;ii<origlen&&windex<prevlen;){
			res[windex] = text[ii];
			ii+=offset;
			windex++;
	}

	*reslen = windex;
}

/*
int main()
{
	char prompt[] = "Spiheayaaitoviakoplfasesreupleyi   s y   ttym h l";

	int lenn = strlen(prompt);
	char *todecode = lowerplus(prompt, &lenn);
	int len = lenn/2;

	char *res = malloc(2 * len * sizeof(char));
	int reslen;

	//len can be "halfed" under assumptions
	for (int i=2;i<len;i++)
	{
		decode(todecode, len, i, res, &reslen);//key = 'len'/i
		printf("%.*s\n", reslen, res);
	}

	free(todecode);	
	free(res);
	return 0;
}
*/
