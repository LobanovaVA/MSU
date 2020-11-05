#include "group_avl_tree_node.h"


group_avl_tree_node::group_avl_tree_node (int n1, int n2, list_node *k) 
{ 
    left = right = 0; height = 1;
    size1 = n1; size2 = n2;
    search1.set_size (size1);
    search2 = new avl_tree [size2];
    if (k) 
    {
        group = k -> get_group();
        insert (k);
    }
}

void group_avl_tree_node::delete_current (list_node *k)
{
    int p = phone_hash (k -> get_phone(), size2);
    search2[p].delete_current (k);
    search1.delete_current (k);
}


void group_avl_tree_node::print (int space, FILE* out)
{
    search1.print (space, out);
    printf("\n");
    for (int i = 0; i < space-1; i++) fprintf (out, "        ");
    printf("HASH_TREE:");

    for (int i = 0; i < size2; i++)
    {
        printf("\n");
        for (int i = 0; i < space-1; i++) fprintf (out, "        ");
        fprintf(out, "tree[%2d]:\n", i);
        search2[i].print (search2[i].get_root (), space, out);
    }
}

int group_avl_tree_node::insert (list_node *elem)
{
	int p = phone_hash (elem -> get_phone(), size2);
	if (search2[p].insert(elem)) return ERROR_SAME_DATA;
	
    search1.insert (elem);
    return 0;
}


void group_avl_tree_node::select (command &line, list_node *&first)
{
    if (line.oper == OR && check_group (group, line))
    { 
        no_search(first); 
        return; 
    }

    if (line.c_name  == EQ)
    {
        int n = name_hash (line.get_name(), size1);
        search1.search (search1.arr[n], line, first);
        return;
    }

    if (line.c_phone == EQ)
    {
        int p = phone_hash (line.get_phone(), size2);
        search2[p].search (search2[p].get_root(), line, first);
        return;
    }

    def_search (line, first);
    return;
}


void group_avl_tree_node::no_search (list_node *&first)
{
    hash_node *curr;
    for (int n = 0; n < size1; n++)
    {
        for (curr = search1.arr[n]; curr; curr = curr -> next)
        { 
            curr -> orig -> next_found = first; 
            first = curr -> orig;
        }
    }
}

void group_avl_tree_node::def_search (command &line, list_node *&first)
{
    hash_node *curr;
    for (int n = 0; n < size1; n++)
    {
        for (curr = search1.arr[n]; curr; curr = curr -> next)
            if (check (curr -> orig, line)) 
            { 
                curr -> orig -> next_found = first; 
                first = curr -> orig;
            }
    }
}


int check_group (int gr, command &line)
{
    int fl = 0;
    switch (line.c_group)
    {
        case COND_NONE: break;
        case EQ: if (gr == line.get_group()) fl = 1; break;
        case LT: if (gr <  line.get_group()) fl = 1; break;
        case GT: if (gr >  line.get_group()) fl = 1; break;
        case NE: if (gr != line.get_group()) fl = 1; break;
        case LE: if (gr <= line.get_group()) fl = 1; break;
        case GE: if (gr >= line.get_group()) fl = 1; break;
        case LIKE: break;
    }
    return fl;

}

int check (list_node *curr, command &line) 
{
    if (line.c_name == COND_NONE && line.c_phone == COND_NONE && line.c_group == COND_NONE) return 1;
    int fl_n = 0;
    switch (line.c_name)
    {
        case COND_NONE: break;
        case EQ: if (strcmp (curr -> get_name(), line.get_name()) == 0) fl_n = 1; break;
        case LT: if (strcmp (curr -> get_name(), line.get_name()) <  0) fl_n = 1; break;
        case GT: if (strcmp (curr -> get_name(), line.get_name()) >  0) fl_n = 1; break;
        case NE: if (strcmp (curr -> get_name(), line.get_name()) != 0) fl_n = 1; break;
        case LE: if (strcmp (curr -> get_name(), line.get_name()) <= 0) fl_n = 1; break;
        case GE: if (strcmp (curr -> get_name(), line.get_name()) >= 0) fl_n = 1; break;
        case LIKE: if (like (curr -> get_name(), line.get_name())) fl_n = 1; break;
    }

    int fl_p = 0;
    switch (line.c_phone)
    {
        case COND_NONE: break;
        case EQ: if (curr -> get_phone() == line.get_phone()) fl_p = 1; break;
        case LT: if (curr -> get_phone() <  line.get_phone()) fl_p = 1; break;
        case GT: if (curr -> get_phone() >  line.get_phone()) fl_p = 1; break;
        case NE: if (curr -> get_phone() != line.get_phone()) fl_p = 1; break;
        case LE: if (curr -> get_phone() <= line.get_phone()) fl_p = 1; break;
        case GE: if (curr -> get_phone() >= line.get_phone()) fl_p = 1; break;
        case LIKE: break;
    }

    int fl_g = 0;
    switch (line.c_group)
    {
        case COND_NONE: break;
        case EQ: if (curr -> get_group() == line.get_group()) fl_g = 1; break;
        case LT: if (curr -> get_group() <  line.get_group()) fl_g = 1; break;
        case GT: if (curr -> get_group() >  line.get_group()) fl_g = 1; break;
        case NE: if (curr -> get_group() != line.get_group()) fl_g = 1; break;
        case LE: if (curr -> get_group() <= line.get_group()) fl_g = 1; break;
        case GE: if (curr -> get_group() >= line.get_group()) fl_g = 1; break;
        case LIKE: break;
    }

    int ans = 0;
    switch (line.oper)
    {
        case OP_NONE:
        {
            ans = fl_n + fl_p + fl_g;
            break;
        }
        case AND:
        {
            if (line.c_name  != COND_NONE && line.c_phone != COND_NONE) ans = fl_n * fl_p;
            if (line.c_name  != COND_NONE && line.c_group != COND_NONE) ans = fl_n * fl_g;
            if (line.c_phone != COND_NONE && line.c_group != COND_NONE) ans = fl_p * fl_g;
            break;
        }
        case OR:
        {
            if (line.c_phone == EQ && line.c_name == EQ) fl_p = 0;
            ans = fl_n + fl_p + fl_g;
            break;
        }
    }

    if (ans != 0) return 1;
    return 0;
    //printf("%d %d %d %d\n", fl_n, fl_p, fl_p, ans);
}



