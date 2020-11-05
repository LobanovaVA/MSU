#include "student.h"
#include "sort.h"


void heap_sort(student *a, int n){
    int i, z, h, t;
    student f;

    for(i=1; i<n; i++) {
        z=i;
        while(z>=0 && !(a[i]<a[z])) {
            t=z;
            if(z==0) break;
            z=(z-1)/2;
        }
        f.copy(a[i]);
        for(h=i; h>t; h=(h-1)/2) a[h].copy(a[(h-1)/2]);
        a[t].copy(f);
        f.init(nullptr, 0);
    }
    for(i=n-1; i>0; i--)
    {
        a[i].swap(a[0]);
        max_tree(a,i);
    }
}

void max_tree(student *a, int n)
{
    int  z=0, mc;
    student f;
    f.copy(a[0]);
    
    while(2*z+1<n){
        if(2*z+2<n && a[2*z+2]>a[2*z+1] ) mc=2*z+2;
        else mc=2*z+1;

        if(a[mc]>f){
            a[z].copy(a[mc]); z=mc;   }
        else break;
    }
    a[z].copy(f);
    f.init(nullptr, 0);
}




/*
void heap_sort(student *a, int n)
{
    int i=0;  
    max_tree(a, n, i);
    for(i=n/2-1; i>=0; i--) max_tree(a, n, i);

    for(i=n-1; i>=0; i--)
    {
        a[i].swap(a[0]);
        max_tree(a, i, 0);
    }
}


void max_tree(student *a, int n, int j)
{
    int  mc;
    for(;;)
    {
        mc=j;
        if(2*j+1<n) mc=2*j+1;
        if(2*j+2<n && a[2*j+2]>a[mc]) mc=2*j+2;

        if(a[mc]>a[j]) a[j].swap(a[mc]); 
        else break;
        j=mc;
    }
}

*/