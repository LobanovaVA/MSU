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
    
    if(n>644) return printf("Answer: inf\n"), 0;
    printf("Answer: %.0lf\n", sequence(n));
}

double sequence(unsigned int n){
    double  ans=1.0, p=2.0;
    for(;n>0; p*=2.0, n--) ans=3*ans+4*p;
    return ans;
}
