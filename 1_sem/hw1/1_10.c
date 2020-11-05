int printf(const char*, ...);
int scanf(const char*, ...);
double sequence(unsigned int n);

int main(void) {
    unsigned char end;
    unsigned int n;
    printf("Input number: ");
    if(scanf("%u%c", &n, &end) != 2 || end!=10){
        printf("ERROR invalid number format or value\n");
        return 1;
    }
    
    if(n>512) return printf("Answer: inf\n"), 0;
    printf("Answer: %.0lf\n", sequence(n));
}

double sequence(unsigned int n){
    int a0=2, a1=9;
    double  ans, p=4;
    if(n==0) return a0;
    if(n==1) return a1;
    for(;n>1; n--, p*=4) {
        ans=5*a1-6*a0+p;
        a0=a1;
        a1=ans;
    }
    return ans;
}
