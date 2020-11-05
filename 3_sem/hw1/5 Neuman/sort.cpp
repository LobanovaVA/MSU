#include "student.h"
#include "sort.h"

void merge_arrays(student *a, int n, student *b, int m, student *c)
{
    int i=0, j=0, s=0;
    while(i<n && j<m){
        if(a[i]<b[j]) {c[s].copy(a[i]); i++; s++;}
        else {c[s].copy(b[j]); j++; s++;}
    }
    while (i<n) {c[s].copy(a[i]); i++; s++;}
    while (j<m) {c[s].copy(b[j]); j++; s++;}
}

void Neuman_sort(student *a, int n, student *b)
{
    int d, i, r=0;
    student *c, *a0=a;

    for(d=1; d<n; d<<=1)
    {
        for(i=0; (i+2*d)<=n; i+=2*d)
            merge_arrays(a+i, d, a+i+d, d, b+i);
        merge_arrays(a+i, n-i-r, a+n-r, r, b+i);
        r=n-i;
        c=a; a=b; b=c;
    }
    if(a!=a0) 
        for(i=0; i<n; i++) 
        {
        b[i].copy(a[i]);
        a[i].init(nullptr, 0);
        }
    else 
    {
        for(i=0; i<n; i++) 
        b[i].init(nullptr, 0);
    }
        
}
