#include "student.h"
#include "sort.h"


void bin_insertion_sort(student *a, int n)
{
    student f;
    int i, j, z;
    for(i=1; i<n; i++)
    {
        z=location_of_insertion(a, i, a[i]);
        f.copy(a[i]);
        for(j=i; j>z; j--) a[j].copy(a[j-1]);
        a[z].copy(f);
    }
    f.init(nullptr, 0);
}
int location_of_insertion(student *a, int n, student x){
    int l=0, r=n-1;
    if(a[r]<x) return n;
    while(r-l){
        if(x>a[(l+r)/2]) l=1+(l+r)/2;
        else r=(l+r)/2;
    }
    return l;
}
