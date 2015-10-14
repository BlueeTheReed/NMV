#ifndef VERSION_H
#define VERSION_H

/*
struct version {
	unsigned short major;
	unsigned long minor;
	char flags;
};
*/

struct version
{
  unsigned long minor;
  unsigned short major;
  char flags;
};

int is_unstable (struct version *v);
int is_unstable_bis (struct version *v);

//void display_version(struct version *v);
void display_version (struct version *v, int (*f) (struct version * v));

int cmp_version (struct version *v, int major, int minor);

#endif
