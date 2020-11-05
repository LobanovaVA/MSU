#include "student.h"
#include "sort.h"

void quick_sort(student *a, int n)
{
    student x;
    int k;
    if(n<2) return;
    while(n>2){
        k=sort_by_x(a,n,a[n/2]);
        if(k<n-k){
            quick_sort(a, k);
            a+=k;
            n-=k;
        }
        else{   quick_sort(a+k, n-k); n=k;  }
    }
    if(n==2 && a[n-2]>a[n-1]) a[n-2].swap(a[n-1]);
    
    return;
}

int sort_by_x(student *a, int n, student& x)
{
    int l=0, r=n-1;
    while(r>=l)
    {
        for(; l<n && a[l]<x; l++);
        for(; r>0 && a[r]>x; r--);
        if(l<=r)  
        {
        	a[l].swap(a[r]); 
        	l++; 
        	r--;
        }
    }
    return l;
}
