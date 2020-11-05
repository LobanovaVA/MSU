#include "student.h"
#include "sort.h"

void linear_insertion_sort(student *a, int n){
    int z, i, j;
    student f;
    for (i=1; i<n; i++)
    {
        for (j=0; j<=i; j++)
            if (!(a[i]>a[j])) { z=j; break; }
        f.copy(a[i]);
        for(j=i; j>z; j--) a[j].copy(a[j-1]);
        a[z].copy(f);
    }
    f.init(nullptr, 0);
}
