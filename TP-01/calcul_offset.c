#include <stdio.h>
#include <stdlib.h>

/*
 * Exercice 2
 */

#include "version.h"
#include "commit.h"

int main()
{

	printf("id: %p\n", &(((struct commit *)NULL)->id));
	printf("comment: %p\n", &(((struct commit *)NULL)->comment));
	printf("version: %p\n", &(((struct commit *)NULL)->version));

	/*
	 * Commit of
	 */

	struct commit e;

	e.version.major = 3;

	printf("Flèche: \t%p\n", &e);
	printf("Fonction: \t%p\n", commitOf(&(e.version)));

}
