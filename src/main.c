#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char **argv)
{
	const int limit = 256;
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

	wrd word;
	int wrdcnt = 0, charcnt = 0;
	//len can be "halfed" under assumptions
	int iterations = (flagss.half)?len/2:len;
	char *rotbuf = NULL;
	char capitaloff = (flagss.ignorequotes)?'a':'A';
	if (flagss.userot){
		iterations=26;//////
		rotbuf = malloc(lenn * sizeof(char));
		memcpy(rotbuf, str, lenn);///////////
	}

	long long eval;

	locateargs args;
	locatepre(&args, len*2);

	wifargs wargs;
	wordsinfilepre(&wargs, bufsize, args.words, flagss.ignorequotes);

	for (int i=1;i<iterations;i++)
	{
		
		if(!flagss.userot){
			decode(todecode, (len < limit)?len:limit, len, i, decoded, &decodedlen);//key = 'len'/i
			//^^ use the wrd 'api' for this possibly and more
			word.len = decodedlen;
			word.str = decoded;
		}else {
			int tmplen = (lenn < limit)?lenn:limit;
			decoderot(rotbuf, str, tmplen, i, capitaloff);
			word.len = tmplen;
			word.str = rotbuf;
		}

		//printf("%.*s\n", word.len, word.str);
		locate(&args, &word, &wrdcnt, &charcnt, flagss.ignorequotes);//is chrcnt useless??

		
		wordsinfile(&wargs, args.words, &wrdcnt, bufsize);//improve

		//for(int i=0;i<wrdcnt;i++)printf("-%.*s-\n", wargs.words[i].len, wargs.words[i].str);
		eval = streval(wargs.words, wrdcnt, charcnt);
		if(eval > flagss.threshold * thresholdmp)
		{
			if(!flagss.userot){
			//expand str or smth.....
				free(todecode);
				lenn/=2;
        			todecode = lowerplus(str, &lenn, 0);
				decode(todecode, len, len, i, decoded, &decodedlen);
				printf("%lld\t%.*s\n", eval, decodedlen, decoded);
			}else{
				printf("%.*s\n", lenn, rotbuf);
			}
		}
		

	}

	free(args.words);
	locatefree(&args);
	wordsinfilefree(&wargs);
	if(rotbuf)free(rotbuf);
	free(todecode);
	free(decoded);
	return 0;
}
