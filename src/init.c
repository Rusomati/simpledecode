#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

int init(int argc, char **argv, flags *flagss)
{
	if(argc==1){
		//multiple fprintf calls..
		fprintf(stderr, "usage: %s [flags] <string to decode>\n", argv[0]);
		fprintf(stderr, "flags: -[qrth][a hexidecimal character representing a 'threshold']\n");
		fprintf(stderr, "q: dont ignore quotes, r: decrypt ROT\n");
		fprintf(stderr, "t: print results as they get found, h: half keys tested\n");
		exit(-1);
	}

	if(argc==3)
	{
		if(argv[1][0] == '-'){

			char *buf = argv[1];

			for(int i=1;i<(int)strlen(argv[1]);i++)
			{
				if(buf[i]=='q')flagss->ignorequotes=0;
				else if(buf[i]=='r')flagss->userot=1;
				else if(buf[i]=='t')flagss->nosort=1;
				else if(buf[i]=='h')flagss->half=1;
				else{
					if (buf[i]>='0'&&buf[i]<='9')flagss->threshold = buf[i] - '0';
					else if (buf[i]>='a'&&buf[i]<='f')flagss->threshold = 10 + buf[i] - 'a';
					else if (buf[i]>='A'&&buf[i]<='F')flagss->threshold = 10 + buf[i] - 'A';
					else{
						fprintf(stderr, "ignored illegal option: %c\n", buf[i]);
					}
				}
			}
		}
	}

	unsigned char buf[2];
	FILE *fp = fopen("../.genconfig.halfassed", "r");
	fread(buf, sizeof(char), 2, fp);
	int res = (256*buf[0])+buf[1];

	return res;//bufsize
}

/*
int main(int argc, char **argv)
{
	byte ignorequotes=1, userot=0, nosort=0, threshold=3;
	int bufsize = init(argc, argv, &ignorequotes, &userot, &nosort, &threshold);
	//printf("ignorequotes: %d, userot: %d, nosort: %d, threshold: %d\n",
	//	ignorequotes, userot, nosort, threshold);

	return 0;
}
*/
