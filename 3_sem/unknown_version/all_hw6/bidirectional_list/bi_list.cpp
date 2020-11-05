#include "bi_list.h"
#include "addition.h"

void bi_list::delete_list ()
{
        while (head)
        {
            current = head;
            head = head -> next;
            delete current;
        }
        delete head;
}

int bi_list::read (FILE *fp)
{
	int ret;
	delete_list ();
	bi_list_node *next;

	next = new bi_list_node ();
	if (!next) return ERROR_NOT_ENOUGH_MEMORY;
	ret = next -> read (fp);
	if (ret != 0) return delete next, ret;

    next -> prev = nullptr;
	head = current = next; 
	for (;;)
	{
		next = new bi_list_node;
		if (!next) return ERROR_NOT_ENOUGH_MEMORY;
		ret = next -> read (fp);
		if (ret != 0) return delete next, ret;

		current -> next = next;
        next -> prev = current;
		current = next;
		next = nullptr;
	}
	return 0;
}

void bi_list::print (FILE *out)
{
    int i=0; 
    current=head;
    while(current && i<MAX_PRINT)
    {
        current -> print (out);
        current = current -> next;
        i++;
    }
}

//sort:________________________________________________________________________________________________________________________________



void bi_list::bubble_sort(bool (*cmp)(bi_list_node *x, bi_list_node *y))
{
    int n =length();
    bool sorted;
    for(int i = 0; i < n; i++)
    {
        sorted = true;
        current = head;
        for(int j = 0; j < n-i-1; j++)
            if (!cmp(current, current -> next))
            {
                sorted = false;
                swap(current, current -> next);
            }
        else current = current -> next;
        if (sorted) return;
    }
    
}


void bi_list::min_elem_sort (bool (*cmp)(bi_list_node*, bi_list_node*))
{
    bi_list_node *min;
    bi_list b;
    while (head)
    {
        min = head;
        for (current = head; current; current = current -> next)
            if (cmp(current, min)) min = current;
        current = min;
        b.add_next (cut_current ());
    }

    head = b.head;
    b.head = nullptr;
    b.delete_list();   
}

void bi_list::max_elem_sort (bool (*cmp)(bi_list_node*, bi_list_node*))
{
    bi_list_node *max;
    bi_list b;
    while (head)
    {
        max = head;
        for (current = head; current; current = current -> next)
            if (cmp(max, current)) max = current;
        current = max;
        b.add_before_head (cut_current ());
    }

    head = b.head;
    b.head = nullptr;
    b.delete_list();  
}





void bi_list::linear_insertion_sort (bool (*cmp)(bi_list_node *, bi_list_node *))
{
    bi_list_node *i = head -> next, *j, *z;
    while (i)
    {
        z = i;
        i = i -> next;
        for (j = head; j != z ; j = j -> next)
            if (cmp (z, j)) 
                {
                    insert (j, z);
                    break; 
                }
    }   

}


void bi_list::Neuman_sort (bool (*cmp)(bi_list_node*, bi_list_node*)){
    bi_list_node *cur_head, *last, *tmp;
    if (!head) return;
    size_t k = 1;
    while (true) {
        head = merge (head, k, last, cmp);
        if (!(last -> next)) return;
        while (last -> next) 
        {
            cur_head = last;
            tmp = merge (last -> next, k, last, cmp);
            cur_head -> next = tmp;
            tmp -> prev = cur_head;
        }
        k *= 2;
    }
    return;
}

bi_list_node *  bi_list::merge (bi_list_node *cur_head, size_t k, bi_list_node * & last, bool (*cmp)(bi_list_node *, bi_list_node *)) {
    bi_list_node *ret, *beg1, *end1, *beg2, *end2, *tail;
    size_t i;
    beg1 = end1 = cur_head;

    for (i = 1; i < k; i ++) 
    {
        if (!(end1 -> next)) return last = end1, cur_head;
        end1 = end1 -> next;
    }

    beg2 = end2 = end1 -> next;
    end1 -> next = nullptr;

    if (!beg2) return last = end1, cur_head;

    for (i = 1; i < k && end2 -> next; i++) 
        end2 = end2 -> next;
    
    tail = end2 -> next;
    end2 -> next = nullptr;

    if (cmp(beg1, beg2)) { ret = last = beg1; beg1 = beg1 -> next; } 
    else                 { ret = last = beg2; beg2 = beg2 -> next; }

    while (beg1 && beg2) 
    {
        if (cmp(beg1, beg2)) { last -> next = beg1; beg1 -> prev = last; last = beg1; beg1 = beg1 -> next; } 
        else                 { last -> next = beg2; beg2 -> prev = last; last = beg2; beg2 = beg2 -> next; }
    }

    if (beg1) { last -> next = beg1; beg1 -> prev = last; last = end1; } 
    else      { last -> next = beg2; beg2 -> prev = last; last = end2; }
    last -> next = tail;
    if (tail) tail -> prev = last;
    return ret;
}





