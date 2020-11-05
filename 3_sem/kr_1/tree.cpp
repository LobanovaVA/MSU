#include "tree.h"
#include "addition.h"

int tree::read (FILE *fp)
{
	int ret;
	delete_tree (root);
	tree_node *elem;

	elem = new tree_node();
	if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
	ret = elem -> read (fp);
	if (ret !=0) return delete elem, ret;
        root = current = elem;
	for (;;)
	{

		elem = new tree_node();
                if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
		ret = elem -> read (fp);


		if (ret != 0) return delete elem, ret;
                if (!add_elem(elem, root)) return delete elem, ERROR_CANNOT_READ_CLASS;
		elem = nullptr;
	}
	return 0;
}

void tree::print (tree_node *tmp, int space, FILE *out)
{   

    if(tmp)
    {
        for (int i=0; i<space; i++) fprintf (out, "    ");
        tmp -> print ();
        if (tmp && space<MAX_PRINT) 
        {
            space++;
            print (tmp -> left,   space, out);
            print (tmp -> middle, space, out);
            print (tmp -> right,  space, out);
        }
    }
}


//navigation:______________________________________________________________________________________________

tree_node * tree::get_left () const
{
    if (current) return current -> left;
    else return nullptr;
}

tree_node * tree::get_middle() const
{
    if (current) return current -> middle;
    else return nullptr;
}

tree_node * tree::get_right () const
{
    if (current) return current -> right;
    else return nullptr;
}

bool tree::go_left  ()
{
    if (current) return current = current -> left,  true;
    else return false;
}
bool tree::go_middle()
{
    if (current) return current = current -> middle,  true;
    else return false;
}
bool tree::go_right  ()
{
    if (current) return current = current -> right, true;
    else return false;

}

//adding:______________________________________________________________________________________________

bool tree::add_root (tree_node *elem)
{
    if (this -> root) return false;
    return this -> root = elem, true;
}

bool tree::add_left (tree_node *elem)
{
    if (current -> left ) return false;
    return current -> left = elem, true;
}

bool tree::add_middle(tree_node *elem)
{
    if (current -> middle) return false;
    return current -> middle= elem, true;
}
bool tree::add_right (tree_node *elem)
{
    if (current -> right ) return false;
    return current -> right = elem, true;
}


tree_node * tree::add_elem(tree_node *tmp, tree_node *root)
{
    if(!root) 
    {
        root = tmp;
        return root;
    }
    else
    {
        if (*tmp < *root)
        {
             tmp = add_elem(tmp, root->left);
            if (tmp) root -> left = tmp;
            else return 0;
        }
        else
        {
            if (*tmp > *root)
            {
                tmp = add_elem(tmp, root-> right);
                if (tmp) root -> right = tmp;
                else return 0;
            }
            else
            {
                tmp = add_elem(tmp, root-> middle);
                if (tmp) root -> middle = tmp;
                else return 0;
            }
        }
    }
    return root;
}


//deleting:______________________________________________________________________________________________

void tree::delete_tree (tree_node *tmp)
{
    if (tmp)
    {
        delete_tree (tmp -> left );
        delete_tree (tmp -> middle);
        delete_tree (tmp -> right);
    }
    if(tmp == root) root = nullptr;
    delete tmp;

}

void tree::delete_root ()
{
    if (root && !(root -> left || root -> right || root -> middle ))
    {
        delete root;
        root = nullptr;
    }
}

void tree::delete_left ()
{
    tree_node *tmp;
    tmp = current -> left;
    if (tmp && !(root -> left || root -> right || root -> middle )) delete tmp;
    current -> left = nullptr;
}

void tree::delete_middle ()
{
    tree_node *tmp;
    tmp = current -> middle;
    if (tmp && !(root -> left || root -> right || root -> middle )) delete tmp;
    current -> middle = nullptr;
}

void tree::delete_right ()
{
    tree_node *tmp;
    tmp = current -> right;
    if (tmp && !(root -> left || root -> right || root -> middle )) delete tmp;
    current -> right = nullptr;
}

//solution:______________________________________________________________________________________________

int tree::solve (tree_node *tmp)
{
    if (!tmp) return 0;
    int count = 0;
    /*
    if ((  (tmp -> left) && !(tmp -> middle) && !(tmp -> right) && !((tmp -> left   )-> left) && !((tmp -> left   )-> middle) && !((tmp -> left   )-> right) )) count++;
    if (( !(tmp -> left) &&  (tmp -> middle) && !(tmp -> right) && !((tmp -> middle )-> left) && !((tmp -> middle )-> middle) && !((tmp -> middle )-> right) )) count++;
    if (( !(tmp -> left) && !(tmp -> middle) &&  (tmp -> right) && !((tmp -> right  )-> left) && !((tmp -> right  )-> middle) && !((tmp -> right  )-> right))) count++;
    */
    if (c(tmp)==1) count++;
    return count + solve (tmp -> left  ) + solve (tmp -> middle) + solve (tmp -> right );
}

int tree::c(tree_node *tmp)
{
    int count = 0;
    tree_node *tmp2 ;
    if (tmp -> left)
    {
        tmp2 = tmp -> left;
        count++;
        if (tmp2 -> left) count++;
        if (tmp2 -> middle) count++;
        if (tmp2 -> right) count++;
    }
    if (tmp -> middle)
    {
        tmp2 = tmp -> middle;
        count++;
        if (tmp2 -> left) count++;
        if (tmp2 -> middle) count++;
        if (tmp2 -> right) count++;
    }
    if (tmp ->  right)
    {
        tmp2 = tmp -> right;
        count++;
        if (tmp2 -> left) count++;
        if (tmp2 -> middle) count++;
        if (tmp2 -> right) count++;
    }
    return count;
}


