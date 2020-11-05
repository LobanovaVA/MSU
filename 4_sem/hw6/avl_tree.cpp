#include "avl_tree.h"


avl_tree_node * avl_tree::right_rotation(avl_tree_node *curr) 
{
	avl_tree_node *tmp = curr -> left;
	curr -> left = tmp -> right;
	tmp -> right = curr;
	curr -> fix_height();
	tmp ->  fix_height();
	return tmp;
}

avl_tree_node * avl_tree::left_rotation(avl_tree_node *curr)
{
	avl_tree_node *tmp = curr -> right;
	curr -> right = tmp -> left;
	tmp -> left = curr;
	curr -> fix_height();
	tmp ->  fix_height();
	return tmp;
}


avl_tree_node * avl_tree::balance (avl_tree_node *curr)
{
	curr -> fix_height();
	if (curr -> get_balance() == 2)
	{
		if (curr -> right -> get_balance() < 0)
			curr -> right = right_rotation (curr -> right);
		return left_rotation (curr);
	}
	if (curr -> get_balance() == -2)
	{
		if (curr -> left -> get_balance() > 0)
			curr -> left = left_rotation (curr -> left);
		return right_rotation (curr);
	}
	return curr;
}

int avl_tree::insert (list_node *k) 
{ 
	int ch = 1;
	avl_tree_node *tmp = insert_rec (root, k, ch);
	if (ch) return root = tmp, 0;
	else return ERROR_SAME_DATA;
}

avl_tree_node * avl_tree::insert_rec (avl_tree_node *ptr, list_node *k, int& ch) 
{
	if (!ptr) return new avl_tree_node (k); 
	if (*k == *(ptr -> orig)) return ch = 0, ptr;
	if (*k < *(ptr -> orig)) ptr -> left = insert_rec(ptr -> left, k, ch);
	else ptr -> right = insert_rec(ptr -> right, k, ch);
	return balance (ptr);
}


avl_tree_node * avl_tree::find_min (avl_tree_node *ptr)
{
	if (ptr -> left) return find_min (ptr -> left);
	else return ptr;
}

avl_tree_node * avl_tree::delete_min (avl_tree_node *ptr) 
{
	if (ptr -> left == nullptr) return ptr -> right;
	ptr -> left = delete_min (ptr -> left);
	return balance (ptr);
}


void avl_tree::delete_current (list_node *k) { root = delete_current_rec (root, k); }
avl_tree_node * avl_tree::delete_current_rec (avl_tree_node *ptr, list_node *k) 
{
	if (!ptr) return nullptr;
	if (k == ptr -> orig)
	{
		avl_tree_node *l = ptr -> left, *r = ptr -> right;
		delete ptr;
		if (!r) return l;
		avl_tree_node *min = find_min(r);
		min -> right = delete_min (r);
		min -> left = l;
		return balance (min);
	}
	if (*k < *(ptr -> orig)) ptr -> left = delete_current_rec (ptr -> left, k);
	else ptr -> right = delete_current_rec (ptr -> right, k);	
	
	return balance(ptr);
}


void avl_tree::delete_avl_tree (avl_tree_node *tmp)
{   
    if (tmp)
    {   
        delete_avl_tree (tmp -> left );
        delete_avl_tree (tmp -> right);
    }
    if(tmp == root) root = nullptr;
    delete tmp;

}


void avl_tree::print (avl_tree_node *tmp, int space, FILE *out)
{   
    if(tmp)
    {
    	space++;
    	if (tmp && space<MAX_PRINT) print (tmp -> right, space, out); 

        for (int i=0; i<space-1; i++) fprintf (out, "        ");
        tmp -> orig -> print ();
        
    	if (tmp && space<MAX_PRINT) print (tmp -> left , space, out);         
    }
}


list_node * avl_tree::search (avl_tree_node *curr, command &line)
{
	list_node *head_found = nullptr;
	while (curr && curr -> orig -> get_phone() != line.get_phone())
	{
		if (curr -> orig -> get_phone() < line.get_phone()) curr = curr -> right;
		else curr = curr -> left;
	}

	if (curr) head_found = curr -> orig;
	else return nullptr;

	search_next_found (curr -> left , line, search_next_found (curr -> right, line, head_found));
	if (check (curr -> orig, line)) return head_found;
	else
	{
		list_node *tmp = head_found -> next_found;
		head_found -> next_found = nullptr;
		return tmp;
	}
}

list_node * avl_tree::search_next_found (avl_tree_node *curr, command &line, list_node *curr_found)
{
	if (!curr) return curr_found;
	curr_found = search_next_found (curr -> right, line, curr_found);
    curr_found = search_next_found (curr -> left , line, curr_found);
	if (curr -> orig -> get_phone() == line.get_phone()) 
		if (check (curr -> orig, line))
		{
			curr_found -> next_found = curr -> orig;
            curr_found = curr  -> orig;
            curr -> orig -> next_found = nullptr;
			return curr -> orig;
		}
	return curr_found;
}



list_node * avl_tree::search_or (avl_tree_node *curr, command &line, list_node* &res_or)
{
	list_node *head_found = nullptr;
	while (curr && curr -> orig -> get_phone() != line.get_phone())
	{
		if (curr -> orig -> get_phone() < line.get_phone()) curr = curr -> right;
		else curr = curr -> left;
	}
	
	if (curr) head_found = curr -> orig;
	else return nullptr;

	res_or = search_next_found_or (curr -> left , line, search_next_found_or (curr -> right, line, head_found));
	if (!check (curr -> orig, line)) return head_found;
	else 
	{
		list_node *tmp = head_found -> next_found;
		head_found -> next_found = nullptr;
		return tmp;
	}
}

list_node * avl_tree::search_next_found_or (avl_tree_node *curr, command &line, list_node *curr_found)
{
	if (!curr) return curr_found;
	curr_found = search_next_found_or (curr -> right, line, curr_found);
    curr_found = search_next_found_or (curr -> left , line, curr_found);
	if (curr -> orig -> get_phone() == line.get_phone()) 
		if (!check (curr -> orig, line))
		{
			curr_found -> next_found = curr -> orig;
            curr_found = curr  -> orig;
            curr_found -> next_found = nullptr;
			return curr_found;
		}
	return curr_found;
}








