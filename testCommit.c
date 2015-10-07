#include<stdlib.h>
#include<stdio.h>

#include"commit.h"

int
main (int argc, char const *argv[])
{
  struct commit *first = new_commit (0, 0, "First !");
  struct commit *tmp, *victim, *last;

  struct commit *major_commit_aux;

  first->ops.display = display_major_commit;
  first->major_parent = first;
  first->ops.extract = extract_major;

  display_commit (first);
  printf ("\n");

  display_history (first);

  tmp = add_minor_commit (first, "Work 1");
  tmp = add_minor_commit (tmp, "Work 2");
  victim = add_minor_commit (tmp, "Work 3");
  last = add_minor_commit (victim, "Work 4");
  display_history (first);

  del_commit (victim);
  display_history (first);

  major_commit_aux = tmp = add_major_commit (last, "Realse 1");
  tmp = add_minor_commit (tmp, "Work 1");
  tmp = add_minor_commit (tmp, "Work 2");
  tmp = add_major_commit (tmp, "Realse 2");
  tmp = add_minor_commit (tmp, "Work 1");
  display_history (first);

  add_minor_commit (last, "Oversight !!!");
  display_history (first);

  infos (first, 1, 2);

  infos (first, 1, 7);

  infos (first, 4, 2);


  /*
   * Test Exercice 7
   */

  del_commit (major_commit_aux);
  display_history (first);

  //freeHistory(first);
  return 0;
}
