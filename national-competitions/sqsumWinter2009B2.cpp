extern "C"
{
    int scanf(const char*, ...);
    int printf(const char*, ...);
}

int digitSums[12];

void init()
{
    digitSums[0]=0;
    for(int i=1;i<12;i++)digitSums[i]=i+digitSums[i-1];
}

int s;
int main()
{
    init();

    scanf("%d", &s);
    for(int i=1;i<=s;i++)
    {
        int lineEnd=i%10?(i/10+1)*10:i;
        for(int width=1;width<=lineEnd-i+1;width++)
        {
            int sum=i*width*width;
            sum+=width*digitSums[width-1];

            sum+=digitSums[width-1]*width*10;
            if(sum==s)
            {
                printf("%d\n", i);
                return 0;
            }
        }
    }
}
