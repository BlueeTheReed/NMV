CFLAGS= -g -Wall 

all: testVersion

testVersion: testVersion.o version.o 
	gcc $(CFLAGS) -o $@ $^

version.o:version.c version.h
	gcc $(CFLAGS)  -o $@  -c $<

%.o:%.c
	gcc $(CFLAGS)  -o $@  -c $^

clean:
	rm -f *.o

cleanall: clean
	rm -f *~
