#include "v_tree.h"
#include "addition.h"
#include <math.h>

b_tree (int order)  
{   
    this -> root = nullptr; 
    this -> current = nullptr; 
    this -> order = order;  
}


int b_tree::read(FILE *fp)
{
    student buf; int i = 0;

    int ret;
    delete_tree (root);
    b_tree_node *elem;

    elem = new v_tree_node();
    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
    ret = elem -> read (fp);
    if (ret !=0) return delete elem, ret;



    b_tree_node ret1 = 0, ret2;
    b_tree_node * retP1 = &ret1, * retP2 = &ret2;

    student *res = insert(&((new student) -> move(buf)), 0, &retP1, &retP2);
    if(res) {insert_node(res, 0, &retP1, &retP2);}
    i++;


    while(1) 
    {
    if(!buf.read(fp)) {fclose(fp); return i;}
    student * res = insert(&((new student) -> move(buf)), 0, &retP1, &retP2);
    if(res) {insert_node(res, 0, &retP1, &retP2);}
    i++;
    }
}


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



//adding:______________________________________________________________________________________________




//deleting:______________________________________________________________________________________________


void b_tree::delete_tree(b_tree_node *root)
{
    if(!root) return;
    for(int i = 0; i < root -> size + 1; i++)
        delete_tree (root -> children[i]);
    root -> delete_node();
    delete root;
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
        
  


/*
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

 
*/


///*

int v_tree::solve_3 (v_tree_node *tmp, int k)
{
    if (k==0) return 0;
    int len = 0, elem = 0;
    return _solve_3 (tmp, k, len, elem);
}
int v_tree::_solve_3 (v_tree_node *tmp, int k, int& len, int& elem)
{
    if (!tmp) return 0;
    int ans = 0, elem_1 = 0, elem_2 = 0, len_1 = 0, len_2 = 0;
    
    ans += _solve_3 (tmp -> brother, k, len_1, elem_1); 
    ans += _solve_3 (tmp -> child,   k, len_2, elem_2); 
    
    if(len_2 + 1 <= k) ans += elem_2 + 1;
    elem = elem_1 + elem_2 + 1;
    if(len_2 + 1 > len_1) len = len_2 + 1;
    else len = len_1;
    return ans;
}

//s*/


/*

static int elems = 0;
static int t_len = 0;

int v_tree::solve_3 (v_tree_node *tmp, int k)
{
    if(!root) return 0;
    _solve_3(tmp, k);
    return elems;
}
int v_tree::_solve_3 (v_tree_node *tmp, int k)
{
    if (k==0 && !tmp) return 0;
    int ans = 0, count = 0, len = 0;
    
    while (tmp)
    {
        count = _solve_3 (tmp -> child, k) + 1;
        t_len ++;
        len = (len>t_len ? len : t_len);
        if(t_len<=k) elems += count;
        ans += count;
        if ((tmp = tmp -> brother)) t_len = 0;
        else t_len = len;
    }
    return ans;
}

*/





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
