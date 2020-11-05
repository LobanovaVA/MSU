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
    list_node *max = head;;
    while(head)
    {
        if (*head > *max)
        {
            count = 0;
            max=head;
        }
        if (!(*head < *max) && !(*head < *max) ) count++;
        head = head->get_next();
    }
    return count;
}
