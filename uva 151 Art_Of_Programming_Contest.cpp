#include <stdio.h>  
#define MAX 150  
   
/** Implementatiom of circular queue  **/  
 
 
int queue[MAX];  
int e,f,r;  
 
/** _f is front; _r is rear & _e is element number **/  
   
/* ************************************************** */  
/*   A general push algorithm act over queue    */  
/* ************************************************** */  
  
void push(int i)  
{  
   r++;  
   e++;  
   if(r>=MAX)  
      r=1;  
   queue[r] = i;  
}  
   
 
/* ************************************************** */  
/*   A general pop algorithm act over queue     */  
/* ************************************************** */  
 
int pop(void)  
{  
   e--;  
   int i=queue[f];  
   f++;  
   if(f>=MAX)  
      f = 1;  
   return i;  
}  

/** End of circular queue **/  
/* ***********************************    */  
/* A general joshusf function.           */     
/* This function start removing          */  
/* element from first element            */  
/* and return the sirviver              */  
/* ***********************************   */  
 
int joshups(int n,int v)  
{   
   register int i;  
   e=n;  
   for(i=1;i<=n;i++)  
      queue[i] = i;  
   f = 1; // 0 for serviving first element.  
   r = n; // n+1 for serviving first element.  
   i = 0;  
   if(n > 1)  
      pop();  
   while(e!=1)  
   {  
      if(i!=v)  
      {  
         i++;  
         push(pop());  
      }  
      else  
      {  
     pop();  
     i = 0;  
      }  
   }  
   return queue[f];  
}  

/*sample main function*/  
 
int main(void)  
{  
   int i,m;  
   scanf("%d",&i);  
   while(i)  
   {   m=1;  
      while((joshups(i,m++)) != 13 );  
      printf("%d",m);  
      putchar('\n');  
      scanf("%d",&i);  
   }  
 
   return 0; } 
