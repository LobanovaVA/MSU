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
    int count=1, ans=1;
    list_node *x0 = head;
    if (head) head = head->get_next ();
    if (!head) return 1;
    if (*head > *x0) count++;
    x0 = head;
    if (head) head = head -> get_next ();
    
    while(head)
    {
        if (*head > *x0) count++;
        else 
        {            
            if (ans < count) ans=count;
            count=1;
        }
        x0=head;
        head = head->get_next ();
    }
    if (ans < count) ans=count;
    return ans;
}
