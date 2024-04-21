#include <stdio.h>
#include <string.h>

#define bufsize 4096

int main()
{
	char buf[bufsize];//overwritten so no zero-out
	char writebuf[bufsize] = {0};//to simplify zeroed out just in case
	FILE *fdr = fopen("../../newdict.txt", "r");
	FILE *fdw = fopen("../../newerdict.txt", "w");

	int towrite = 0;
	int readcount;

	char intro[] = "\n";
	fwrite(intro, sizeof(char), strlen(intro),fdw);

	while(readcount = fread(buf, sizeof(char), bufsize, fdr))
	{
		if (readcount<bufsize)
		{
			buf[readcount] = EOF;
		}
		for(int i=0;i<bufsize;i++)
		{
			if (buf[i]!='\n')//very half assed structure i know
			{

				if (buf[i]>='A' && buf[i]<='Z')
				{
					buf[i] += 'a' - 'A';
				}
				if (buf[i]>='a' && buf[i]<='z')
				{
					writebuf[towrite] = buf[i];
					towrite++;
				}
			}
			else
			{
				writebuf[towrite] = buf[i];
				towrite++;
			}
			if (buf[i]==EOF)
			{
				
				//writebuf[towrite] = buf[i];
				//towrite++;
				break;
			}
		}
		fwrite(writebuf, sizeof(char), towrite,fdw);
		towrite = 0;
	}

	char outro[] = "\n";
	fwrite(outro, sizeof(char), strlen(outro), fdw);

	fclose(fdr);
	fclose(fdw);
	return 0;
}
