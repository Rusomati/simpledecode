#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char **argv)
{
	flags flagss = {
		.ignorequotes=1,
		.userot=0,
		.nosort=0,
		.half=0,
		.threshold=3
	};
	const int thresholdmp = 20;
	int bufsize = init(argc, argv, &flagss);

	char *str = (argc==3)?argv[2]:argv[1];
	int lenn = strlen(str);
        char *todecode = lowerplus(str, &lenn, flagss.ignorequotes);
	
	int len = lenn/2;//
	char *decoded = malloc(2 * len * sizeof(char));
        int decodedlen;

	wrd *words;
	wrd word;
	int wrdcnt = 0, charcnt = 0;
	//len can be "halfed" under assumptions
	//add a flag for it
	int iterations = (flagss.half)?len/2:len;
	char *rotbuf = NULL;
	char capitaloff = (flagss.ignorequotes)?'a':'A';
	if (flagss.userot){
		iterations=26;//////
		rotbuf = malloc(lenn * sizeof(char));
		memcpy(rotbuf, str, lenn);///////////
	}
	long long eval;
	for (int i=1;i<iterations;i++)
	{
		
		if(!flagss.userot){
			decode(todecode, len, i, decoded, &decodedlen);//key = 'len'/i
			//^^ use the wrd 'api' for this possibly and more
			word.len = decodedlen;
			word.str = decoded;
		}else {
			decoderot(rotbuf, str, lenn, i, capitaloff);
			word.len = lenn;
			word.str = rotbuf;
		}
		words = locate(&word, &wrdcnt, &charcnt, flagss.ignorequotes);//is chrcnt useless??

		words = wordsinfile(words, &wrdcnt, bufsize, flagss.ignorequotes);//improve

		eval = streval(words, wrdcnt, charcnt);
		if(eval > flagss.threshold * thresholdmp)
		{
			if(!flagss.userot){
			//expand str or smth.....
				free(todecode);
				lenn/=2;
        			todecode = lowerplus(str, &lenn, 0);
				decode(todecode, len, i, decoded, &decodedlen);
				printf("%lld\t%.*s\n", eval, decodedlen, decoded);
			}else{
				printf("%.*s\n", lenn, rotbuf);
			}
		}

		freewrd(words, wrdcnt);//i dont want this in my loop
	}

	if(rotbuf)free(rotbuf);
	free(todecode);
	free(decoded);
	return 0;
}
