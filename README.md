# cs101

int main()
{
    int rows;
 
    printf("Enter Inverted Triangle of Alphabets Rows = ");
    scanf("%d", &rows);
 
    printf("Printing Inverted Triangle Alphabets Pattern\n");
    int alphabet = 65;
 
    for (int i = 0; i <= rows - 1; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k <= rows - i - 1; k++)
        {
            printf("%c ", alphabet + k);
        }
        printf("\n");
    }
}










