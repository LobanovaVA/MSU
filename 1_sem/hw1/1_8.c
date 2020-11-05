int printf(const char*, ...);
int scanf(const char*, ...);
int pow2(double n);

int main(void) {
    unsigned char end;
    double n;
    printf("Input number: ");
    if(scanf("%lf%c", &n, &end) != 2 || end!=10 || n<=0 ){
        printf("ERROR invalid number format or value\n");
        return 1;
    }

    printf("Answer: %d\n", pow2(n));
}

int pow2(double n){
    int ans=0;
    double p=1.0;
    if(n>=1.0)
      for(; n-2*p>=0.0; p*=2.0, ans++);
    else for(; n-p<0.0; p/=2.0, ans--);
    return ans;
}
