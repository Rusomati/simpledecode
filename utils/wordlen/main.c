//does count the \n at the end..
#include <stdio.h>
#include <stdlib.h>

int buflen = 4096;

int main()
{
	char *buf = malloc(buflen*sizeof(char));
	FILE *dict = fopen("/usr/share/dict/linux.words","r");

	int maxchr = 0, wlen = 0, index = 0, loc, read;
	while(read = fread(buf,sizeof(char),buflen,dict))
	{
		for(int i=0;i<read;i++)
		{
			wlen++;
			index++;
			if(buf[i]=='\n')
			{
				if (wlen>maxchr){
					maxchr = wlen;
					loc = index-wlen;
				}
				wlen = 0;
			}
		}
	}
	fseek(dict,loc,SEEK_SET);
	fread(buf,sizeof(char),maxchr,dict);
	printf("the length of the longest word here: %d located at: %d\nword: %.*s", maxchr, loc, maxchr, buf);

	maxchr = maxchr * 2;
	unsigned char binchr[2];
	binchr[0] = maxchr/256;
	binchr[1] = maxchr%256;
	FILE *fgenopt = fopen("../../.genconfig.halfassed","w");
	fwrite(binchr, sizeof(char), 2,fgenopt);

	fclose(fgenopt);
	fclose(dict);
	free(buf);

	return 0;
}
