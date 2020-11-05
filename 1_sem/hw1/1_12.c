int printf(const char*, ...);
int scanf(const char*, ...);
const long int limn=100000000;
double sum(unsigned int n);

int main(void) {
    unsigned char end;
    unsigned int  n;
    printf("Input number: ");
    if(scanf("%u%c", &n, &end) != 2 || end!=10 || n==0){
        printf("ERROR invalid number format or value\n");
        return 1;
    }
    printf("Answer: %.16lf\n", sum(n));
}

double sum(unsigned int n){
    unsigned int k=1;
    double  ans=0;
    if(limn<n) n=limn;
    for(;k<=n; k++) {
        if(k%2==0) ans+=1.0/(double)k;
        else ans-=1.0/(double)k;
    }
    return ans;
}
