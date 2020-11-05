#include "v_tree.h"
#include "addition.h"
#include <math.h>

int v_tree::read (FILE *fp)
{
    int ret;
    delete_tree (root);
    v_tree_node *elem;

    elem = new v_tree_node();
    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
    ret = elem -> read (fp);
    if (ret !=0) return delete elem, ret;
    root = current = elem;
    for (;;)
    {
        elem = new v_tree_node();
        if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
        ret = elem -> read (fp);
        if (ret != 0) return delete elem, ret;
        //if (!add_elem(elem, root)) return delete elem, ERROR_CANNOT_READ_CLASS;
        add_elem(elem, root);
        elem = nullptr;
    }
    return 0;
}

void v_tree::print (v_tree_node *tmp, int space, FILE *out)
{

    if(tmp)
    {
        for (int i=0; i<space; i++) fprintf (out, "    ");
        tmp -> print ();
        if (tmp && space<MAX_PRINT)
        {
            space++;
            v_tree_node *ptr;
            ptr = tmp -> child;     
            if (ptr) 
                {
                    print (ptr, space, out);
                    ptr = ptr -> brother;
                    if(ptr)
                    {
                        print (ptr, space, out);
                        ptr = ptr -> brother;
                        if(ptr) print (ptr, space, out);
                    }
                }
        }
    }
}


//navigation:______________________________________________________________________________________________


v_tree_node * v_tree::get_child () const
{
    if (current) return current -> child;
    else return nullptr;
}

v_tree_node * v_tree::get_brother () const
{
    if (current) return current -> brother;
    else return nullptr;
}

bool v_tree::go_child ()
{
    if (current) return current = current -> child,  true;
    else return false;
}

bool v_tree::go_brother ()
{
    if (current) return current = current -> brother, true;
    else return false;

}


//adding:______________________________________________________________________________________________

bool v_tree::add_root (v_tree_node *elem)
{
    if (this -> root) return false;
    return this -> root = elem, true;
}

bool v_tree::add_child (v_tree_node *elem)
{
    if (current -> child) return false;
    return current -> child = elem, true;
}

bool v_tree::add_brother (v_tree_node *elem)
{
    if (current == root || current -> brother) return false;
    return current -> brother = elem, true;
}



void v_tree::add_elem(v_tree_node *tmp, v_tree_node *root)
{
    if(!root) { root = tmp; return; }
    else
    {
        if (!(root -> child)) root -> child = tmp;
        else
        {
            v_tree_node *child_1 = root -> child;
            if (!(child_1 -> brother))
            {
                if (*child_1 < *root)
                {
                    if (*tmp < *root) add_elem(tmp, child_1);
                    else child_1 -> brother = tmp;
                }
                else 
                {

                    if (*child_1 > *root)
                    {
                        if (*tmp > *root) add_elem(tmp, child_1);
                        else 
                        {
                            root -> child = tmp;
                            tmp -> brother = child_1;
                        }

                    }
                    else
                    {
                        if (*tmp > *root) child_1 -> brother = tmp;
                        else
                        {
                            if (*tmp < *root)
                            {
                                root -> child = tmp;
                                tmp -> brother = child_1;
                            }
                            else add_elem(tmp, child_1);
                        }
                    }
                }
            }

            else 
            {
                v_tree_node *child_2 = child_1 -> brother;
                if (!(child_2 -> brother))  
                {
                    if(*child_1 < *root && *child_2 > *root)
                    {
                        if (*tmp < *root) add_elem(tmp, child_1);
                        else 
                        {
                            if (*tmp > *root) add_elem(tmp, child_2);
                            else 
                            {
                                child_1 -> brother =tmp;
                                tmp -> brother = child_2;
                            }
                        }
                    }
                    else
                    {
                        if(*child_1 < *root)
                        {
                            if (*tmp > *root) child_2 -> brother = tmp;
                            else 
                            {
                                if (*tmp < *root) add_elem(tmp, child_1);
                                else add_elem(tmp, child_2);
                            }
                        }
                        else 
                        {
                            if (*tmp > *root) add_elem(tmp, child_2);
                            else 
                            {
                                if (*tmp < *root)
                                {
                                    root -> child =tmp;
                                    tmp -> brother = child_1;
                                }
                                else add_elem(tmp, child_1);
                            }
                        }
                    }
                } 
                else 
                {
                    v_tree_node *child_3 = child_2 -> brother;
                    if (*tmp < *root) add_elem(tmp, child_1);
                    else 
                    {
                        if (*tmp > *root) add_elem(tmp, child_3);
                        else add_elem(tmp, child_2);
                    }
                }                           
            }
        }
    }
    return;
}



//deleting:______________________________________________________________________________________________

