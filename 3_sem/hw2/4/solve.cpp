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
    int count=0;
    list_node *x0 = head;
    if (head) head = head->get_next ();
    list_node *x1 = head;
    if (head) head = head->get_next ();
    
    while(head)
    {
        if (*x1 > *x0 && *x1 > *head) count++;
        x0=x1;
        x1=head;
        head = head->get_next ();
    }
    return count;
}
