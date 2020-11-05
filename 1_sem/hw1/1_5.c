int printf(const char*, ...);
int scanf(const char*, ...);
int get_max_dis_0to0(unsigned int n);
int get_max_bits(unsigned int n);
void print_bits(unsigned int n, int len);

int main(void) {
    unsigned char end;
    unsigned int n;
    int len, ans;
    
    printf("Input number: ");
    if(scanf("%u%c", &n, &end) != 2 || end!=10){
        printf("ERROR invalid number format or value\n");
        return 1;
    }
    
    len=get_max_bits(n);
    print_bits(n, len);
    ans=get_max_dis_0to0(n);
    if(ans==-1 || n==0) return printf("Only one bit 0\n"), 0;
    if(ans==-2) return printf("No bit 0\n"), 0;
    printf("Answer: %d\n", ans);
}

int get_max_dis_0to0(unsigned int n){
    int ans=0, k=-1;
    for(; n&1 && n!=0; n>>=1);
    if(n==0) return -2;
    
    for(;;){
        if(!(n&1)) ans=k;
        k++;
        n>>=1;
        if(n==0) break;
    }
    return ans;
}

int get_max_bits(unsigned int n){
    int i=0;
    do{
        i++;
        n>>=1;
    }
    while(n);
    return i;
}

void print_bits(unsigned int n, int len){
    int i=0;
    for(; i<len; i++){
        if(n&(1<<(len-i-1))) printf("1");
        else printf("0");
    }
    printf("\n");
}
