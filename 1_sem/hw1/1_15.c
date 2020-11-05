
int printf(const char*, ...);
int scanf(const char*, ...);
unsigned int part_of_n(unsigned int n, int m, int k);
int get_max_bits(unsigned int n);
void print_bits(unsigned int n, int len);

int main(void) {
    unsigned char end;
    unsigned int n, k, m, ans;
    int len;
    
    printf("Input numbers: ");
    if(scanf("%u %u %u%c", &n, &k, &m, &end) != 4 || end!=10 || m>31 || k>31){
        printf("ERROR invalid number format or value\n");
        return 1;
    }
    
    len=get_max_bits(n); print_bits(n, len);
    ans=part_of_n(n, k, m);
    len=get_max_bits(ans); print_bits(ans, len);
    printf("Answer: %d\n", ans);
}

unsigned int part_of_n(unsigned int n, int k, int m){
    int len=8*sizeof(unsigned int);
    if(m>k+1) m=k+1;
    return (n<<(len-k-1))>>(len-m);
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
