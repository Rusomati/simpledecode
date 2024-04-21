// we can put C code and global variables ig
// we should probably (declare?) functions here
// and thats it
#ifndef COMMON
#define COMMON
//declarations go here
typedef unsigned char byte;

typedef struct{
	byte ignorequotes;
	byte userot;
	byte nosort;
	byte half;
	byte threshold;
}flags;

typedef struct {
	int len;
	char *str;
} wrd;

int init(int argc, char **argv, flags *flagss);
//^^ gets flags and bufsize

char *lowerplus(char *str, int *length, byte lwr);
//lowers the string then pads it with spaces (for decoding)

void decode(char *text, int len, int offset, char *res, int *reslen);
//(transponder?) decoder

wrd *makewrd(char *str, int len);
void freewrd(wrd *words, int count);

int filter(wrd *word);//removes '\'' from a word
wrd *locate(wrd *buf, int *wordcnt, int *charcnt, byte ignorequote);
//^^ converts a string into a 'simplified' array of wrds

int comparewrd(wrd *w_one, wrd *w_two);
//^^ return zero on equal one for 'greater than' (down)
//and negative one for 'less than' (up)

//gets the beggining of the word which 'intersects' with pos
//requires a file to read from a buffer (to reduce unnecessary alloctions)
//and the file size for bound checking
int getword(int pos, FILE *fp, wrd* word_got, char *buf, int fsize, int bufsize);
//^^untested main(might not be the only untested main..

wrd *wordsinfile(wrd *words, int *count, int bufsize, byte ignorequotes);
//checks if wrds exist in a sorted file using binary search

unsigned long long streval(wrd *words, int cnt, int chars);
//evaluates a list of words in terms of how human they are, fairly basic atm
#endif
