//define bufsize well

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

int getword(int pos, FILE *fp, wrd *word_got, char *buf, int fsize, int bufsize)
{

	int buf_offset = bufsize/2;
	//for low values
	if(buf_offset > pos)buf_offset = pos;

	fseek(fp, (long)(pos-buf_offset), SEEK_SET);
	fread(buf, sizeof(char), bufsize, fp);

	//out of bound check ig
	if(pos<=1||pos>=fsize){
		//fprintf(stderr, "debug: nonexistent\n");//
		return -1;
	}

	int frontcnt = buf_offset, backcnt = buf_offset;
	

	//if pos hits a \n we will ignore it
	if(buf[backcnt]=='\n')backcnt--;

	//a word is [a-zA-Z']+ here
	//we go back to get the index
	//length = distance to start + distance to end..
	for(;buf[frontcnt]!='\n';frontcnt++);
	for(;buf[backcnt]!='\n';backcnt--);

	//copy word
	word_got->len = frontcnt - backcnt - 1;//added -1 to simplify stuff..
	memcpy(word_got->str, &buf[backcnt+1], word_got->len);
	//return the startof the word got
	return pos+backcnt+1-buf_offset;
}

//untested and will prob fail
/*
int main()
{
	FILE *fp = fopen("../newerdict.txt", "r");
	int bufsize = 150;
	char *buf = malloc(bufsize * sizeof(char));

	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp) - 1;//for the last \n

	wrd *special_nigga = makewrd(NULL, bufsize/2);

	int pos = getword(1000, fp, special_nigga, buf, fsize, bufsize);//word
	//if(pos>0){//the equal is unnecessary in this very case
	printf("position: %d, word:%.*s", pos, special_nigga->len,special_nigga->str);
	//}else {}//'ignore word' because it probably cant be valid
	pos = getword(pos+special_nigga->len, fp, special_nigga, buf, fsize, bufsize);//next word
	printf("position: %d, word:%.*s", pos, special_nigga->len,special_nigga->str);
	
	pos = getword(pos-1, fp, special_nigga, buf, fsize, bufsize);//prev word
	printf("position: %d, word:%.*s", pos, special_nigga->len, special_nigga->str);

	free(buf);
	freewrd(special_nigga, 1);
	return 0;
}
*/