void v_tree::delete_tree (v_tree_node *tmp)
{
    if (tmp)
    {
        delete_tree (tmp -> brother);
        delete_tree (tmp ->  child );
    }
    if(tmp == root) root = nullptr;
    delete tmp;

}

void v_tree::delete_root ()
{
    if (root && !(root -> child))
    {
        delete root;
        root = nullptr;
    }
}

void v_tree::delete_child ()
{
    
    v_tree_node *tmp = current -> child;
    if (tmp)
    {
        current -> child = tmp -> brother;
        delete tmp;
    }
}

void v_tree::delete_brother ()
{
    v_tree_node *tmp = current -> brother;
    if (tmp)
    {
        current -> brother = tmp -> brother;
        delete tmp;
    }
}

void v_tree::delete_child_tree  ()  
{   
    if (current) 
    {
        v_tree_node *tmp = current -> child;
        current -> child = tmp -> brother;
        delete_tree (tmp);  
    }
}



//solution:______________________________________________________________________________________________























int v_tree::solve_1 (v_tree_node *tmp, int k)
{
    if (k>3 || !tmp) return 0;
    int count = 0, i=0;
    tmp = tmp -> child;
    for(i = 0; tmp; i++, tmp = tmp -> brother)
        count += solve_1(tmp, k);
    if (i == k) count++;
    return count;
}

int v_tree::solve_2 (v_tree_node *tmp, int k)
{
    if (k==0) return 0;
    int ans = 0;
    _solve_2 (tmp, k, ans);
    return ans;
}
int v_tree::_solve_2 (v_tree_node *tmp, int k, int& ans)
{
    if (!tmp) return 0;
    int count_brother = _solve_2 (tmp -> brother,  k, ans);
    int count_child = 1 + _solve_2 (tmp -> child,  k, ans);
    if (count_child <= k) ans += count_child;
    return count_child + count_brother;
}
        
    
int v_tree::solve_3 (v_tree_node *tmp, int k)
{
    if (k==0) return 0;
    int ans = 0;
    _solve_3 (tmp, k, ans);
    return ans;
}
int v_tree::_solve_3 (v_tree_node *tmp, int k, int& ans)
{
    if (!tmp) return 0;
    int count_brother = _solve_3 (tmp -> brother,  k, ans);
    int count_child = 1 + _solve_3 (tmp -> child,  k, ans);
    int count = fmax(count_child, count_brother);
    if (count_child <= k) ans += amount_of_elements(tmp); 
    return count;
}



int v_tree::solve_5 (v_tree_node *tmp, int k)
{
    if (!tmp) return 0;
    if (k == 1) return 1;
    k--;
    int count = 0;
    for(tmp = tmp -> child; tmp; tmp = tmp -> brother)
        count += solve_5(tmp, k);
    return count;
}

int v_tree::solve_6 (v_tree_node *tmp, int k)
{
    if(!tmp) return 0;
    if (k == 1)
        {
            if(!( tmp -> child)) return 1;
            else return 0;
        }
    k--;

    int count = 0;
    for(tmp = tmp -> child; tmp; tmp = tmp -> brother)
        count += solve_6(tmp, k);
    if (count) count++;
    return count;
    
}





int v_tree::solve_4 (v_tree_node *tmp, int k)
{
    if (k==0) return 0;
    int n = 0;
    n = depth (root);
    return _solve_4 (tmp, k, n);
}

int v_tree::_solve_4 (v_tree_node *tmp, int k, int n)
{
    if (!tmp) return 0;
    int count = 0, ans = 0;
    for (int i=0; i<n; i++)
    {
        int width = width_of_level (tmp, i);
        if (width > count) count = width;
        if (width > k) break;
    }
    if (count <= k) ans += amount_of_elements (tmp);
    n--;

    
    for(tmp = tmp -> child; tmp; tmp = tmp -> brother)
        ans +=_solve_4 (tmp, k, n);  
    return ans;
         
}

int v_tree::amount_of_elements (v_tree_node *tmp)
{
    if (!tmp) return 0;
    int count = 1;
    for(tmp = tmp -> child; tmp; tmp = tmp -> brother)
        count += amount_of_elements(tmp);
    return count;
}

int v_tree::depth (v_tree_node *tmp)
{
    if (!tmp) return 0;
    int max = 0;
    for(tmp = tmp -> child; tmp; tmp = tmp -> brother)
        max = fmax (max, depth (tmp));
    return 1 + max;
}

int v_tree::width_of_level (v_tree_node *tmp, int need)
{
    if (!tmp) return 0;
    if (need == 0) return 1;
    need--;
    int count = 0;
    for(tmp = tmp -> child; tmp; tmp = tmp -> brother)
        count += width_of_level(tmp, need);
    return count;
}






































