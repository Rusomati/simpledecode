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

void decoderot(char *buf, char *str, int len, int key, byte capitaloff);

void decode(char *text, int len, int origlen, int offset, char *res, int *reslen);
//(transponder?) decoder

wrd *makewrd(char *str, int len);
void freewrd(wrd *words, int count);

typedef struct locateargs{
	wrd *words;
	wrd filterbuf;//a massive string
}locateargs;

void locatepre(locateargs *args, int len);

int filter(wrd *word, wrd *buf,int *offset);//removes '\'' from a word
void locate(locateargs *args, wrd *buf, int *wordcnt, int *charcnt, byte ignorequote);
//^^ converts a string into a 'simplified' array of wrds

void locatefree(locateargs *args);

int comparewrd(wrd *w_one, wrd *w_two);
//^^ return zero on equal one for 'greater than' (down)
//and negative one for 'less than' (up)

//gets the beggining of the word which 'intersects' with pos
//requires a file to read from a buffer (to reduce unnecessary alloctions)
//and the file size for bound checking
int getword(int pos, FILE *fp, wrd* word_got, char *buf, int fsize, int bufsize);
//^^untested main(might not be the only untested main..

typedef struct wordsinfileargs{
	wrd *words;
	wrd *fileword;
	char *buf;
	FILE *fp;
	int fsize;
}wifargs;

void wordsinfilepre(wifargs* args, int bufsize, wrd *words, byte ignorequotes);

void wordsinfile(wifargs *args, wrd *words, int *count, int bufsize);
//checks if wrds exist in a sorted file using binary search

void wordsinfilefree(wifargs *args);

unsigned long long streval(wrd *words, int cnt, int chars);
//evaluates a list of words in terms of how human they are, fairly basic atm
#endif
