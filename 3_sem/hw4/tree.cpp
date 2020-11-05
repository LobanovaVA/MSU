#include "tree.h"
#include "addition.h"
#include <math.h>

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
            print (tmp -> left , space, out);
            print (tmp -> right, space, out);  
        }
    }
}

//navigation:______________________________________________________________________________________________


tree_node * tree::get_left () const 
{ 
    if (current) return current -> left; 
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
            tmp = add_elem(tmp, root-> right);
            if (tmp) root -> right = tmp;
            else return 0;
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
        delete_tree (tmp -> right);
    }
    if(tmp == root) root = nullptr;
    delete tmp;

}

void tree::delete_root ()
{
    if (root && !(root -> left || root -> right)) 
    {
        delete root;
        root = nullptr;
        }
}

void tree::delete_left ()
{
    tree_node *tmp;
    tmp = current -> left;
    if (tmp && !(tmp -> left || tmp -> right)) delete tmp;
    current -> left = nullptr;
}

void tree::delete_right ()
{
    tree_node *tmp;
    tmp = current -> right;
    if (tmp && !(tmp -> left || tmp -> right)) delete tmp;
    current -> right = nullptr; 
}

//decision:______________________________________________________________________________________________          



int tree::solve_1 (tree_node *tmp)
{
    int count = 0;
    if (tmp -> left ) count += solve_1 (tmp -> left);
    if (tmp -> right) count += solve_1 (tmp -> right);
    if ( !(tmp -> left || tmp -> right) ) count++;
    return count;
}

//int max (int a, int b){ if (a > b) return a; else return b;}

int tree::solve_2 (tree_node *tmp)
{
    int count = 1, l=0, r=0;  
    if (tmp -> left ) l = solve_2 (tmp -> left );
    if (tmp -> right) r = solve_2 (tmp -> right);
    count += fmax(l, r);
    return count;
}

int tree::solve_3 ()
{
    int n = solve_2 (root);
    int count = 1;
    for (int i=1; i<n; i++)
        count = fmax (count, how_match_level (root, 0, i) );
    return count;
}

int tree::how_match_level (tree_node *tmp, int now, int need)
{
    int count = 0;  
    if (need == now) return 1; 
    now++;
    if (tmp -> left ) count += how_match_level (tmp -> left,  now, need);
    if (tmp -> right) count += how_match_level (tmp -> right, now, need);
    return count;
}


int tree::solve_4  (tree_node *tmp,int &ans)
{
    int count = 1, l = 0, r = 0, ans_l = 0, ans_r = 0;
    if (tmp -> left ) l = solve_4 (tmp -> left,  ans_l);
    if (tmp -> right) r = solve_4 (tmp -> right, ans_r);
    ans = (ans_l>ans_r) ? ans_l : ans_r;
    count += (l > r) ? l : r;
    ans = (l-r > ans) ? l-r : ans;
    ans = (r-l > ans) ? r-l : ans;
    return count;
}

int tree::solve_5 (tree_node *tmp)
{
    int count = 0;
    if ( (tmp -> left && !(tmp -> right)) ||  (tmp -> right && !(tmp -> left)) ) count++;
    if (tmp -> left ) count += solve_5 (tmp -> left);
    if (tmp -> right) count += solve_5 (tmp -> right);
    
    return count;
}




/*

int tree::solve_4 (tree_node *tmp, int& ans)
{
    int l=0, r=0, ans_l=0, ans_r=0;
    if ( !(tmp -> left) && !(tmp -> right) ) return 1;
    else 
    {
        if (tmp -> left ) l = solve_4 (tmp -> left,  ans_l);
        if (tmp -> right) r = solve_4 (tmp -> right, ans_r);
        ans = (int)fabs(l-r);
        ans = fmax (fmax (ans_l, ans_r), ans);
        return fmax (l, r)+1;
    }

}


int tree::solve_4  (tree_node *tmp,int &ans)
{
        int maxim = 1,l = 0,r = 0, ans_l = 0, ans_r = 0;
        if (tmp -> left ) l = solve_4 (tmp -> left,  ans_l);
        if (tmp -> right) r = solve_4 (tmp -> right, ans_r);
        if (ans_l > ans_r) ans = ans_l;
        else ans = ans_r;
        if (l > r)
        {
            maxim += l;
            if (l-r > ans) ans = l-r;
        }
        else
        {
            maxim += r;
            if (r-l > ans) ans = r-l;
        }
        return maxim;
}

*/
