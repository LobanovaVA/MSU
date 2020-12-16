#ifndef TREE_H
#define TREE_H

#include "tree_node.h"

template <class T>
class tree
{
private:
  tree_node<T> * root = nullptr;

public:
  tree () = default;
  ~tree () { delete_tree (get_root ()); }

  tree_node<T> * get_root () const { return root; }

  int
  get_length (tree_node<T> *begin) const
  {
    if (!begin)
      return 0;

    int count = 1;
    int l = 0, r = 0;

    tree_node<T> *left_elem  = begin -> get_left ();
    tree_node<T> *right_elem = begin -> get_right ();

    if (left_elem)
      l = get_length (left_elem);

    if (right_elem)
      r = get_length (right_elem);

    count += (l > r) ? l : r;
    return count;
  }

  void
  delete_tree (tree_node<T> *tmp)
  {
    if (tmp)
      {
        delete_tree (tmp -> get_left ());
        delete_tree (tmp -> get_right ());
      }
    if (tmp == get_root ())
      root = nullptr;

    delete tmp;
  }

  /* ============ initialization ============ */
  tree_node<T> *
  insert (tree_node<T> *elem, tree_node<T> *begin)
  {

    if (!begin)
      {
        if (!get_root ())
          root = elem;
        begin = elem;
        return begin;
      }
    else
      {
        if (*elem < *begin)
          {
            elem = insert (elem, begin -> get_left ());
            if (elem)
              begin -> left = elem;
            else
              return nullptr;
          }
        else
          {
            elem = insert (elem, begin -> get_right ());
            if (elem)
              begin -> right = elem;
            else
              return nullptr;
          }
      }
    return begin;
  }


  int
  read (const char * filename)
  {
    FILE *fp;
    int ret = SUCCESS;
    tree_node<T> *elem;

    fp = fopen (filename, "r");
    if (!fp)
      return ERROR_CANNOT_OPEN_INPUT_FILE;

    this -> ~tree ();

    while (ret != ERROR_END_OF_INPUT_FILE)
      {
        elem = new tree_node<T>;
        ret = elem -> read (fp);

        if (ret != SUCCESS && !elem -> get_length ())
          {
            delete elem;
            fclose (fp);
            return ret;
          }

        if (!insert (elem, get_root ()))
          {
            delete elem;
            fclose (fp);
            return ERROR_INITIALIZATION_TREE;
          }
        elem = nullptr;
      }

    fclose (fp);
    return SUCCESS;
  }


  /* ============ print ============ */
  void
  print (int r)
  {
    printf("\n╔=========");
    printf("\n║ 👀 TREE\n║\n║");

    print_rec (get_root(), r, 0);
    //print_rec (get_root(), r, 0, 0);

    printf("\n╚=========\n\n");
  }

  void
  print_rec (tree_node<T> *tmp, int print_lim, int space)
  {
    if (print_lim == 0)
      return;

    if (space == 0)
      printf(" Root: (");

    if (tmp)
      {
        tmp -> print ();
        printf (" )\n║");

        if (print_lim != 1)
          {
            space++;
            print_lim--;

            for (int i = 0; i < space; i++)
              printf ("        ");
            printf("%dL: (", space);
            print_rec (tmp -> get_left () , print_lim, space);

            for (int i = 0; i < space; i++)
              printf ("        ");
            printf("%dR: (", space);
            print_rec (tmp -> get_right (), print_lim, space);
          }
      }
    else
      printf (" --- )\n║");
  }


  void
  print_rec (tree_node<T> *tmp, int print_lim, int space, int fl)
  {
    if (print_lim == 0)
      return;

    if (print_lim != 1)
      {
        space++;
        print_lim--;

        if (tmp)
          print_rec (tmp -> get_left (), print_lim, space, -1);

        for (int i = 0; i < space - 1; i++)
          printf ("          ");

        switch (fl)
          {
          case -1:
            printf("%dL: (", space - 1);
            break;
          case 0:
            printf(" Root: (");
            break;
          case 1:
            printf("%dR: (", space - 1);
            break;
          }

        if (tmp)
          tmp -> print ();
        else
          printf (" ---");

        printf (" )\n║");

        if (tmp)
          print_rec (tmp -> get_right (), print_lim, space, 1);
      }
  }




  /* ============ problems ============ */
  int problem_1 () const { return problem_1_rec (get_root ()); }

  int
  problem_1_rec (tree_node<T> * begin) const
  {
    if (!begin)
      return 0;

    int count = 0;

    tree_node<T> *left_elem  = begin -> get_left ();
    tree_node<T> *right_elem = begin -> get_right ();

    if (left_elem)
      count += problem_1_rec (left_elem);

    if (right_elem)
      count += problem_1_rec (right_elem);

    if (!left_elem && !right_elem)
      count += begin -> get_length ();

    return count;
  }


  int problem_2 () const { return problem_2_rec (get_root ()); }

  int
  problem_2_rec (tree_node<T> * begin) const
  {
    if (!begin)
      return 0;

    int l = 0, r = 0;
    int count = begin -> get_length ();

    tree_node<T> *left_elem  = begin -> get_left ();
    tree_node<T> *right_elem = begin -> get_right ();

    if (left_elem)
      l = problem_2_rec (left_elem);

    if (right_elem)
      r = problem_2_rec (right_elem);

    count += (l > r) ? l : r;
    return count;

  }


  int
  problem_3 () const
  {
    if (!get_root ())
      return 0;

    int i, ret, count = get_root () -> get_length ();
    int len = get_length (get_root ());

    for (i = 1; i < len; i++)
      {
        ret = how_match_in_level (get_root (), 0, i);
        if (ret > count)
          count = ret;
      }

    return count;
  }

  int
  how_match_in_level (tree_node<T> *tmp, int now, int need) const
  {
    if (!tmp)
      return 0;

    int count = 0;
    if (need == now)
      return tmp -> get_length ();

    now++;
    if (tmp -> get_left ())
      count += how_match_in_level (tmp -> get_left (),  now, need);

    if (tmp -> get_right ())
      count += how_match_in_level (tmp -> get_right (), now, need);

    return count;
  }


  int problem_4 () const
  {
    int ans = 0;
    problem_4_rec (get_root (), ans);
    return ans;
  }
  int problem_4_rec (tree_node<T> *begin, int &ans) const
  {
    if (!begin)
      return 0;

    int count = begin -> get_length ();
    int l = 0, r = 0, ans_l = 0, ans_r = 0;

    if (begin -> get_left ())
      l = problem_4_rec (begin-> get_left (),  ans_l);

    if (begin -> get_right ())
      r = problem_4_rec (begin -> get_right (), ans_r);

    ans = (ans_l > ans_r) ? ans_l : ans_r;
    count += (l > r) ? l : r;
    ans = (fabs(l - r) > ans) ? fabs(l - r) : ans;
    return count;
  }


  int problem_5 () const { return problem_5_rec (get_root ()); }
  int problem_5_rec (tree_node<T> *begin) const
  {
    if (!begin)
      return 0;

    int count = 0;

    tree_node<T> *left_elem  = begin -> get_left ();
    tree_node<T> *right_elem = begin -> get_right ();

    if ((left_elem && !right_elem) || (!left_elem && right_elem))
      count += begin -> get_length ();

    if (left_elem)
      count += problem_5_rec (left_elem);

    if (right_elem)
      count += problem_5_rec (right_elem);

    return count;
  }

};


#endif






