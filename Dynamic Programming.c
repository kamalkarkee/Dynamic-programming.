// gcc -o main main.c
// ./main < file.dat
//compilation used in Omega
//the asymptotic worst-case time is Θ(mn)
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;    // input size set
    int m=0;    // Target value
    int *S;   // Input set
    int **C;   // Cost value table 
    // -----------------------------------------------------------
    // Read Input
    // Input n
    scanf("%d",&n);
    // Allocate memory for input sequence
    S=(int*) malloc((n+1)*sizeof(int));
    if(!S)
    {
        printf("malloc failed %d\n",__LINE__);
        exit(0);
    }
    S[0] = 0;
    // Input sequence
    int i,j;
    for (i=1; i<n+1; i++)
    {
        scanf("%d",&S[i]);
        m+=S[i];
    }
    // Display input sequence
    printf("%d/%d = %d\n\n",m,3,m/3);
    printf("  i   S\n");
    printf("-------\n");
    for (i=0; i<n+1; i++)
    {
        printf("%3d %3d\n",i,S[i]);
    }
    printf("\n");
    // Check if divisible by 3
    if (m%3 != 0)
    {
        printf("m is not divisible by 3 %d\n\n",__LINE__);
        exit(0);
    }
    m = m/3;
    // Allocate memory for 2-D cost table
    C = (int**) malloc((m+1)*sizeof(int*));
    for (i=0; i<(m+1); i++)
        C[i] = (int*) malloc((m+1)*sizeof(int));        
    if(!C)
    {
        printf("malloc failed %d\n",__LINE__);
        exit(0);
    }
    // ----------------------------------------------------------
    // Subset Sum
    int potentialSum, leftover;
    C[0][0]=0;
    for (potentialSum=1; potentialSum<=m; potentialSum++)
    {
        for (j=1; j<(n+1); j++)
        {
            leftover=potentialSum-S[j];
            if (leftover>=0 && C[0][leftover]<j)
                break;
        }
        C[0][potentialSum]=j;
    }
    for (i=1; i<(m+1); i++)
    {
        C[i][0] = C[0][i];
        for (potentialSum=1; potentialSum<=m; potentialSum++)
        {
            for (j=1; j<(n+1); j++)
            {
                leftover=potentialSum-S[j];
                if (leftover>=0 && C[i][leftover]<j)
                    break;
            }
            C[i][potentialSum]=j;
        }
    }
    // Print Cost Table
    if (m<=10)
    {
        printf("  i   j   C\n");
        for (i=0; i<(m+1); i++)
        {
            for (j=0; j<(m+1); j++)
            {
                printf("%3d %3d %3d\n",i,j,C[i][j]);
            }
        }
    }
    printf("\n");
    // ------------------------------------------------------
    // Write Output
    int set1[100], set2[100];
    int set1Count=0, set2Count=0;
    if (C[m][m]==n+1)
        printf("No Solution\n");
    else
    {
        for (i=m; i>0; i-=S[C[m][i]])
        {
            //printf("%3d %3d\n", C[m][i], S[C[m][i]]);
            set1[set1Count] = C[m][i];
            set1Count++;
        }
        for (i=m; i>0; i-=S[C[0][i]])
        {
            //printf("%3d %3d\n", C[0][i], S[C[0][i]]);
            set2[set2Count] = C[0][i];
            set2Count++;
        }
        int setFlag=1;

        printf("Solution\n");
        printf("i %3d %3d %3d\n",0,1,2);
        for (i=1; i<n+1; i++)
        {
            printf("%d ",i);
            for (j=0; j<set1Count; j++)
            {
                if (set1[j]==i)
                {
                    printf("%3d\n",S[i]);
                    setFlag=0;
                    break;
                }
            }
            for (j=0; j<set2Count; j++)
            {
                if (set2[j]==i)
                {
                    printf("%7d\n",S[i]);
                    setFlag=0;
                    break;
                }
            }
            if (setFlag==0)
                setFlag=1;
            else
            {
                printf("%11d\n",S[i]);
            }
        }
    }
    // Free allocated dynamic memory
    free(S);
    for (i=0; i<(m+1); i++)
        free(C[i]);
    free(C);
}