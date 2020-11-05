int printf(const char*, ...);
int scanf(const char*, ...);
const long int limn=170;
double sumfac(unsigned int n);

int main(void) {
    unsigned char end;
    unsigned int n;
    printf("Input number: ");
    if(scanf("%u%c", &n, &end) != 2 || end!=10 || n==0){
        printf("ERROR invalid number format or value\n");
        return 1;
    }
    printf("Answer: %.16lf\n", sumfac(n));
}

double sumfac(unsigned int n){
    unsigned int k=1;
    double  ans=0.0, f=1.0;
    if(limn<n) n=limn;
    for(;k<=n; k++, f/=(double)k) ans+=f;
    return ans;
}

