#include <stdio.h>
#include <string.h>
#include <iostream>

#include "student.h"
#include "list_node.h"
#include "list.h"
#include "addition.h"

int list::read (FILE *fp, int n2, int n3)
{
	int ret;
	delete_list ();
	list_node *elem, *curr;

	elem = new list_node;
	if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
	ret = elem -> read (fp, n3);
	if (ret != 0) return delete elem, ret;
        head = curr = elem;

	for (int i = 1; i < n2; i++)
	{
            elem = new list_node;
            if (!elem) return ERROR_NOT_ENOUGH_MEMORY;
            ret = elem -> read (fp, n3);
            if (ret != 0) return delete elem, ret;
            curr -> next = elem;
            curr = elem;
            //elem = nullptr;
	}
	return 0;
}

void list::print (FILE *out)
{
    printf("\n╔=============================================================╗");
    printf("\n║                          👀 LIST                            ║\n");
    int i = 0;
    list_node *curr = head;
    while (curr && i<MAX_PRINT)
    {
        if(curr==current) printf("  👉");
        else printf("    ");
        curr -> print ( curr -> get_root(), out);
        curr = curr -> next;
        i++;
    }
    printf("\n╚=============================================================╝");
}


//adding:__________________________________________________________________________________________________________

bool list::add_head (list_node *elem) 
{ 
    if (!elem) elem = new list_node;
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
bool list::add_next (list_node *elem)
{ 
    //if (head == nullptr) return add_head(elem);   //если нет головы добавитьв голову 
    if (current_check ()) return false;             
    //if (current -> next) return printf("item already exists\n"), false; //если next уже есть RETURN
    if (!elem) elem = new list_node;
    list_node *ptr = current -> next;
    current -> next = elem;
    elem -> next = ptr;
    return true; 
}
    
//deleting:__________________________________________________________________________________________________________

 //удаляет голову и ставит новую голову
void list::delete_head ()
{
    list_node *tmp = head;
    if (head) 
    {
        head = tmp -> next;
        if (current == tmp) current = nullptr;
        delete tmp;
    }
}


void list::delete_next ()
{
    if(current_check ()) return;
    list_node *tmp = current -> next;
    if (tmp)
    {
        current -> next = tmp -> next;
        delete tmp;
    }
}

//other:__________________________________________________________________________________________________________



 // 🐙 🐢 🐣 🐤 🐥 🐦🐧 🐨 🐩 🐫 🐬 🐭 🐮 🐯 🐰 🐱 🐲 🐳 🐴 🐵 🐶 🐷 🐸 🐹 🐺 🐻 🐼 🌛
void list::menu ()
{
    char buf[LEN]; 
    print_menu ();
    for(;;)
    {
        printf("\nEnter command: ");
        if (!(fgets (buf, LEN, stdin))) return;
        enum MENU_ITEMS key = (MENU_ITEMS) buf [0];
        switch (key)
        {
            case MENU_MENU       : {printf("PRINT LIST MENU:");          print_menu (); break;}
            case MENU_PRINT      : {printf("PRINT LIST:\n");             print (); break;}
            case MENU_CURRENT    : {printf("PRINT LIST CURRENT:\n");     if(!current_check ()) current -> print (current -> get_root()); break;}
            case MENU_GO_HEAD    : {printf("GO LIST HEAD\n");            go_head (); break;}
            case MENU_GO_NEXT    : {printf("GO LIST NEXT\n");            go_next (); break;}
            case MENU_ADD_HEAD   : {printf("ADD HEAD\n");                add_head(); break;}
            case MENU_ADD_NEXT   : {printf("ADD NEXT\n");                add_next(); break;}
            case MENU_DEL_HEAD   : {printf("DELETE HEAD\n");             delete_head(); break;}
            case MENU_DEL_NEXT   : {printf("DELETE NEXT\n");             delete_next(); break;}
            case MENU_KILL       : {printf("KILL ALL LIST\n");           delete_list(); break;}
            case MENU_WORK       : {printf("GO INTO NEXT STRUCTURE (LIST)\n");    if(!current_check ()) current -> menu (); break;}
            case MENU_EXIT       : {printf("EXIT INTO PREV STRUCTURE (QUEUE)\n");  return;}
        }
    }
}


void list::print_menu()
{
    printf("\n\n");
    printf("\n               ╔=====🐙 🐯 🐰 🐲 🐢 🐺 🐶 🐷=====╗");
    printf("\n               ║                                 ║");
    printf("\n               ║      LIST MENU:                 ║");
    printf("\n               ║                                 ║");
    printf("\n               ║  m - print menu                 ║");
    printf("\n               ║  p - print list                 ║");
    printf("\n               ║  c - print list current         ║");
    printf("\n               ║                                 ║");
    printf("\n               ║  h - go to head                 ║");
    printf("\n               ║  n - go to next                 ║");
    printf("\n               ║                                 ║");
    printf("\n               ║  a - add head                   ║");
    printf("\n               ║  s - add next                   ║");
    printf("\n               ║                                 ║");
    printf("\n               ║  x - delete head                ║");
    printf("\n               ║  y - delete next                ║");
    printf("\n               ║  k - kill all list              ║");
    printf("\n               ║                                 ║");
    printf("\n               ║  w - go into next structure 🐾  ║");
    printf("\n               ║  e - exit                       ║");
    printf("\n               ║                                 ║");
    printf("\n               ╚=================================╝");
    printf("\n\n");         
}










