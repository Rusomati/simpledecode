#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <common.h>

void decoderot(char *buf, char *str, int len, int key, byte capitaloff)
{
	for (int i=0;i<len;i++)
	{
		if (str[i]>='a'&&str[i]<='z')
			buf[i] = (str[i]+key-'a')%26+'a';
		if (str[i]>='A'&&str[i]<='Z')
			buf[i] = (str[i]+key-'A')%26+capitaloff;
	}
}

/*
int main()
{
	char prompt[] = "abcdABCD";
	int len = strlen(prompt);
	char *buf = malloc(len * sizeof(char));
	for (int i=0;i<26;i++){
		decoderot(buf, prompt, len, i, 'a');
		printf("%.*s, %d\n", len, buf, i);
	}
	free(buf);
	return 0;
}
*/
