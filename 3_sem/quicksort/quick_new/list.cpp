#include "student.h"
#include "list_node.h"
#include "list.h"
#include "addition.h"

void list::delete_list ()
{
        while (head)
        {
            current = head;
            head = head -> next;
            delete current;
        }
        delete head;
}

int list::read (FILE *fp)
{
	int ret;
	delete_list ();
	list_node *next;

	next = new list_node ();
	if (!next) return ERROR_NOT_ENOUGH_MEMORY;
	ret = next -> read (fp);
	if (ret != 0) return delete next, ret;

	head = current = next; 
	for (;;)
	{
		next = new list_node;
		if (!next) return ERROR_NOT_ENOUGH_MEMORY;
		ret = next -> read (fp);
		if (ret != 0) return delete next, ret;

		current -> next = next;
		current = next;
		next = nullptr;
	}
	return 0;
}

void list::print (FILE *out)
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


void list::bubble_sort(bool (*cmp)(list_node* x, list_node* y))
{
    int n =length();
    bool sorted;
    for (int i = 0; i < n; i++)
    {
        sorted = true;
        current = head;
        list_node *e = current -> next;
        if (!e) return;
        list_node *f = e -> next;

        if (!cmp(current, e))
        {
            sorted = false;
            e -> next = current;
            current -> next = f;
            head = e;
        }

        current = head;
        for (int j = 0; j < n-i-2; j++)
        {
            list_node *b = current -> next;
            list_node *e = b -> next;
            if (!e) return;
            if (!cmp(b, e)) 
            {
                sorted = false;
                list_node *f = e -> next;
                b -> next = f;
                e -> next = b;
                current -> next = e;
            }
            current = current -> next;
        }
        if (sorted) return;
    }
}



void list::min_elem_sort (bool (*cmp)(list_node*, list_node*))
{
    list_node *min;
    list b;
    while (head)
    {
        min = head;
        for (current = head; current -> next; current = current -> next)
            if (cmp(current -> next, min -> next)) min = current;

        if ( !(min -> next) || cmp(head, min -> next)) b.add_next (cut_head ());
        else
        {
            current = min;
            b.add_next (cut_next ());
        }
    }
    head = b.head;
    b.head = nullptr;
    b.delete_list();
}



void list::max_elem_sort (bool (*cmp)(list_node*, list_node*))
{
    list_node *max;
    list b;
    while (head)
    {
        max = head;
        for (current = head; current -> next; current = current -> next)
            if (cmp(max -> next, current -> next)) max = current;

        if ( !(max -> next) || cmp(max -> next, head)) b.add_before_head (cut_head ());
        else 
        {
            current = max;
            b.add_before_head (cut_next ());
        }

    }

    head = b.head;
    b.head = nullptr;
    b.delete_list();  
}


void list::linear_insertion_sort (bool (*cmp)(list_node *, list_node *))
{
    bool fl;
    list_node *i = head, *j;
    while (i -> next)
    {
        fl = true;
        j = head;
        if (cmp (i -> next, j))
        {
            fl = false;
            current = i;
            list_node *tmp = cut_next();
            add_before_head (tmp);
        }
        else
        {
            for (j = head; j != i ; j = j -> next)
            {
                if (cmp (i -> next, j -> next))
                {
                    fl = false;
                    insert (j, i);
                    break;
                }
            }
        }
        if(fl) i = i -> next;
    }
}

void list::insert (list_node *j, list_node *i)
{
    list_node *b = j -> next, *e = i -> next, *f = e -> next;
    i -> next = f;
    j -> next = e;
    e -> next = b;
}




void list::Neuman_sort (bool (*cmp)(list_node*, list_node*)){
    list_node *cur_head, *last;
    if (!head) return;
    size_t k = 1;
    while (true) {
        head = merge (head, k, last, cmp);
        if (!(last -> next)) return;
        while (last -> next) 
        {
            cur_head = last;
            cur_head -> next = (merge (last -> next, k, last, cmp) );
        }
        k *= 2;
    }
    return;
}

list_node * list::merge (list_node *cur_head, size_t k, list_node * & last, bool (*cmp)(list_node *, list_node *)) {
    list_node *ret, *beg1, *end1, *beg2, *end2, *tail;
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
        if (cmp(beg1, beg2)) { last -> next = beg1; last = beg1; beg1 = beg1 -> next; } 
        else                 { last -> next = beg2; last = beg2; beg2 = beg2 -> next; }
    }

    if (beg1) { last -> next = beg1; last = end1; } 
    else      { last -> next = beg2; last = end2; }
    last -> next = tail;
    return ret;
}



