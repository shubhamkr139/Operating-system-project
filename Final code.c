#include<stdio.h>
#include<unistd.h>
#include<stdlib.h> 
 
void print(int x[][10],int n,int m)
{
int i,j;
for(i=0;i<n;i++)
 {   
	printf("\n");
	for(j=0;j<m;j++)
	 {
	  printf("%d\t",x[i][j]);
	 }     
 }
} 
 
//Resource Request 
void res_request(int A[10][10],int Y[10][10],int AV[10][10],int pid,int m)
 {
 int reqmat[1][10];
 int i;
 printf("\n Enter additional request : \n");
 for(i=0;i<m;i++)
  {         
     printf(" Request for resource %d : ",i+1); 
     scanf("%d",&reqmat[0][i]); 
  } 
 
  for(i=0;i<m;i++) 
  if(reqmat[0][i] > Y[pid][i])
   {
     printf("\n Error encountered.\n");
     exit(0); 
   } 
  for(i=0;i<m;i++)
  if(reqmat[0][i] > AV[0][i])
   { 
    printf("\n Resources unavailable.\n");
    exit(0);
   } 
  for(i=0;i<m;i++)
    { 
      AV[0][i]-=reqmat[0][i];
      A[pid][i]+=reqmat[0][i];
      Y[pid][i]-=reqmat[0][i];
    } 
 } 
//Algorithm for sefety
int safety(int A[][10],int Y[][10],int AV[1][10],int n,int m,int a[])
{ 
 int i,j,k,x=0;
 int S[10],R[1][10];
 int pflag=0,flag=0;
 for(i=0;i<n;i++)
 S[i]=0;     
 for(i=0;i<m;i++)
 R[0][i]=AV[0][i]; 
 for(k=0;k<n;k++)
 {         
   for(i=0;i<n;i++)
    {             
      if(S[i] == 0)
       {                 
        flag=0;                 
        for(j=0;j<m;j++)
         {                     
          if(Y[i][j] > R[0][j])                         
          flag=1;                 
         }                 
 if(flag == 0 && S[i] == 0)
  {                     
        for(j=0;j<m;j++)                         
        R[0][j]+=A[i][j];                     
        S[i]=1;                     
        pflag++; 
        a[x++]=i;                 
  }             
        }         
    }         
 if(pflag == n)             
 return 1;     
 }     
 return 0; 
}
  
void accept(int A[][10],int Y[][10],int M[10][10],int R[1][10],int *n,int *m)
{     
 int i,j;     
 printf("\n Enter total number of processes : ");     
 scanf("%d",n);     
 printf("\n Enter total number of resources : ");     
 scanf("%d",m);     for(i=0;i<*n;i++)
  {         
   printf("\n Process %d\n",i+1);         
   for(j=0;j<*m;j++)
   {             
   printf(" Allocation for resource %d : ",j+1);             
   scanf("%d",&A[i][j]);             
   printf(" Maximum for resource %d : ",j+1);             
   scanf("%d",&M[i][j]);         
   }     
  }     
printf("\n Available resources : \n");     
for(i=0;i<*m;i++)
{         
  printf(" Resource %d : ",i+1);         
  scanf("%d",&R[0][i]);     
} 
 
for(i=0;i<*n;i++)         
for(j=0;j<*m;j++)             
Y[i][j]=M[i][j]-A[i][j]; 
 
printf("\n Allocation Matrix");     
print(A,*n,*m);     
printf("\n Maximum Requirement Matrix");     
print(M,*n,*m);     
printf("\n Need Matrix");     
print(Y,*n,*m); 
 
} 
 
int banker(int A[][10],int Y[][10],int R[1][10],int n,int m)
{     
  int j,i,a[10];     
  j=safety(A,Y,R,n,m,a);     
  if(j != 0 )
   {         
    printf("\n\n");         
    for(i=0;i<n;i++)              
    printf(" P%d  ",a[i]);         
    printf("\n A safety sequence has been detected.\n");         
    return 1;     
   }
  else
    {         
     printf("\n Deadlock occured.\n");         
     return 0;     
    } 
} 
 
 
int main()
{     
 int ret;     
 int A[10][10];     
 int M[10][10];     
 int Y[10][10];     
 int R[1][10];     
 int n,m,pid,ch;     
 printf("\nAVOIDANCE DEADLOCK BY USING BANKER'S ALGORITHM\n");     
 accept(A,Y,M,R,&n,&m);     
 ret=banker(A,Y,R,n,m);     
 if(ret !=0 )
  {         
   printf("\n Do you want make additional request ? (1=Yes|0=No)");         
   scanf("%d",&ch);         
   if(ch == 1)
    {             
     printf("\n Enter the process number : ");             
     scanf("%d",&pid);             
     res_request(A,Y,R,pid-1,m);             
     ret=banker(A,Y,R,n,m);             
     if(ret == 0 )                 
     exit(0);         
	 }      
  } 
else         
exit(0);     
return 0; 
} 
