int printf(const char*, ...);
int scanf(const char*, ...);
int prime(unsigned int n);

int main(void) {
    unsigned char end;
    unsigned int  n, i;
    int ans=0;
    printf("Input number: ");
    if(scanf("%u%c", &n, &end) != 2 || end!=10)
        return printf("ERROR invalid number format or value\n"), 1;

    if(n<=2) return printf("Answer: 0\n"), 0;
    for(i=2; i<n-1; i+=2, ans+=prime(i));
    printf("Answer: %d\n", ans+1);
    return 0;
}

int prime(unsigned int n){
    long int i;
    int k=1;
    //for(i=(unsigned long int)sqrt(n)+1; i>2; i--)
    for(i=2; i*i<=n; i+=2)
        if(n!=i && n%i==0) {
            k=0;
            break;
        }
    return k;
}
