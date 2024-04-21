CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address,undefined,leak -O2 -lm -g -I./
#-lm......
CPRODFLAGS = -I./ 
#CPPFLAGS = -I./common.h

all: main

main: ../objfiles/main.o ../objfiles/init.o ../objfiles/lowerplus.o ../objfiles/decode.o \
../objfiles/word.o ../objfiles/simplify.o ../objfiles/dictword.o ../objfiles/wordcompare.o\
../objfiles/wordsinfile.o ../objfiles/streval.o
	echo "linking debug build"
	$(CC) $(LDFLAGS) $(CFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

../objfiles/main.o: main.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/init.o: init.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/lowerplus.o: lowerplus.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/decode.o: decode.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/word.o: word.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/simplify.o: simplify.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/dictword.o: dictword.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/wordcompare.o: wordcompare.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/wordsinfile.o: wordsinfile.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@

../objfiles/streval.o: streval.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $^ -o $@


#dictwordp: ../objfiles/dictwordp.o ../objfiles/wordp.o
#	echo "linking production build"
#	$(CC) $(LDFLAGS) $(CPRODFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@
#
#../objfiles/dictwordp.o: dictword.c
#	echo "compiling simplify.c"
#	$(CC) -c $(CPPFLAGS) $(CPRODFLAGS) $^ -o $@
#
#../objfiles/wordp.o: word.c
#	echo "compiling word.c"
#	$(CC) -c $(CPPFLAGS) $(CPRODFLAGS) $^ -o $@

clean:
	sh -c "rm ../objfiles/*.o"
