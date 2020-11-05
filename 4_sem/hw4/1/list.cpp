#include "addition.h"
#include "list.h"
#include "record.h"
#include "command.h"


int list::read (FILE *fp)
{
    char buf[LEN]; int ph, gr;
    delete_list ();
    while(fscanf (fp, "%s %d %d", buf, &ph, &gr) == 3)
        insert (buf, ph, gr);

    if (feof(fp)) return ERROR_END_OF_INPUT_FILE;
    return ERROR_READ_A;
}


int list::insert (char *buf, int ph, int gr)
{
    list_node *elem;

    elem = new list_node;
    if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
    int ret = elem -> init(buf, ph, gr);
    if (ret != 0) return delete elem, ret;

    if (!head) head = elem;
    else
    {

        ///*
        elem -> next = head;
        head -> prev = elem;
        head = elem;
        //*/

        /*

        list_node *curr = head;
        while (curr -> next && curr -> get_phone () <  elem -> get_phone ())  curr = curr -> next;
        while (curr -> next && curr -> get_phone () == elem -> get_phone ())
           if (*curr == *elem) return delete elem, ERROR_SAME_DATA;

        if (curr -> get_phone () > elem -> get_phone ()) 
        {
            if (curr == head)
            {
                elem -> next = curr;
                curr -> prev = elem;
                head = elem;
            }
            else 
            {
                curr -> prev -> next = elem;
                elem -> prev = curr -> prev;
                curr -> prev = elem;
                elem -> next = curr;
            }
        }
        else
        {
            if (*curr == *elem) return delete elem, ERROR_SAME_DATA;
            if (curr == head)
            {
                elem -> next = curr;
                curr -> prev = elem;
                head = elem;
            }
            else
            {
                curr -> next = elem;
                elem -> prev = curr;  
            }
        }
           
        */


        /*
        list_node *curr = head;
        while (curr -> next)
        {
            if (*curr == *elem) return delete elem, ERROR_SAME_DATA;
            curr = curr -> next;
        }
        if (*curr == *elem) return delete elem, ERROR_SAME_DATA;
        curr -> next = elem;
        elem -> prev = curr;
        */

    }
    return 0;
}

void list::print (FILE* out)
{
    int i=0;
    list_node *curr = head;
    while(curr && i<MAX_PRINT)
    {
        curr -> print (out);
        curr = curr -> next;
        i++;
    }
}

void list::delete_head ()
{
    list_node *tmp = head;
    if (head) 
    {
        head = tmp -> next;
        if (tmp -> next) tmp -> next -> prev = nullptr;
        delete tmp;
    }
}

void list::delete_current (list_node *curr)
{
    if (!curr) return;
    if (curr == head) return delete_head();
    if (curr -> next) curr -> next -> prev = curr -> prev;
    curr -> prev -> next = curr -> next;
    delete curr;
}




//navigation:

        //list_node <T> * get_head () const { return head; }
        //list_node <T> * get_next () const { if (current) return current -> next; else return nullptr; }

//adding:
/*
        bool add_head (list_node <T> *elem = nullptr)
        { 
            if (!elem) elem = new list_node <T>;
            if (!head)
            {
                head = elem;
                head -> next = nullptr;
            }
            else
            {
                elem -> next = head;
                head = elem;
            }
            return true; 
        }
*/
/*
        bool add_next (list_node <T> *elem = nullptr)
        { 
            //if (head == nullptr) return add_head(elem);   //если нет головы добавитьв голову 
            if (!curr) return false;
            //if (current -> next) return printf("item already exists\n"), false; //если next уже есть RETURN
            if (!elem) elem = new list_node <T>;
            list_node <T> *ptr = curr -> next;
            curr -> next = elem;
            elem -> next = ptr;
            return true; 
        }
   */
//deleting:

         //удаляет голову и ставит новую голову

    