void bi_list::_quick_sort (bi_list_node *first, bi_list_node *end, bool (*cmp)(bi_list_node *, bi_list_node *))
{
    bi_list_node *curr, *first_min, *first_max, *min, *max, *prev;
    int l_min = 0, l_max = 0;

    if(first || (first -> next == end))
    {
        while (first -> next != end)
        {
            min = first_min= nullptr;
            max = first_max = first;
            l_min = 0; l_max = 1;
            if (first != head) prev = first -> prev;

            for (curr = first -> next; curr != end; curr = curr -> next)
            {
                if (cmp(curr,first))
                {
                    if (!min) { first_min = curr; min = first_min; }
                    else { min -> next = curr; curr -> prev = min; min = curr; }
                    l_min++;
                }
                else { max -> next = curr; curr -> prev = max; max = curr; l_max++; }
            }

            if (first_min)
            {
                max -> next = end;
                if (end) end-> prev = max;
                min -> next = first_max;
                first_max-> prev = min;
                if (first == head) head = first_min;
                else { prev -> next = first_min; first_min-> prev = prev; }
            }
            else { first_min = first_max; first_max = first_max -> next; }

            if (l_min < l_max)
            {
                _quick_sort (first_min, first_max, cmp);
                first = first_max;
            }
            else
            {
                if (first_max != end && first_max -> next != end) _quick_sort (first_max, end, cmp);
                end = first_max; first = first_min;
            }
        }
    }
}



//other:________________________________________________________________________________________________________________________________

void bi_list::swap (bi_list_node *b, bi_list_node *e)
{
    bi_list_node *a = b -> prev;
    bi_list_node *f = e -> next;
    e -> next = b;
    b -> prev = e;
    if (a) a -> next = e;
    e -> prev = a;
    if (f) f -> prev = b;
    b -> next = f;
    if(!a) head = e;
}

void bi_list::insert (bi_list_node *j, bi_list_node *i)
{

    bi_list_node *a = j -> prev;
    current = i;
    bi_list_node *tmp = cut_current();

    tmp -> next = j;
    tmp -> prev = a;
    j -> prev =tmp;
    if (a) a -> next = tmp;
    else head = tmp;
}

int bi_list::length()
{
    int n;
    for (current = head, n=0; current; n++,current = current -> next);
    return n;
}

bool bi_list::sort_control (bool (*cmp)(bi_list_node* x, bi_list_node* y))
{
    if (is_empty()) return true;
    current = head;
    while(current -> next)
    {
        if(!cmp(current, current -> next) && ( *current < *(current -> next) || *current > *(current -> next) ) ) return false;
        current = current -> next;
    }
    return true;
}

//________________________________________________________________________________________________________________________________
/*
void bi_list::bubble_sort(bool (*cmp)(bi_list_node* x, bi_list_node* y))
{
    bi_list_node *l = head;
    bi_list_node *r = head -> next;
    while (l -> next)
    {
        while (r)
        {
            if (!cmp(l, r)) 
            {
                //(*l).swap(*r);
                swap(l,r);
                l = r;
            }
            r = r -> next;

        }
        l = l -> next;                  
        r = l -> next;
    }

}
*/

/*

void bi_list::exchange (bi_list_node* b, bi_list_node* e)
{

    if (b == e) return;
    bi_list_node *a = b -> prev;
    bi_list_node *c = b -> next;
    bi_list_node *d = e -> prev;
    bi_list_node *f = e -> next;

    if ( c == e )
    {
        e -> next = b;
        b -> prev = e;
    }
    else
    {
        c -> prev = e;
        e -> next = c;

        d -> next = b;
        b -> prev = d;

    }

    if (a) a -> next = e; 
    e -> prev = a;

    if (f) f -> prev = b;
    b -> next = f;

    if(!a) head = e;

}
*/
