int printf(const char*, ...);
int scanf(const char*, ...);
unsigned int replace_bits1(unsigned int n);
int get_max_bits(unsigned int n);
void print_bits(unsigned int n, int len);

int main(void) {
    unsigned char end;
    unsigned int n, ans;
    int len;
    
    printf("Input number: ");
    if(scanf("%u%c", &n, &end) != 2 || end!=10){
        printf("ERROR invalid number format or value\n");
        return 1;
    }
    
    len=get_max_bits(n);
    print_bits(n, len);
    ans=replace_bits1(n);
    print_bits(ans, len);
    printf("Answer: %d\n", ans);
    return 0;
}

unsigned int replace_bits1(unsigned int n){
    return n-(n&(n<<1)&(n>>1));
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


