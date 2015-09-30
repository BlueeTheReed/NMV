CFLAGS= -g -Wall 

all: testVersion calcul_offset

testVersion: testVersion.o version.o 
	gcc $(CFLAGS) -o $@ $^

version.o:version.c version.h
	gcc $(CFLAGS)  -o $@  -c $<

calcul_offset: calcul_offset.c version.o
	gcc $(CFLAGS) -o $@ $^

%.o:%.c
	gcc $(CFLAGS)  -o $@  -c $^

clean:
	rm -f *.o testVersion

cleanall: clean
	rm -f *~
