#include <stdio.h>
#include <stdlib.h>

#include "version.h"

struct commit {
	unsigned long id;
	struct version version;
	char *comment;
};


int main(){

	printf("comment: %p\n", &(((struct commit *) NULL)->id));
	printf("comment: %p\n", &(((struct commit *) NULL)->comment));
	printf("comment: %p\n", &(((struct commit *) NULL)->version));

}
