#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

//const int glob1 = 0x33;
int glob1;
int glob2 = 100; 


int main()
{
 //
 //pointers, in a programming language is nothing but 
 //virtual / logical addresses, in the OS/kernel context 
 //so, if we use virtual /logical addresses, they will 
 //be stored/assigned to pointer variables and dereferenced ??
 //
 //
 //  char *ptr = (char *)0x555555558010;
//   char *ptr = (char *)0xffffc87fffffffff;
   char *ptr1 = (char *)0x555555755010; //a virtual address, in global data-segment
   char *ptr2 = (char *)0x555555556001; //a virtual address, in global RO data-segment
 
//char *ptr = (char *)0x00600f00;
// char *ptr = (char *)0x0000000000000000;  //illegal virtual address
//char *ptr = (char *)0x7ffff7faa000;  //illegal virtual address
                                  //ununsed /invalid
 // char *ptr = (char *)0x0000000a;  //illegal/ununsed /invalid
//  char *ptr = (char *)0x08048000;  //illegal
//  char *ptr = (char *)0xc0000000;  //illegal/ununsed /invalid
// char *ptr = (char *)0x555555556002; //code /text segment/illegal for 
                           //write access 
  // char *ptr = (char *)0x561f5f4f2001; //RO region 
                           //write access 
//     char *ptr = 0x561f5f4f3000; //ready only data segment 
//   char *ptr = (char *)0x555555558002;   //read and write data segment 
  // char *ptr = 0xc0000000;   //valid kernel space segment,
                            //invalid access privileges 

//printf("ptr value is %x\n",(*ptr)); 
//*ptr = 0xaa;
//printf("ptr value is %x\n", (*ptr)); 

//   printf("ptr value is %c\n", (*ptr1)); 
//   *ptr1 = 0xaa;
//  printf("ptr value is %c\n", (*ptr1)); 


//   printf("ptr value is %c\n", (*ptr2)); 
//   *ptr2 = 0xaa;
   //printf("ptr value is %c\n", (*ptr2)); 

   int local1 = 0x55;

   glob1++;
   glob2++;


   printf(" glob1 is %x\n", glob1); 
  printf("address glob2 is %x\n", glob2); 
 
   printf("virtual address  of glob1 is %lx\n", (unsigned long)&glob1); 

   printf("virtual address of glob2 is %lx\n", (unsigned long)&glob2); 
   
   printf("virtual address of local1 is %lx\n",(unsigned long) &local1); 
  
   printf("virtual address of main is %lx\n",(unsigned long) &main); 
    

  //printf("address is %lx\n",(unsigned long) &sched_yield); 
   

  // alarm(120); //this is a system call API, 
                 //which tells the system/kernel, 
                 //to generate a SIGALRM signal 
                 //,after 30/60/120seconds !!!
                 //in this context, SIGALRM signal leads to 
                  //forcible termination of this process

//we use alarm() here, to forcibly terminate certain 
//high, real-time priority processes, during scheduling 
//experiments....these processes can completely 
//steal and use the cpu cycles, and starve all the 
//other processes on the processor....



   //sleep(1);

  while(1);  //a simple job, in an application/active application
 
//  while(1) sched_yield();
 //  alarm(20); //this is wrong ???

 
 //  while(1) {

              //we will add a job 
  //         sched_yield();
 //         printf("this is a bad diagnostics\n"); 
 //  }
   
 //  while(1) sleep(1);

   //this is not a good approach to deal with scheduler 


  //if this code/program/application reaches here, 
  //it will complete 
 
  //exit() will be executed - what happens, if exit() 
  //will be executed ??

  //exit() will normally terminate the process and the 
  //process will enter terminated state/zombie state - 
  //since exit() is explicitly invoked by the application/
  //code/program,we say that the process is normally 
  //terminated - this is a normal termination of 
  //a process - active application is completed  
  
   //we wish to complete the active application and  
   //effectively, the current process will be terminated
   //and scheduler will be invoked 
   //from here the scheduler will take over and schedule/
   //dispatch another process/active application

//   exit(0); 

  //pause() is a simple blocking system call API 
  //this system call API will set the state of the 
  //current process to blocked state and invoke the 
  //scheduler - so, the current process will not be
  //terminated, but in blocked state 

  //pause(); 

  exit(0); //this is from OS perspective - this system call API 
           //will do a normal termination of the current process

  //return 0; //this is from programming language perspective - 
              //this will internally invoke exit(0) 

} 
