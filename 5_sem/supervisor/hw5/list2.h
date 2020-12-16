#ifndef LIST_H
#define LIST_H

#include "list2_node.h"

class list2
{
private:
  list2_node * head = nullptr;
  static int m;
  static int r;

public:
  list2 () = default;
  ~list2 () { delete_list(); }

  static void set_m (int m) { list2::m = m; }
  static void set_r (int r) { list2::r = r; }

  list2_node * get_head () const;
  int get_length () const;

  void delete_curr (list2_node *elem);
  void delete_head ();
  void delete_list ();

  void add_head (list2_node *elem);
  void add_next (list2_node *curr, list2_node *elem);
  void add_prev (list2_node *curr, list2_node *elem);

  int read (FILE *fp);
  void print ();

  int operator< (const list2& b);

};

#endif
