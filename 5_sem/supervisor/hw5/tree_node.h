#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "addition.h"

template <class T> class tree;

template <class T>
class tree_node : public T
{
private:
  tree_node * left = nullptr;
  tree_node * right = nullptr;

public:
  friend class tree<T>;

  tree_node () = default;
  ~tree_node () = default;

  void set_right (tree_node<T> *elem) { right = elem; }
  void set_left  (tree_node<T> *elem) { left  = elem; }

  tree_node<T> * get_left  () const { return left;  }
  tree_node<T> * get_right () const { return right; }

};


#endif
