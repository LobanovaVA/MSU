#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
 
#include "student.h"
#include "addition.h"
#include "list.h"
#include "list_node.h"

int solve(list_node *);

int solve(list_node *head)
{
    int ans;
    list_node *x0 = head;
    if (head) head = head -> get_next ();
    if (!head) return 4;
    
    if (*x0 < *head) ans = 1;
    else 
    {
        if (*x0 > *head) ans = 2;
        else ans =  3;
    }
    x0 = head;
    
    if (head) head = head->get_next ();
    else return ans;
    
    while(head)
    {
        if ( (ans == 1 && *x0 > *head) || (ans == 2 && *x0 > *head) ) return 0;
        if (ans == 3)
        {
            if (*x0<*head) ans = 1;
            if (*x0>*head) ans = 2;
        }
        x0=head;
        head = head->get_next ();
    }
    return ans;
}
