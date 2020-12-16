#include "list2.h"

/* ============ get set data ============ */
list2_node * list2::
get_head () const
{
  return head;
}

int list2::
get_length () const
{
  int count = 0;
  list2_node *tmp = get_head ();

  while (tmp)
    {
      count++;
      tmp = tmp -> get_next ();
    }

  return count;
}


/* ============ deleting ============ */
void list2::
delete_curr (list2_node *elem)
{
  if (elem == get_head ())
    delete_head ();

  list2_node * next_elem = elem -> get_next ();
  list2_node * prev_elem = elem -> get_prev ();

  next_elem -> set_prev (prev_elem);
  prev_elem -> set_next (next_elem);

  delete elem;
}

void list2::
delete_head ()
{
  list2_node * tmp = get_head ();
  if (tmp)
    {
      head = tmp -> get_next ();
      delete tmp;
    }
}

void list2::
delete_list ()
{
  while (get_head ())
    delete_head ();
}


/* ============ add elem ============ */
void list2::
add_head (list2_node *elem)
{
  list2_node * tmp = get_head ();
  head = elem;
  elem -> set_next (tmp);
  elem -> set_prev (nullptr);

  if (tmp)
    tmp -> set_prev (elem);
}

void list2::
add_next (list2_node *curr, list2_node *elem)
{
  list2_node * tmp = curr -> get_next ();

  curr -> set_next (elem);
  elem -> set_prev (curr);
  elem -> set_next (tmp);

  if (tmp)
    tmp -> set_prev (elem);
}

void list2::
add_prev (list2_node *curr, list2_node *elem)
{
  list2_node * tmp = curr -> get_next ();

  curr -> set_prev (elem);
  elem -> set_next (curr);
  elem -> set_prev (tmp);

  if (tmp)
    tmp -> set_next (elem);
}



/* ============ comparison ============ */
int list2::
operator< (const list2& b)
{
  if (!get_length () && !b.get_length ())
    return 0;

  if (!get_length ())
    return 1;

  if (!b.get_length ())
    return 0;

  return (* get_head ()) < (* b.get_head ());
}


/* ============ in-out ============ */
int list2::
read (FILE *fp)
{
  int read_lim = m, ret = SUCCESS;
  list2_node *elem;

  this -> ~list2 ();

  if (read_lim > 0)
    {
      while (read_lim > 0)
        {
          elem = new list2_node;
          if (!elem)
            return ERROR_NOT_ENOUGH_MEMORY;

          ret = elem -> read (fp);
          if (ret != SUCCESS)
            {
              delete elem;
              return ret;
            }

          add_head (elem);
          read_lim--;
        }
    }
  else
    {
      while (true)
        {
          elem = new list2_node;
          if (!elem)
            return ERROR_NOT_ENOUGH_MEMORY;
          ret = elem -> read (fp);

          if (ret != SUCCESS)
            {
              delete elem;
              return ret;
            }

          add_head (elem);
        }
    }

  return SUCCESS;
}


void list2::
print ()
{
  int print_lim = r;
  list2_node *tmp = get_head ();

  printf(" 🌿");

  if (print_lim > 0)
    {
      while (tmp && print_lim > 0)
        {
          tmp -> print ();
          tmp = tmp -> get_next ();
          print_lim--;
        }

      if (tmp)
        printf(" ...");
    }
  else
    {
      while (tmp)
        {
          tmp -> print ();
          tmp = tmp -> get_next ();
        }
    }
}

