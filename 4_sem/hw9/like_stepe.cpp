
int like_default (char *str_name, char *str_like) 
{
    int h, g = 0, ret = 1;
    for (h = 0; str_name[h] && str_like[h+g]; h++)
    {
        if (str_like [h+g] == '%') return 1;
        if (str_like [h+g] != '_')
        {
            if (str_like [h+g] == '\\') g++;
            if (str_like [h+g] != str_name [h]) { ret = 0; break;}
        }
        
    }
    if (ret && (str_name[h+g] || str_like[h])) ret = 0;
    if (ret) return 1;
    return 0;
}


int like (char *str_name, char *str_like) 
{
    char *p = strchr (str_like, '%');
    if (!p || !*(p+1)) return like_default(str_name, str_like);

    
    int len_name = strlen(str_name);
    int a[LEN] = {0}, b[LEN] = {0}, i; 
    int *c, *A, *B;
    a[0] = 1; 
    if (str_like[0] == '%') b[0] = 1;

    printf("%d\n", len_name);

    for (i = 0; str_name[i] && str_like[i]; i++)
    {
        printf("\narray1\n");
        for (int j=len_name; j>=0; j--) printf("%d %d\n", a[j], b[j] );
        
        if (str_like[i] == '%')
        {
            for (int h = 1; h < len_name + 1; h++)
            {
                if (a[h] == 1 || b[h-1] == 1) b[h] = 1;
                a[h] = 0;
            }
        }
        else
        {
            for (int h = 1; h < len_name + 1; h++)
            {
                printf("a[h-1] = %d  like =%c| name=%c|\n", a[h-1], str_like[i],  str_name[h-1] );
                if (a[h-1] == 1 && ( str_like[i] == str_name[h-1] || str_like[i] == '_' ))  b[h] = 1;
                a[h-1] = 0;  
            }
        }
        printf("\narray2\n");
        for (int j=len_name; j>=0; j--) printf("%d %d\n", a[j], b[j] );
        A = a; B = b;
        c = A; A = B; B = c;

        printf("\narray3\n");
        for (int j=len_name; j>=0; j--) printf("%d %d\n", a[j], b[j] );
    }

    printf("%d\n",b[len_name]);
    if (str_like[i]) return 0;
    return b[len_name];
}
