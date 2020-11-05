#include "student.h"
#include "sort.h"

void bubble_sort(student *a, int n)
{
    for(int i=0;i<n; i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j]>a[j+1]) a[j].swap(a[j+1]);

}