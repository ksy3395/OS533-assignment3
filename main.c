#include "scheduler.h"
#include <stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFER 200

void asyncio_call(void *args);
extern ssize_t read_wrap(int, void*, int);

void print_nth_prime(void *pn)
{
  int n= *(int *) pn;

  int c = 1, i = 1;

  printf("Enter the primeth number you wish to see:");
  scanf("%d", &n);

  while(c <= n)
 {
    ++i;
    int j, isprime = 1;
   
    for(j = 2; j < i; ++j)
	 {
           if(i % j == 0)
		 {
                    isprime = 0;
                    break;
      		 }
    	 }	
    if(isprime)
	 {
     		 ++c;
         }
    yield();
  }
  printf("\n%dth prime: %d\n", n, i);
 
}

void print_power(void *pn)
{

  int num = *(int*)pn;

  int pow,i=1;

  long int sum=1;

  printf("\nEnter a number for the power: ");
  scanf("%d",&num);
  printf("Enter power: ");
  scanf("%d",&pow);

  while(i<=pow)
{
            sum=sum*num;
            i++;
	    yield();
}
  
  printf("\n%d to the power %d is: %ld\n",num,pow,sum);
  
}

void print_factorial(void*pn)
{

  long long i=1;
  unsigned long long f=1;
  int num= *(int*)pn;

  printf("Enter a number in range of 1-25 to find factorial: ");
  scanf("%d",&num);

  while(i<=num){
      f=f*i;
      i++;
	yield();
  }

  printf("\nFactorial of %d is: %lld\n",num,f);
  
}



void asyncio_call(void *args)
{
	int  fd,readvalue;
	int count = 65;
	unsigned char *buffer=malloc(sizeof(BUFFER));
	fd = open("/u/snuchhi/OS533/assign3/assign3.txt", O_RDONLY);
	readvalue = read_wrap(fd,buffer,count);
	printf("\nIn asyncio the read value is %d", readvalue);
        printf("\nThe data in file is : %s\n",buffer);

	close(fd);

}
	

int main(void)
{
  
//  printf("In main\n");

    scheduler_begin();
  
//  printf("did scheduler begin\n");
 
  int n1 ;
 
//  thread_fork(asyncio_call, &n1);

  thread_fork(print_nth_prime, &n1);

  thread_fork(print_power, &n1);

  thread_fork(asyncio_call,&n1);  //async io file open and read
 
  thread_fork(print_factorial, &n1);

  scheduler_end();

  free(current_thread->stack_base);
  free(current_thread); 

}


