CFLAGS= -g -Wall 

all: testVersion calcul_offset testCommit

testVersion: testVersion.o version.o 
	gcc $(CFLAGS) -o $@ $^

calcul_offset: calcul_offset.c version.o commit.o
	gcc $(CFLAGS) -o $@ $^


testCommit: testCommit.o commit.o version.o
	gcc $(CFLAGS) -o $@ $^


version.o:version.c version.h
	gcc $(CFLAGS)  -o $@  -c $<

commit.o:commit.c commit.h
	gcc $(CFLAGS)  -o $@  -c $<



%.o:%.c
	gcc $(CFLAGS)  -o $@  -c $^

clean:
	rm -f *.o testVersion calcul_offset testCommit

cleanall: clean
	rm -f *~
