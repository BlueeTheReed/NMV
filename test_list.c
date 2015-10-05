#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Lundi 5 Oct 2015
 * 
 * Un magnifique de pourquoi et comment compiler selon le for_each que l'on veut
 */

LIST_HEAD(liste);

struct e{
	int a;
	int b;
	struct list_head maliste;
};


int main(){

	struct e e1, e2;
	struct list_head *cursor = NULL; //for_each
	struct e *cursor2 = NULL; //for_each_entry

	e1.a = 8;
	e1.b = 9;
	e2.a= 10;
	e2.b = 11;

	
	list_add(&e1.maliste, &liste);
	list_add(&e2.maliste, &liste);

	list_for_each(cursor, &liste){
		printf("hello\n");
	}

	list_for_each_entry(cursor2, &liste, maliste){
		printf("hello %d %d\n", cursor2->a, cursor2->b);
	}


	return 0;
}
