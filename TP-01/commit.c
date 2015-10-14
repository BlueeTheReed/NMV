#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"commit.h"

/*Initialisé à zéro automatiquement */
static int nextId;

/**
 * new_commit - alloue et initialise une structure commit correspondant au parametre
 * @major:      numero de version majeure
 * @minor:      numero de version mineure
 * @comment:    pointeur vers une chaine de caracteres contenant un commentaire
 */
struct commit *new_commit(unsigned short major, unsigned long minor,
			  char *comment)
{
	/* Exercice 3 - Question 2 */

	struct commit *new = malloc(sizeof(struct commit));
	if (new == NULL)
		perror("malloc commit"), exit(-1);

	new->id = nextId++;
	new->version.major = major;
	new->version.minor = minor;
	new->comment = comment;

	new->major_parent = new;

	INIT_LIST_HEAD(&new->history);
	INIT_LIST_HEAD(&new->major_list);

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

	list_add(&(new->history), &from->history);

	if (new->major_parent == new) {
		list_add(&(new->major_list), &(from->major_parent->major_list));
	}

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

	struct commit *new =
	    new_commit(from->version.major, from->version.minor + 1, comment);
	new->major_parent = from->major_parent;
	insert_commit(from, new);

	new->ops.display = display_commit;
	new->ops.extract = extract_minor;

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
	struct commit *new =
	    new_commit(from->version.major + 1, from->version.minor, comment);
	new->major_parent = new;
	insert_commit(from, new);

	new->ops.display = display_major_commit;
	new->ops.extract = extract_major;

	return new;
}

/**
 * del_commit - extrait le commit de l'historique
 * @victim:         commit qui sera sorti de la liste doublement chainee
 */
struct commit *del_commit(struct commit *victim)
{
	/*  TODO : Exercice 3 - Question 5 */

	victim->ops.extract(victim);

	return NULL;
}

void extract_major(struct commit *victim)
{
	struct commit *aux, *n;
	list_for_each_entry_safe(aux, n, &victim->history, history) {
		if (aux->major_parent == aux && aux != victim)
			break;
		aux->ops.extract(aux);
	}
	extract_minor(victim);

}

void extract_minor(struct commit *victim)
{
	list_del(&victim->history);
	free(victim);
}

/**
 * display_commit - affiche un commit : "2:  0-2 (stable) 'Work 2'"
 * @c:             commit qui sera affiche
 */
void display_commit(struct commit *c)
{
	/*  Exercice 3 - Question 4 */

	printf("%ld: ", c->id);

	display_version(&(c->version), is_unstable);

	printf("\t%s\n", c->comment);

}

/* Exercice 7 Q2
 * display_major_commit
 */
void display_major_commit(struct commit *c)
{

	printf("%ld: ", c->id);

	display_version(&(c->version), is_unstable);

	printf("\t%s\t###\n", c->comment);

}

/**
 * display_history - affiche tout l'historique, i.e. l'ensemble des commits de la liste
 * @from:           premier commit de l'affichage
 */
void display_history(struct commit *from)
{
	/*  Exercice 3 - Question 4 */

	struct commit *aux = from;

	from->ops.display(from);

	list_for_each_entry(aux, &from->history, history) {
		aux->ops.display(aux);
	}

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
	int found = 0;
	/*
	   struct commit *aux = from;
	   do{

	   if(aux->version.major == major &&
	   aux->version.minor == minor){
	   display_commit(aux);
	   found++;
	   break;
	   }
	   aux = aux->next;

	   }while(aux != from && aux != NULL && ( aux->version.major <= major && aux->version.minor <= minor) ); */

	struct commit *aux = NULL, *firstMajor = NULL;
	list_for_each_entry(aux, &from->major_list, major_list) {
		if (aux->version.major >= major)
			break;
	}
	if (aux->version.major == major) {
		firstMajor = aux;
		list_for_each_entry(aux, &firstMajor->history, history) {
			if (aux->version.major != major)
				break;
			if (aux->version.minor == minor) {
				found++;
				display_commit(aux);
			}
		}

	}

	if (!found)
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

	void *offset = &(((struct commit *)NULL)->version);

	return (struct commit *)(((void *)version) - offset);
}

/**
 * freeHistory - Libère l'ensemble des commits qui sont liés à celui passé en
 * paremètre. Avant le return, la fonction free le commit passé en paramètre
 * @from : Le commit à partir duquel la libération commence
 */
void freeHistory(struct commit *from)
{

	struct commit *aux, *n;

	list_for_each_entry_safe(aux, n, &from->history,
				 history) del_commit(aux);
	free(from);
}
