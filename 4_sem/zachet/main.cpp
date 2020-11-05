#include <stdio.h>
#include <ctime>
#include "data_base.h"

#ifdef ZACHET
//53
int name_hash (char *str, int n)
{
    unsigned int sum = 0, j = 1;
    for (int i = 0; str[i]; i++, j*=53) sum += (unsigned int)(str[i]-'a')*j;
    return sum%n;
}


int phone_hash (int ph, int n) { return ph%n; }
#else
int name_hash (char *str, int n)
{
    int sum = 0;
    for (int i = 0; str[i]; i++) sum += (int)str[i];
    return sum%n;
}

int phone_hash (int ph, int n)
{
    int sum = 0;
    for (; ph > 0; ph = ph/10) sum += ph % 10;
    return sum%n;
}
#endif

int main(int argc, char **argv)
{

    const char *file; int n1, n2;
    if (argc !=4 || !(n1 = atoi(argv[2])) || !(n2 = atoi(argv[3])) || n1 <= 0 || n2 <=0) return printf ("Usage: %s FILE.txt hash_NAME_size hash_PHONE_size \n", argv[0]), 1;
    file = argv[1];

    FILE *in;
    if (!( in=fopen(file, "r"))) return  printf("Cannot open %s\n", file), ERROR_OPEN_A;

    n1 = 500000; n2 = 100000; 
 
    data_base A(n1,n2);
    double time = clock ();

    int ret = A.read(in);
    fclose (in);
    if (ret<0)
    {
        switch (ret)
        {
            case ERROR_OPEN_A:  printf ("Cannot open input file\n"); break;
            case ERROR_READ_A:  printf ("Cannot read input file\n"); break;
            case ERROR_READ_CLASS: printf ("Cannot read record\n"); break;
            case ERROR_NOT_ENOUGH_MEMORY: printf ("Not enough memory to read \n"); break;
            default: printf ("Unknown error %d\n", ret);
        }
        return 3;
    }

    //A.print();
    
    int alf [256] = {0}; char buf[LEN];
    char spaces_str [7] = {' ', ',', ';', '(', ')', '\t', '\n'};
    for (int i = 0; i < 7; i++) alf[(int)spaces_str[i]] = 1;

    time = clock () - time;
    printf("TIME_READ: %lf\n\n", time/CLOCKS_PER_SEC);

    command line;
    while (fgets (buf, LEN, stdin))
    {
        ret = line.parse (alf, buf);
        if (ret < 0) continue;
        //line.print();
        ret = A.do_command(line);
        //A.print();
        if (ret == 1) break;
    }

    //A.print();
    time = clock () - time;
    printf("\nTIME_DO_COMMAND: %lf\n",time/CLOCKS_PER_SEC);
    
    return 0;
}














