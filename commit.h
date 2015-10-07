#ifndef COMMIT_H
#define COMMIT_H

#include"version.h"
#include"list.h"

struct commit;

struct commit_ops
{
  void (*display) (struct commit * c);
  void (*extract) (struct commit * c);
};

struct commit
{
  unsigned long id;
  struct version version;
  char *comment;
  struct list_head history, major_list;
  struct commit *major_parent;
  struct commit_ops ops;
  /* 
   * Le major parent d'une commit major pointer vers lui-même
   */
  //struct commit *next;
  //struct commit *prev;
};

struct commit *new_commit (unsigned short major, unsigned long minor,
			   char *comment);

struct commit *add_minor_commit (struct commit *from, char *comment);

struct commit *add_major_commit (struct commit *from, char *comment);

struct commit *del_commit (struct commit *victim);

void display_commit (struct commit *from);

void display_history (struct commit *from);

void infos (struct commit *from, int major, unsigned long minor);


/*
 * Exercice 2
 */

struct commit *commitOf (struct version *version);


/*
 * Exercice 6
 */

void freeHistory (struct commit *from);

/**
 * Exercice 7
 */
void display_major_commit (struct commit *from);

void extract_major (struct commit *victim);
void extract_minor (struct commit *victim);
#endif
