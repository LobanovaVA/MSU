#include "student.h"
#include "sort.h"

void min_sort(student *a, int n)
{
    for(int i=0; i<n; i++){
        int f=i;
        for(int j=i; j<n; j++) if(a[j]<a[f]) f=j;
        a[f].swap(a[i]);
    }
}