/*
int v_tree::solve_1 (v_tree_node *tmp, int k)
{
    if (k>3) return 0;
    int count = 0, child_count=0;
    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        child_count++;
        count += solve_1 (child_1,  k);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            child_count++;
            count += solve_1 (child_2,  k);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3)
            {
                child_count++;
                count += solve_1 (child_3,  k);
            }
        }
    }
    if (k == child_count) count++;
    return count;
}



int v_tree::solve_2 (v_tree_node *tmp, int k)
{
    if (k==0) return 0;
    int ans = 0;
    _solve_2 (tmp, k, ans);
    return ans;
}
int v_tree::_solve_2 (v_tree_node *tmp, int k, int& ans)
{
    int count = 1, ans_1 = 0, ans_2 = 0 , ans_3 = 0;
    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        count += _solve_2 (child_1,  k, ans_1);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            count += _solve_2 (child_2,  k, ans_2);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3) count += _solve_2 (child_3,  k, ans_3);
        }
    }
    ans += ans_1 + ans_2 + ans_3;
    if (count <= k) ans+=count;
    return count;
}



int v_tree::solve_3 (v_tree_node *tmp, int k)
{
    if (k==0) return 0;
    int ans = 0;
    _solve_3 (tmp, k, ans);
    return ans;
}
int v_tree::_solve_3 (v_tree_node *tmp, int k, int& ans)
{
    int count = 1, ans_1 = 0, ans_2 = 0, ans_3 = 0;
    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        ans_1 = _solve_3 (child_1,  k, ans);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            ans_2 = _solve_3 (child_2,  k, ans);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3) ans_3= _solve_3 (child_3,  k, ans);
                
        }
    }
    count += fmax(ans_1, fmax(ans_2, ans_3));
    if (count <= k) ans+=amount_of_elements(tmp); 
    return count;
}



int v_tree::solve_4 (v_tree_node *tmp, int k)
{
    if (k==0) return 0;
    int n = 0;
    n = depth (root);
    return _solve_4 (tmp, k, n);
}

int v_tree::_solve_4 (v_tree_node *tmp, int k, int n)
{
    if (!tmp) return 0;
    int count = 0, ans = 0;
    for (int i=0; i<n; i++)
    {
        int width = width_of_level (tmp, i);
        if (width > count) count = width;
        if (width > k) break;
    }
    if (count <= k) ans += amount_of_elements (tmp);
    n--;

    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        ans += _solve_4 (child_1, k, n);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            ans += _solve_4 (child_2, k, n);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3) ans += _solve_4 (child_3, k, n);  
        }
    }
    return ans;
}




int v_tree::solve_5 (v_tree_node *tmp, int k)
{
    if(!tmp) return 0;
    if (k == 1) return 1;
    k--;

    int count = 0;
    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        count += solve_5 (child_1,  k);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            count += solve_5 (child_2,  k);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3) count += solve_5 (child_3,  k);
        }
    }
    return count;
}



int v_tree::solve_6 (v_tree_node *tmp, int k)
{
    if(!tmp) return 0;
    if (k == 1)
        {
            if(!( tmp -> child)) return 1;
            else return 0;
        }
    k--;

    int count = 0;
    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        count += solve_6 (child_1,  k);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            count += solve_6 (child_2,  k);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3) count += solve_6 (child_3,  k);
        }
    }
    if (count) count++;
    return count;
}


int v_tree::amount_of_elements (v_tree_node *tmp)
{
    if (!tmp) return 0;
    int count = 1;
    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        count += amount_of_elements (child_1);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            count += amount_of_elements (child_2);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3) count += amount_of_elements (child_3);  
        }
    }
    return count;
}


int v_tree::depth (v_tree_node *tmp)
{
    if (!tmp) return 0;
    int ans_1 = 0, ans_2 = 0, ans_3 = 0;
    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        ans_1 = depth (child_1);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            ans_2 = depth (child_2);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3) ans_3= depth (child_3);
        }
    }
    return 1 + fmax(ans_1, fmax(ans_2, ans_3));

}


int v_tree::width_of_level(v_tree_node *tmp, int need)
{
    if (!tmp) return 0;
    if (need == 0) return 1;
    need--;
    int count = 0;
    v_tree_node *child_1 = tmp -> child;
    if (child_1)
    {
        count += width_of_level (child_1, need);
        v_tree_node *child_2 = child_1 -> brother;
        if (child_2)
        {
            count += width_of_level (child_2, need);
            v_tree_node *child_3 = child_2 -> brother;
            if (child_3) count += width_of_level (child_3, need);
        }
    }
    return count;
}

*/
