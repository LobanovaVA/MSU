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






/*
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
*/

double list::get_average(list_node *first, list_node *end)
{
    double sum = 0;
    int n = 0;
    list_node *curr;

    for(curr = first;  curr != end; curr = curr -> next)
    {
        sum += (curr -> hash());
        n++;
    }
    return (sum /= n);
}



/*
void list::get_average(list_node *first, list_node *end, student& elem)
{
    double value = 0;
    int symbol = 0, n = 0;
    list_node *curr;

    for(curr = first;  curr != end; curr = curr -> next)
    {
        value  += (*curr).get_value();
        symbol += (int)((*curr).get_name()[0]-'0');
        n++;
    }
    symbol /= n;
    value  /= n;


    strcpy (elem.name, symbol);
    elem.value = value;
}

*/



/*
void list::_quick_sort (list_node *first, list_node *end, list_node *prefirst, bool (*cmp)(list_node *, list_node *))
{
    list_node *curr, *first_min, *first_max, *min, *max, *prev2, *prefirst1, *prev1, *tmp, *prev_tmp;
    int l_min = 0, l_max = 0;
    tmp = select_elem(first, end);

    if(tmp) 
    {   
        prev_tmp = tmp;
        tmp = tmp -> next;
        prev_tmp -> next = tmp -> next;
        tmp -> next = first;
        first = tmp;
        if(prefirst) prefirst -> next = tmp;
        else head = tmp;
    }

    if(first || (first -> next == end))
    {
        while (first->next != end)
        {

            min = first_min = nullptr;
            max = first_max = first;
            prev2 = prefirst;
            l_min = 0; l_max = 1;

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

*/



/*
void list::_quick_sort (list_node *first, list_node *end, list_node *prefirst, student& elem)
{
    list_node *curr, *first_min, *first_max, *min, *max, *prev2, *prefirst1, *prev1, *tmp, *prev_tmp;
    int l_min = 0, l_max = 0;
    //bool (*cmp)(double, double);
    get_average(first, end, elem);
    //printf("\n\n\n\n%lf\n", m);
    //first -> print();
    //if( end) end -> print();
    //printf("\nLISTTTTT\n");
    //for (curr = first; curr != end; curr = curr -> next) curr -> print();



    if(first || (first -> next == end))
    {
        while (first->next != end)
        {   

            get_average(first, end, elem);
            if (!(*first > elem))
            {
                for (tmp = first; tmp -> next != end; tmp = tmp -> next)
                    if (*(tmp -> next) > elem) break;

                if (tmp -> next == end) 
                    {
                        elem = *first;
                        strcpy (elem.name, (*first).name[0]);
                        elem.value = (*first).value;
                    }

                else 
                {   
                    prev_tmp = tmp;
                    tmp = tmp -> next;
                    prev_tmp -> next = tmp -> next;
                    tmp -> next = first;
                    first = tmp;
                    if(prefirst) prefirst -> next = tmp;
                    else head = tmp;
                }
            }


            min = first_min = nullptr;
            max = first_max = first;
            prev2 = prefirst;
            l_min = 0; l_max = 1;


            for (prev1 = first, curr = first -> next; curr != end; prev1 = curr, curr = curr -> next)
            {
                if (*curr < elem)
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


            //printf("\n\nLISTTTTT2222222\n");
            //for (curr = first; curr != end; curr = curr -> next) curr -> print();

            printf("\n dlina %d %d\n", l_min , l_max);
            if (l_min < l_max)
            {
                _quick_sort (first_min, first_max, prefirst1);
                first = first_max; prefirst = prev2;
            }
            else
            {
                if (first_max != end && first_max -> next != end)
                    _quick_sort (first_max, end, prev2);

                end = first_max; first = first_min; prefirst = prefirst1;
            }
        }
    }
}



*/


bool list::sort_control ()
{
    if (is_empty()) return true;
    current = head;
    while(current -> next)
    {
        if(!(*current < *(current -> next)) && (  (*current > *(current -> next)) || (*current < *(current -> next)) ) ) return false;
        current = current -> next;
    }
    return true;
}




