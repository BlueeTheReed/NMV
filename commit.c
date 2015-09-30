#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"commit.h"

static int nextId = 0;

/**
  * new_commit - alloue et initialise une structure commit correspondant au parametre
  * @major:      numero de version majeure
  * @minor:      numero de version mineure
  * @comment:    pointeur vers une chaine de caracteres contenant un commentaire
  */
struct commit *new_commit(unsigned short major, unsigned long minor, char *comment)
{
	/* Exercice 3 - Question 2 */

	struct commit *new = malloc(sizeof(struct commit));
	if(new == NULL)
		perror("malloc commit"), exit(-1);

	new->id = nextId++;

	new->version.major = major;
	new->version.minor = minor;
	new->comment = strdup(comment);

  return new;
}

/**
  * insert_commit - insert sans le modifier un commit dans la liste doublement chainee
  * @from:       commit qui deviendra le predecesseur du commit insere
  * @new:        commit a inserer - seul ses champs next et prev seront modifie
  */
static struct commit *insert_commit(struct commit *from, struct commit *new)
{
	/* 
	 *  TODO : Exercice 3 - Question 3 
	 * En quatre étapes, pour l'instant. À vérifier.
	 */

	new->next = from->next;
	if(new->next != NULL)
		new->next->prev = new;
	from->next = new;

	new->prev = from;
	

  return NULL;
}

/**
  * add_minor_commit - genere et insert un commit correspondant a une version mineure
  * @from:           commit qui deviendra le predecesseur du commit insere
  * @comment:        commentaire du commit
  */
struct commit *add_minor_commit(struct commit *from, char *comment)
{
	/*  Exercice 3 - Question 3 */

	struct commit *new = new_commit(from->version.major, from->version.minor+1, comment);
	insert_commit(from, new);

  return new;
}

/**
  * add_major_commit - genere et insert un commit correspondant a une version majeure
  * @from:           commit qui deviendra le predecesseur du commit insere
  * @comment:        commentaire du commit
  */
struct commit *add_major_commit(struct commit *from, char *comment)
{
	/*  Exercice 3 - Question 3 */
	struct commit *new = new_commit(from->version.major+1, from->version.minor, comment);
	insert_commit(from, new);
  return new;
}

/**
  * del_commit - extrait le commit de l'historique
  * @victim:         commit qui sera sorti de la liste doublement chainee
  */
struct commit *del_commit(struct commit *victim)
{
	/*  TODO : Exercice 3 - Question 5 */
  return NULL;
}

/**
  * display_commit - affiche un commit : "2:  0-2 (stable) 'Work 2'"
  * @c:             commit qui sera affiche
  */
void display_commit(struct commit *c)
{
	/*  Exercice 3 - Question 4 */

	printf("%d: ", c->id);
	
	display_version(&(c->version), is_unstable);

	printf("%s\n", c->comment);


}

/**
  * display_history - affiche tout l'historique, i.e. l'ensemble des commits de la liste
  * @from:           premier commit de l'affichage
  */
void display_history(struct commit *from)
{
	/*  Exercice 3 - Question 4 */

	struct commit *aux = from;

	do{

		display_commit(aux);
		aux = aux->next;

	}while(aux != from && aux != NULL);

	printf("\n");
}

/**
  * infos - affiche le commit qui a pour numero de version <major>-<minor>
  * @major: major du commit affiche
  * @minor: minor du commit affiche
  */
void infos(struct commit *from, int major, unsigned long minor)
{
	/*  Exercice 3 - Question 6 */
	struct commit *aux = from;
	int found = 0;

	do{

		if(aux->version.major == major && 
				aux->version.minor == minor){
			display_commit(aux);
			found++;
			break;
		}
		aux = aux->next;

	}while(aux != from && aux != NULL && ( aux->version.major <= major && aux->version.minor <= minor) );
	
	if(!found)
		printf("Not Invented Here!\n");

}

/**
  * commitOf - retourne le commit qui contient la version passe en parametre
  * @version:  pointeur vers la structure version dont cherche le commit
  * Note:      cette fonction continue de fonctionner meme si l'on modifie
  *            l'ordre et le nombre des champs de la structure commit.
  */
struct commit *commitOf(struct version *version)
{
	/*  Exercice 2 - Question 2 */

	void *offset = &(((struct commit *) NULL)->version);

	return (struct commit *) ( ((void*)version) -  offset);


}