/*
        void delete_next ( list_node <T> *curr)
        {
            if (!curr) return;
            list_node <T> *tmp = curr -> next;
            if (tmp)
            {
                curr -> next = tmp -> next;
                if (tmp -> next) tmp -> next -> prev = curr;
                delete tmp;
            }
        }





        void delete_prev (list_node <T> *curr)
        {
            if (!curr) return;
            list_node <T> *tmp = curr -> prev;
            if (tmp)
            {
                curr -> prev = tmp -> prev;
                if (tmp -> prev) tmp -> prev -> next = curr;
                delete tmp;
            }

        }

*/



int list::do_command(command &line) 
{ 
    //line.print_cmd();
    
    switch(line.type)
    {
        case CMD_NONE: return 0;
        case QUIT: return 1; 
        case STOP: return 1; 
        case INSERT: insert (line.name.get(), line.phone, line.group); break;
        case SELECT: 
        {
            //line.print();
            list_node *curr;
            for (curr = head; curr; curr = curr -> next)
                if (search (curr, line)) curr -> print();
            break;
        }

        case DELETE:
        {
            list_node *curr, *tmp;
            for (curr = head; curr;)
            {
                if (search (curr, line))
                {
                    tmp = curr -> next;
                    delete_current(curr);
                    curr = tmp;
                }
                else curr = curr -> next;
            }
            break;
        }
    }
    return 0;
}


int list::search(list_node *curr, command &line) 
{
    int fl_n = 0;
    switch (line.c_name)
    {
        case COND_NONE: break;
        case EQ: if (strcmp (curr -> name.get(), line.name.get()) == 0) fl_n = 1; break;
        case LT: if (strcmp (curr -> name.get(), line.name.get()) <  0) fl_n = 1; break;
        case GT: if (strcmp (curr -> name.get(), line.name.get()) >  0) fl_n = 1; break;
        case NE: if (strcmp (curr -> name.get(), line.name.get()) != 0) fl_n = 1; break;
        case LE: if (strcmp (curr -> name.get(), line.name.get()) <= 0) fl_n = 1; break;
        case GE: if (strcmp (curr -> name.get(), line.name.get()) >= 0) fl_n = 1; break;
        case LIKE: break;
    }

    int fl_p = 0;
    switch (line.c_phone)
    {
        case COND_NONE: break;
        case EQ: if (curr -> phone == line.phone) fl_p = 1; break;
        case LT: if (curr -> phone <  line.phone) fl_p = 1; break;
        case GT: if (curr -> phone >  line.phone) fl_p = 1; break;
        case NE: if (curr -> phone != line.phone) fl_p = 1; break;
        case LE: if (curr -> phone <= line.phone) fl_p = 1; break;
        case GE: if (curr -> phone >= line.phone) fl_p = 1; break;
        case LIKE: break;
    }

    int fl_g = 0;
    switch (line.c_group)
    {
        case COND_NONE: break;
        case EQ: if (curr -> group == line.group) fl_g = 1; break;
        case LT: if (curr -> group <  line.group) fl_g = 1; break;
        case GT: if (curr -> group >  line.group) fl_g = 1; break;
        case NE: if (curr -> group != line.group) fl_g = 1; break;
        case LE: if (curr -> group <= line.group) fl_g = 1; break;
        case GE: if (curr -> group >= line.group) fl_g = 1; break;
        case LIKE: break;
    }

    int ans = 0;
    switch (line.oper)
    {
        case OP_NONE:
        {
            if (line.c_name  != COND_NONE) ans = fl_n;
            if (line.c_phone != COND_NONE) ans = fl_p;
            if (line.c_group != COND_NONE) ans = fl_g;
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
            if (line.c_name  != COND_NONE && line.c_phone != COND_NONE) ans = fl_n + fl_p;
            if (line.c_name  != COND_NONE && line.c_group != COND_NONE) ans = fl_n + fl_g;
            if (line.c_phone != COND_NONE && line.c_group != COND_NONE) ans = fl_p + fl_g;
            break;
        }
    }

    if (ans != 0) return 1;
    return 0;
    //printf("%d %d %d %d\n", fl_n, fl_p, fl_p, ans);
}

    











