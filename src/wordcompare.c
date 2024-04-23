#include <stdio.h>
#include <string.h>
#include "common.h"

//decides whether the dictionary should go up or down
//using the fact that it is sorted
int comparewrd(wrd *w_one, wrd *w_two)
{
	int res = 0;
	int iterations = (w_one->len < w_two->len)?w_one->len:w_two->len;
	//printf("comparing: %.*s, %.*s\n", w_one->len, w_one->str, w_two->len, w_two->str);
	//unnecessary checks?
	
	for (int i=0;i<iterations;i++)
	{
		//equal check omitted
		if (w_one->str[i] > w_two->str[i]){
			res = 1;
			break;
		}
		if (w_one->str[i] < w_two->str[i]){
			res = -1;
			break;
		}
	}

	//res == 0
	if (!res){
		if (w_one->len==w_two->len)return res;
		if (w_one->len>w_two->len)return 1;
		else 
			return -1;
	}
	return res;		
}

/*
int main(int argc,char **argv)
{
	wrd *wordone = makewrd(argv[1], 0);
	wrd *wordtwo = makewrd(argv[2], 0);
	int order = wordcompare(wordone, wordtwo);//what a name
	
	if (!order)printf("equal\n");
	else if (order==1)printf("jump down\n");
	else printf("jump up\n");

	freewrd(wordone, 1);
	freewrd(wordtwo, 1);
	return 0;
}
*/
