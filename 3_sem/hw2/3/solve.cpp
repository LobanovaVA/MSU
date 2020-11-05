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
    list_node *tmp = head;
    if (head) head = head->get_next();
    while(head)
    {
        if (*head > *tmp) count++;
        tmp = head;
        head = head->get_next();
    }
    return count;
}
