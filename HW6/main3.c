int main()
{
    int year =2022;
    if(year%400==0)
        printf("yes");
        
    if(year%4==0 & year%100!=0)
        printf("yes");
        
    else
        printf("no");
    
    return 0;
}
