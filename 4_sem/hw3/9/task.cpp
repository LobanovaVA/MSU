list_node*  list::task9(list_node *b)
{
    int check;
    list_node *start, *ita, *itasaver, *itb;
    current = head;
    while((start = current))
    {
        for(ita = start, itb = b, check = 1; (ita)&&(itb); ita = ita->next, itb = itb->get_next())
        {
            itasaver = ita;
            if(!(*ita == *itb)){check = 0; break;}
        }
        if(check)
        {
            if(ita) {current = ita->next; remove_ab(start, itasaver);}
            else
            {
                if(!itb) remove_ab(start, itasaver);
                current = nullptr;
            }
        }
        else current = current->next;
    }
    return head;
}

void list::remove_ab(list_node *a, list_node *b)
{
    list_node *element, *ptr;
    if(a->prev)
    {
        if(b->next){a->prev->next = b->next;}
        else{tail = a->prev; tail->next = nullptr;}
    }
    else
    {
        if(b->next){head = b->next; head->prev = nullptr;}
        else head = nullptr;
    }
    b->next = nullptr;
    element = a;
    while(element){ptr = element; element = element->next; delete ptr;}
}




list_node* solve_9 (list_node *head_b)
{
    int fl;
    list_node *tmp;
    current = head;
    while(current){

        current_a = current;
        current_b = head_b;
        fl =1;

        while ( (current_a) && (current_b) && fl)
        {
            tmp = current_a;
            if(!(*current_a == *current_b)) fl = 0;

            current_b = current_b -> next;
            current_a = current_a -> next;
        }

        if(fl)
        {
            if (current_a) current = current_a -> next; 
            else current = nullptr;
            if (!current_b) 
                {


                    if (tmp == head)
                    {      
                        current_a = current_a -> next;             
                        if (current_a) 
                        {
                            current_a -> prev -> next = nullptr;
                            current_a -> prev = nullptr;
                        }

                        while(tmp) 
                        {
                            trash = tmp -> next;
                            delete tmp;
                            tmp = trash;
                        }
                
                        head = current_a;
                    }
                    else
                    {
                        current_a = current_a -> next;       
                        if (current_a) 
                        {
                            tmp -> prev -> next = current_a;
                            current_a -> prev -> next = nullptr;
                            current_a -> prev = tmp -> prev;

                        }
                        else tmp -> prev -> next = nullptr;
                
                        while(tmp) 
                        {
                            trash = tmp -> next;
                            delete tmp;
                            tmp = trash;
                        }
                        
                    }
                }


        }

        else current = current -> next;
    }
    return head;
}        

