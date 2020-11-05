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
    int count=1, ans=0;
    list_node *x0 = head;
    if (head) head = head->get_next ();
    if (!head) return 0;
    
    while( head && ( (*head > *x0) || (*head < *x0) ) )
    {
        x0=head;
        head = head->get_next ();
    }
    
    
    while(head)
    {
        if ( (*head > *x0) || (*head < *x0) ) count++;
        else 
        {    
            count--;
            if (ans < count) ans=count;
            count=0;
        }
        x0=head;
        head = head->get_next ();
    }
    
    return ans;
}
