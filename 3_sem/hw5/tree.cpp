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

//solution:______________________________________________________________________________________________

int tree::solve_1_ans (tree_node *tmp, int k)
{
    int ans = 0;
    solve_1 (tmp, k, ans);
    return ans;
}
int tree::solve_1 (tree_node *tmp, int k, int& ans)
{
    int count = 1, ans_l=0, ans_r=0;
    if (tmp -> left ) count += solve_1 (tmp -> left,  k, ans_l);
    if (tmp -> right) count += solve_1 (tmp -> right, k, ans_r);
    ans += ans_r + ans_l;
    if (count <= k) ans++;
    return count;
}


int tree::solve_2_ans (tree_node *tmp, int k)
{
    int ans = 0;
    solve_2 (tmp, k, ans);
    return ans;
}
int tree::solve_2 (tree_node *tmp, int k, int& ans)
{
    int count = 1, ans_l=0, ans_r=0;
    if (tmp -> left ) count += solve_2 (tmp -> left,  k, ans_l);
    if (tmp -> right) count += solve_2 (tmp -> right, k, ans_r);
    ans += ans_r + ans_l;
    if (count <= k) ans+=count;
    return count;
}


int tree::solve_3_ans (tree_node *tmp, int k)
{
    int ans = 0;
    solve_3 (tmp, k, ans);
    return ans;
}
int tree::solve_3 (tree_node *tmp, int k, int& ans)
{
    int count = 1, l=0, r=0;
    if (tmp -> left ) l = solve_3 (tmp -> left,  k, ans);
    if (tmp -> right) r = solve_3 (tmp -> right, k, ans);
    count += fmax(l, r);
    if (count <= k) ans++;
    return count;
}


int tree::solve_5 (tree_node *tmp, int k)
{
    if(!tmp) return 0;
    if (k == 1) return 1;
    k--;
    return solve_5 (tmp -> left, k) + solve_5 (tmp -> right, k);
}

/*
int tree::solve_5 (tree_node *tmp, int k, int now)
{
    int count = 0;
    if (now == k) return 1;
    now++;
    if (tmp -> left ) count += solve_5 (tmp -> left,  k, now);
    if (tmp -> right) count += solve_5 (tmp -> right, k, now);
    return count;
}
*/


int tree::solve_4_ans (tree_node *tmp, int k)
{
    int n = 0;
    n = depth (root);
    return solve_4 (tmp, k, n);
}

int tree::solve_4 (tree_node *tmp, int k, int n)
{
    if (!tmp) return 0;
    int count = 0;
    for (int i=0; i<n; i++)
    {
        int width = width_of_level (tmp, i);
        if (width > count) count = width_of_level (tmp, i);
        if (width > k) break;
    }
    //tmp->print();
    if (count <= k) return amount_of_elements (tmp);
    n--;
    return solve_4 (tmp -> left,  k, n) + solve_4 (tmp -> right, k, n);
}

int tree::amount_of_elements (tree_node *tmp)
{
    if (!tmp) return 0;
    return amount_of_elements (tmp -> left) + amount_of_elements (tmp -> right) + 1;
}

int tree::depth (tree_node *tmp)
{
    if (!tmp) return 0;
    int l = depth (tmp -> left );
    int r = depth (tmp -> right);
    return (1 + (l > r ? l : r));
}

int tree::width_of_level(tree_node *tmp, int need)
{
    if(!tmp) return 0;
    if (need == 0) return 1;
    need--;
    return width_of_level (tmp -> left, need) + width_of_level (tmp -> right, need);
}
