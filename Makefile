CFLAGS= -g -Wall 

all: testVersion calcul_offset testCommit testComment

testVersion: testVersion.o version.o 
	gcc $(CFLAGS) -o $@ $^

testComment: testComment.o comment.o
	gcc $(CFLAGS) -o $@ $^

comment.o: comment.c comment.h
	gcc $(CFLAGS)  -o $@  -c $<

calcul_offset: calcul_offset.c version.o commit.o
	gcc $(CFLAGS) -o $@ $^

testCommit: testCommit.o commit.o version.o
	gcc $(CFLAGS) -o $@ $^


version.o:version.c version.h list.h
	gcc $(CFLAGS)  -o $@  -c $<

commit.o:commit.c commit.h list.h
	gcc $(CFLAGS)  -o $@  -c $<



%.o:%.c
	gcc $(CFLAGS)  -o $@  -c $^

clean:
	rm -f *.o testVersion calcul_offset testCommit testComment

cleanall: clean
	rm -f *~
