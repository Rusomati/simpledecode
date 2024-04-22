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
        char *todecode = lowerplus(str, &lenn, flagss.ignorequotes);//[r]
	
	int len = lenn/2;//
	char *decoded = malloc(2 * len * sizeof(char));
        int decodedlen;

	wrd *words;
	wrd word;
	int wrdcnt = 0, charcnt = 0;
	//len can be "halfed" under assumptions
	//add a flag for it
	int iterations = (flagss.half)?len/2:len;
	long long eval;
	for (int i=2;i<iterations;i++)
	{
		//[r]
		decode(todecode, len, i, decoded, &decodedlen);//key = 'len'/i
		//^^ use the wrd 'api' for this possibly and more

		word.len = decodedlen;
		word.str = decoded;
		words = locate(&word, &wrdcnt, &charcnt, flagss.ignorequotes);//is chrcnt useless??

		words = wordsinfile(words, &wrdcnt, bufsize, flagss.ignorequotes);//improve

		eval = streval(words, wrdcnt, charcnt);
		if(eval > flagss.threshold * thresholdmp)
		{
			//expand str or smth.....
			free(todecode);
			lenn/=2;
        		todecode = lowerplus(str, &lenn, 0);
			decode(todecode, len, i, decoded, &decodedlen);
			printf("%lld\t%.*s\n", eval, decodedlen, decoded);
		}

		freewrd(words, wrdcnt);//i dont want this in my loop
	}

	free(todecode);
	free(decoded);
	return 0;
}