/*

void list::_quick_sort (list_node *first, list_node *end, bool (*cmp)(list_node *, list_node *))
{
    list_node *curr, *first_min, *first_max, *min, *max;
    int l_min = 0, l_max = 0;

    if(first || (first -> next == end))
    {
        while (first -> next != end)
        {
            min = first_min= nullptr;
            max = first_max = first;
            l_min = 0; l_max = 1;
            
            for (curr = first -> next; curr != end; curr = curr -> next)
            {
                if (cmp(curr,first))
                {
                    if (!min) { first_min = curr; min = first_min; }
                    else { min -> next = curr; min = curr; }
                    l_min++;
                }
                else { max -> next = curr; max = curr; l_max++; }
            }

            if (first_min)
            {
                max -> next = end;
                min -> next = first_max;
                if (first == head) head = first_min;
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

*/


list_node * list::select_elem(list_node *first, list_node *end)
{
    double sum = 0, dif = 0, min_dif = 0;
    int n = 0, y = 0;
    list_node *curr, *elem = nullptr;

    for(curr = first;  curr != end; curr = curr -> next)
    {
        sum += (curr -> hash());
        n++;
    }
    sum /= n;

    y = head -> hash();
    min_dif = dif = (sum > y) ? sum - y : y - sum;

    for(curr = first;  curr -> next != end; curr = curr -> next)
    {
        y = curr -> next -> hash();
        dif = (sum > y) ? sum - y : y - sum;
        if (dif <= min_dif) { min_dif = dif; elem = curr; }
    }
    return elem;
}



void list::_quick_sort (list_node *first, list_node *end, list_node *prefirst, bool (*cmp)(list_node *, list_node *))
{
    list_node *curr, *first_min, *first_max, *min, *max, *prev2, *prefirst1, *prev1, *tmp, *prev_tmp;
    int l_min = 0, l_max = 0;

//    printf("\n\nlist1\n");
//    for (curr = first; curr != end; curr = curr -> next) curr -> print();

    tmp = select_elem(first, end);

    printf("\nsredni\n");
    if(tmp) tmp -> next -> print();

//    printf("\n\ntmp ");
//    if (tmp) tmp -> print();
//    else printf("0");

    if(tmp) 
    {   
        prev_tmp = tmp;
//        printf("\nprev tmp ");
//        prev_tmp -> print();

        tmp = tmp -> next;
//        printf("\ntmp ");
//        tmp -> print();

        prev_tmp -> next = tmp -> next;
        tmp -> next = first;
        first = tmp;
        if(prefirst) prefirst -> next = tmp;
        else head = tmp;

//        printf("\nlist1AAAAAA\n");
//        print();
  
    }


//    printf("\n\nSUKA\n");

    //printf("\n\nlist1\n");
    //for (curr = first; curr != end || curr ; curr = curr -> next) curr -> print();


    if(first || (first -> next == end))
    {
        while (first->next != end)
        {

            min = first_min = nullptr;
            max = first_max = first;
            prev2 = prefirst;
            l_min = 0; l_max = 1;

            //tmp = first;
            //printf("\n\ntmp ");
            //tmp -> print();

            for (prev1 = first, curr = first -> next; curr != end; prev1 = curr, curr = curr -> next)
            {
                if (cmp(curr, first))
                {
                    if (!min) { prefirst1 = prev1; first_min = curr; min = first_min; }
                    else { min -> next = curr; min = curr; }
                    l_min++;
                }
                else { max -> next = curr; max = curr; l_max++; }
            }

            if (first_min)
            {
                max -> next = end;
                min -> next = first_max;
                prev2 = min;
                if (first == head) { head = first_min; min -> next = first_max; prefirst1 = nullptr; }
                else { prefirst -> next = first_min; prefirst1 = prefirst; }
            }
            else
            {
                prefirst1 = prev2;
                first_min = first_max;
                prev2 = first_max;
                first_max = first_max -> next;
            }

            if (l_min < l_max)
            {
                _quick_sort (first_min, first_max, prefirst1, cmp);
                first = first_max; prefirst = prev2;
            }
            else
            {
                if (first_max != end && first_max -> next != end)
                    _quick_sort (first_max, end, prev2, cmp);

                end = first_max; first = first_min; prefirst = prefirst1;
            }
        }
    }
}



















//other:________________________________________________________________________________________________________________________________


int list::length()
{
    int n;
    for (current = head, n=0; current; n++,current = current -> next);
    return n;
}

bool list::sort_control (bool (*cmp)(list_node* x, list_node* y))
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




