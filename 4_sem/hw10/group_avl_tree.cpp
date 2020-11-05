#include "group_avl_tree.h"

void group_avl_tree::set_size (int n1, int n2) { size1 = n1; size2 = n2; }


group_avl_tree_node * group_avl_tree::right_rotation(group_avl_tree_node *curr) 
{
	group_avl_tree_node *tmp = curr -> left;
	curr -> left = tmp -> right;
	tmp -> right = curr;
	curr -> fix_height();
	tmp ->  fix_height();
	return tmp;
}

group_avl_tree_node * group_avl_tree::left_rotation(group_avl_tree_node *curr)
{
	group_avl_tree_node *tmp = curr -> right;
	curr -> right = tmp -> left;
	tmp -> left = curr;
	curr -> fix_height();
	tmp ->  fix_height();
	return tmp;
}


group_avl_tree_node * group_avl_tree::balance (group_avl_tree_node *curr)
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

int group_avl_tree::insert (list_node *k) 
{ 
	int ch = 1;
	group_avl_tree_node *tmp = insert_rec (root, k, ch);
	if (ch) return root = tmp, 0;
	else return ERROR_SAME_DATA;
}

group_avl_tree_node * group_avl_tree::insert_rec (group_avl_tree_node *ptr, list_node *k, int& ch) 
{
	if (!ptr) return new group_avl_tree_node (size1, size2, k); 

	if (k -> get_group() == ptr -> get_group())
	{
		if ((ptr -> insert (k)) != 0) ch = 0;
		return ptr;
	}
	

	if (k -> get_group() < ptr -> get_group()) ptr -> left = insert_rec (ptr -> left, k, ch);
	else ptr -> right = insert_rec (ptr -> right, k, ch);
	return balance (ptr);
}


group_avl_tree_node * group_avl_tree::find_min (group_avl_tree_node *ptr)
{
	if (ptr -> left) return find_min (ptr -> left);
	else return ptr;
}

group_avl_tree_node * group_avl_tree::delete_min (group_avl_tree_node *ptr) 
{
	if (ptr -> left == nullptr) return ptr -> right;
	ptr -> left = delete_min (ptr -> left);
	return balance (ptr);
}


void group_avl_tree::delete_current (list_node *k) { root = delete_current_rec (root, k); }
group_avl_tree_node * group_avl_tree::delete_current_rec (group_avl_tree_node *ptr, list_node *k) 
{
	if (!ptr) return nullptr;
	if (k -> get_group() == ptr -> get_group())
		ptr -> delete_current (k);
	
	if (k -> get_group() < ptr -> get_group()) ptr -> left = delete_current_rec (ptr -> left, k);
	else ptr -> right = delete_current_rec (ptr -> right, k);	
	
	return balance(ptr);
}


void group_avl_tree::delete_group_avl_tree (group_avl_tree_node *tmp)
{   
    if (tmp)
    {   
        delete_group_avl_tree (tmp -> left );
        delete_group_avl_tree (tmp -> right);
    }
    if(tmp == root) root = nullptr;
    delete tmp;

}


void group_avl_tree::print (group_avl_tree_node *tmp, int space, FILE *out)
{   
    if(tmp)
    {
    	space++;
    	if (tmp && space<MAX_PRINT) print (tmp -> right, space, out); 
    	printf("\n");
    	for (int i=0; i<space-1; i++) fprintf (out, "        ");
    	printf("=========\n");	
        for (int i=0; i<space-1; i++) fprintf (out, "        ");
        printf("group = %d\n", tmp -> get_group ());
        tmp -> print (space, out);
        
    	if (tmp && space<MAX_PRINT) print (tmp -> left , space, out);         
    }
}


void group_avl_tree::search (group_avl_tree_node *curr, command &line, list_node *&first)
{
	if (!curr) return;
	if (line.oper == OR)
	{
		search (curr -> right, line, first);
        search (curr -> left , line, first);
        curr -> select (line, first);
	}
	else
	{
		switch (line.c_group)
		{
	        case COND_NONE: break;
	        case EQ:
	        {
	        	if (curr -> get_group () == line.get_group()) curr -> select (line, first);
	        	else 
	        	{
		        	if (curr -> get_group () < line.get_group()) search (curr -> right, line, first);
					else search (curr -> left , line, first);
				}
				break;
		
	        } 
	        case LT:
	        {
	        	if (curr -> get_group () >= line.get_group()) search (curr -> left , line, first);
	        	else
	        	{
	        		search (curr -> right, line, first);
		        	search (curr -> left , line, first);
		        	curr -> select (line, first);
	        	}
				break;
	        } 
	        case GT: 
	        {
	        	if (curr -> get_group () <= line.get_group()) search (curr -> right, line, first);
	        	else
	        	{
	        		search (curr -> right, line, first);
		        	search (curr -> left , line, first);
		        	curr -> select (line, first);
	        	}
				break;
	        } 
	        case NE:
	        {
	        	search (curr -> right, line, first);
	        	search (curr -> left , line, first);
	        	if (curr -> get_group () != line.get_group()) curr -> select (line, first);
				break;
		
	        } 

	        case LE:
	        {
	        	if (curr -> get_group () > line.get_group()) search (curr -> left , line, first);
	        	else
	        	{
	        		search (curr -> right, line, first);
		        	search (curr -> left , line, first);
		        	curr -> select (line, first);
	        	}
				break;
	        }
	        case GE: 
	        {
	        	if (curr -> get_group () < line.get_group()) search (curr -> right, line, first);
	        	else
	        	{
	        		search (curr -> right, line, first);
		        	search (curr -> left , line, first);
		        	curr -> select (line, first);
	        	}
				break;
	        } 
	        case LIKE: break;
	                    
		}
	}

}





