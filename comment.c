#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"comment.h"

struct comment *new_comment(int title_size, char *title,
		int author_size, char *author, int text_size,
		char *text)
{
	struct comment *c = (struct comment *)malloc(sizeof(struct comment));

	/*
	 * Exercice 8
	 title_size = strlen(title) + 1;
	 author_size = strlen(author) + 1;
	 text_size = strlen(text) + 1;
	 */

	/*
	c->title = strdup(title);
	c->author = strdup(author);
	c->text = strdup(text);
	*/

	c->title_size = title_size;
	if(! (c->title = malloc(title_size))){
		perror("malloc title");
		return NULL;
	}
	memcpy(c->title, title, title_size);

	c->author_size = author_size;
	if(! (c->author = malloc(author_size))){
		perror("malloc author");
		goto err_author;
	}
	memcpy(c->author, author, author_size);

	c->text_size = text_size;
	if(! (c->text = malloc(text_size))){
		perror("malloc text");
		goto err_text;
	}
	memcpy(c->text, text, text_size);

	return c;

err_text:
	free(c->author);
	c->author = NULL;
err_author:
	free(c->title);
	c->title = NULL;
	return NULL;
}

void display_comment(struct comment *c)
{
	printf("%s from %s \"%s\"\n", c->title, c->author, c->text);
}
