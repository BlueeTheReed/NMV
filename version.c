#include<stdlib.h>
#include<stdio.h>

#include"version.h"

int is_unstable(struct version *v)
{
	//return 1 & ((char *)v)[sizeof(short)];
	return 1 & ((char *)v)[0];
	//return v->minor % 2
}

int is_unstable_bis(struct version *v){
	return 1 & v->minor;
}

void display_version(struct version *v, int (*f)(struct version *v))
{
	printf("%2u-%lu %s", v->major, v->minor,
			     f(v) ? "(unstable)" : "(stable)	");
}

int cmp_version(struct version *v, int major, int minor)
{
	return v->major == major && v->minor == minor;
}
