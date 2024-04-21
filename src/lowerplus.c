#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

//an interesting abstraction to say the least
char *lowerplus(char *str, int *length, byte lwr)
{
	int len = *length;

	char *todecode = malloc(2 * len * sizeof(char));
        memset(todecode+len, ' ', len * sizeof(char));

	for(int i=0;i<len;i++)
	{
		if(str[i]>='A'&&str[i]<='Z'&&lwr)
			todecode[i]=str[i]+'a'-'A';
		else
			todecode[i]=str[i];
	}

	*length = len * 2;
	return todecode;
}

/*
int main(int argc, char **argv)
{
	int len = strlen(argv[1]);
	char *lowered = lowerplus(argv[1], &len);
	printf("%.*s\n", len, lowered);
	
	free(lowered);
	return 0;
}
*/
