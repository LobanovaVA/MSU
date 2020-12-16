#ifndef LIST2_NODE_H
#define LIST2_NODE_H

#include "student.h"

class list2;

class list2_node : public student
{
private:
  list2_node * next = nullptr;
  list2_node * prev = nullptr;

public:
  friend class list2;

  list2_node () = default;
  list2_node (const char* new_name, int new_value) :
    student (new_name, new_value) { }
  ~list2_node () = default;

  void set_next (list2_node *elem) { next = elem; }
  void set_prev (list2_node *elem) { prev = elem; }

  list2_node * get_next () const { return next; }
  list2_node * get_prev () const { return prev; }
};


#endif
