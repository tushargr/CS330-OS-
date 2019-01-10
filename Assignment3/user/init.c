// // // // // #include<init.h>
// // // // // #include<memory.h>
// // // // // static void exit(int);
// // // // // static int main(void);
// // // // // //testcases

// // // // // void init_start()
// // // // // {
// // // // //   int retval = main();
// // // // //   exit(0);
// // // // // }

// // // // // /*Invoke system call with no additional arguments*/
// // // // // static long _syscall0(int syscall_num)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }

// // // // // /*Invoke system call with one argument*/

// // // // // static long _syscall1(int syscall_num, int exit_code)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }
// // // // // /*Invoke system call with two arguments*/

// // // // // static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }



// // // // // static void exit(int code)
// // // // // {
// // // // //   _syscall1(SYSCALL_EXIT, code);
// // // // // }

// // // // // static long getpid()
// // // // // {
// // // // //   return(_syscall0(SYSCALL_GETPID));
// // // // // }

// // // // // static long write(char *ptr, int size)
// // // // // {
// // // // //    return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// // // // // }

// // // // // static void signal(u64 signum, void* addr)
// // // // // {
// // // // //   _syscall2(SYSCALL_SIGNAL, signum,(long)addr) ;
// // // // // }

// // // // // static void alarm(u32 num)
// // // // // {
// // // // //   _syscall1(SYSCALL_ALARM, num) ;
// // // // // }

// // // // // static void sleep(u32 ticks)
// // // // // {
// // // // //   _syscall1(SYSCALL_SLEEP, ticks) ;
// // // // // }

// // // // // static void clone(void* func_addr,void* st_addr)
// // // // // {
// // // // //   _syscall2(SYSCALL_CLONE, (long)func_addr,(long)st_addr) ;
// // // // // }

// // // // // static char* expand(u64 size,u64 flags)
// // // // // {
// // // // //   return (char*)_syscall2(SYSCALL_EXPAND,size,flags);
// // // // // }

// // // // // static void fun2()
// // // // // {
// // // // //   write("Bye Bye\n",9);
// // // // //     exit(0);
// // // // // }

// // // // // static void fun1()
// // // // // {
// // // // //   write("Hello Hello\n",12);
// // // // //   sleep(8);
// // // // //   char* ptr = expand(5, MAP_WR);
// // // // //     ptr[3] = 'A';
// // // // //     ptr[4] = '\n';
// // // // //     write(ptr + 3, 2);
// // // // //     exit(0);
// // // // // }

// // // // // static int main()
// // // // // {
// // // // //     char* ptr1 = expand(20,MAP_WR);
// // // // //     char* ptr2 = expand(20,MAP_WR);
// // // // //     // char* ptr3 = expand(20,MAP_WR);
// // // // //     clone(&fun1,(char*)(((((u64)ptr1)>>12)+2)<<12)-1);
// // // // //     clone(&fun2,(char*)(((((u64)ptr2)>>12)+2)<<12)-1);
// // // // //     write("back to main\n",20);
// // // // //     exit(0);
// // // // // }

// // // // // // #include<init.h>
// // // // // // #include<memory.h>
// // // // // // static void exit(int);
// // // // // // static int main(void);


// // // // // // void init_start()
// // // // // // {
// // // // // //   int retval = main();
// // // // // //   exit(0);
// // // // // // }

// // // // // // /*Invoke system call with no additional arguments*/
// // // // // // static long _syscall0(int syscall_num)
// // // // // // {
// // // // // //   asm volatile ( "int $0x80;"
// // // // // //                  "leaveq;"
// // // // // //                  "retq;"
// // // // // //                 :::"memory");
// // // // // //   return 0;   /*gcc shutup!*/
// // // // // // }

// // // // // // /*Invoke system call with one argument*/

// // // // // // static long _syscall1(int syscall_num, int exit_code)
// // // // // // {
// // // // // //   asm volatile ( "int $0x80;"
// // // // // //                  "leaveq;"
// // // // // //                  "retq;"
// // // // // //                 :::"memory");
// // // // // //   return 0;   /*gcc shutup!*/
// // // // // // }
// // // // // // /*Invoke system call with two arguments*/

// // // // // // static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// // // // // // {
// // // // // //   asm volatile ( "int $0x80;"
// // // // // //                  "leaveq;"
// // // // // //                  "retq;"
// // // // // //                 :::"memory");
// // // // // //   return 0;   /*gcc shutup!*/
// // // // // // }
// // // // // // //////
// // // // // // static u64 _syscall3(int syscall_num, u32 size,int flags)
// // // // // // {
// // // // // //   asm volatile ( "int $0x80;"
// // // // // //                  "leaveq;"
// // // // // //                  "retq;"
// // // // // //                 :::"memory");
// // // // // //   return 0;   /*gcc shutup!*/
// // // // // // }

// // // // // // static u64 _syscall4(int syscall_num, u32 size,int flags)
// // // // // // {
// // // // // //   asm volatile ( "int $0x80;"
// // // // // //                  "leaveq;"
// // // // // //                  "retq;"
// // // // // //                 :::"memory");
// // // // // //   return 0;   /*gcc shutup!*/
// // // // // // }

// // // // // // static u64 _syscall5(int syscall_num, u64 arg1,u64 arg2)
// // // // // // {
// // // // // //   asm volatile ( "int $0x80;"
// // // // // //                  "leaveq;"
// // // // // //                  "retq;"
// // // // // //                 :::"memory");
// // // // // //   return 0;   /*gcc shutup!*/
// // // // // // }

// // // // // // static u64 _syscall6(int syscall_num, u64 arg1)
// // // // // // {
// // // // // //   asm volatile ( "int $0x80;"
// // // // // //                  "leaveq;"
// // // // // //                  "retq;"
// // // // // //                 :::"memory");
// // // // // //   return 0;   /*gcc shutup!*/
// // // // // // }

// // // // // // static u64 _syscall7(int syscall_num, u64 arg1)
// // // // // // {
// // // // // //   asm volatile ( "int $0x80;"
// // // // // //                  "leaveq;"
// // // // // //                  "retq;"
// // // // // //                 :::"memory");
// // // // // //   return 0;   /*gcc shutup!*/
// // // // // // }


// // // // // // /////

// // // // // // static void exit(int code)
// // // // // // {
// // // // // //   _syscall1(SYSCALL_EXIT, code);
// // // // // // }

// // // // // // static long getpid()
// // // // // // {
// // // // // //   return(_syscall0(SYSCALL_GETPID));
// // // // // // }

// // // // // // static long write(char *ptr, int size)
// // // // // // {
// // // // // //    return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// // // // // // }
// // // // // // /////
// // // // // // static void* expand(u32 size,int flags){
// // // // // //   return((void *)(_syscall3(SYSCALL_EXPAND,size,flags)));
// // // // // // }

// // // // // // static void* shrink(u32 size,int flags){
// // // // // //   return((void *)(_syscall4(SYSCALL_SHRINK,size,flags)));
// // // // // // }

// // // // // // static long signal(u64 arg1, u64 arg2)
// // // // // // {
// // // // // //    return(_syscall5(SYSCALL_SIGNAL, arg1, arg2));
// // // // // // }
// // // // // // static long alarm(u64 arg1)
// // // // // // {
// // // // // //    return(_syscall6(SYSCALL_ALARM, arg1));
// // // // // // }
// // // // // // static long sleep(u64 arg1)
// // // // // // {
// // // // // //    return(_syscall7(SYSCALL_SLEEP, arg1));
// // // // // // }

// // // // // // void sigfpehandler(){
// // // // // //   write("this is sigfpehandler\n",22);
// // // // // // }
// // // // // // void sigsegvhandler(){
// // // // // //   write("this is sigsegvhandler\n",22);
// // // // // // }
// // // // // // void sigalrmhandler(){
// // // // // //   write("this is sigalrmhandler\n",22);
// // // // // // }

// // // // // // /////


// // // // // // static int main()
// // // // // // {
// // // // // //   #if 0
// // // // // //   unsigned long i, j;
// // // // // //   unsigned long buff[4096];
// // // // // //   i = getpid();
// // // // // //   signal(SIGFPE,sigfpehandler);
// // // // // //   for(i=0; i<4096; ++i){
// // // // // //       j = buff[i];
// // // // // //   }
// // // // // //   i=0x100034;
// // // // // //   j = i / (i-0x100034);
// // // // // //   #endif
// // // // // //   // #if 0
// // // // // //   char * ptr = expand( 20, MAP_WR);
// // // // // //   if(ptr == NULL)
// // // // // //          write("FAILED\n", 7);

// // // // // //     *(ptr) = 'A';  /*page fault will occur and handled successfully*/
// // // // // //   // #endif
// // // // // //   #if 0
// // // // // //   write("in main1\n",9);
// // // // // //   signal(SIGSEGV,sigsegvhandler);
// // // // // //   write("in main2\n",9);
// // // // // //   int ar[10];
// // // // // //   ar[110]=1;
// // // // // //   write("in main2\n",9);
// // // // // //   #endif
// // // // // //   // sleep(3);
// // // // // //   // write("dsdh\n",5);
// // // // // //   // signal(SIGALRM,sigalrmhandler);
// // // // // //   // alarm(2);
// // // // // //   // while(1);

// // // // // //   // sleep(3);
// // // // // //   // write("dsdh\n",5);
// // // // // //   // while(1);
// // // // // //   exit(-5);
// // // // // //   return 0;
// // // // // // }


#include<init.h>
#include<memory.h>
static void exit(int);
static int main(void);


void init_start()
{
  int retval = main();
  exit(0);
}

/*Invoke system call with no additional arguments*/
static long _syscall0(int syscall_num)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

/*Invoke system call with one argument*/

static long _syscall1(int syscall_num, int exit_code)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}
/*Invoke system call with two arguments*/

static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}


static void exit(int code)
{
  _syscall1(SYSCALL_EXIT, code); 
}

static long getpid()
{
  return(_syscall0(SYSCALL_GETPID));
}

static long write(char *ptr, int size)
{
   return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
}

static long signal(u64 arg1, u64 arg2)
{
   return(_syscall2(SYSCALL_SIGNAL, arg1, arg2));
}
static long alarm(u64 arg1)
{
   return(_syscall1(SYSCALL_ALARM, arg1));
}
static long sleep(u64 arg1)
{
   return(_syscall1(SYSCALL_SLEEP, arg1));
}


static long clone(u64 arg1, u64 arg2)
{
   return(_syscall2(SYSCALL_CLONE, arg1,arg2));
}

static void * _syscall3(int syscall_num, u32 size, int flags)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

static void * expand(u32 size, int flags)
{
  return _syscall3(SYSCALL_EXPAND, size, flags);
  
}

static void sigfpehandler(){
  asm volatile ("push %rax;");
  asm volatile ("push %rbx;");
  asm volatile ("push %rcx;");
  asm volatile ("push %rdx;");
  asm volatile ("push %rsi;");
  asm volatile ("push %rdi;");
  asm volatile ("push %r8;");
  asm volatile ("push %r9;");
  asm volatile ("push %r10;");
  asm volatile ("push %r11;");
  asm volatile ("push %r12;");
  asm volatile ("push %r13;");
  asm volatile ("push %r14;");
  asm volatile ("push %r15;");
  write("this is sigfpehandler\n\n",23);
  asm volatile ("pop %r15;");
  asm volatile ("pop %r14;");
  asm volatile ("pop %r13;");
  asm volatile ("pop %r12;");
  asm volatile ("pop %r11;");
  asm volatile ("pop %r10;");
  asm volatile ("pop %r9;");
  asm volatile ("pop %r8;");
  asm volatile ("pop %rdi;");
  asm volatile ("pop %rsi;");
  asm volatile ("pop %rdx;");
  asm volatile ("pop %rcx;");
  asm volatile ("pop %rbx;");
  asm volatile ("pop %rax;");
}
static void sigsegvhandler(){
  write("this is sigsegvhandler\n\n",23);
}
static void sigalrmhandler(){
  write("this is sigalrmhandler\n",22);
}

static void func(){
  signal(SIGALRM,sigalrmhandler);
  write("in func1\n",9);
  alarm(10);
  while(1);
  write("in func2\n",9);
}
static void clone_func2(){
  write("in clone2\n",10);
  write("in clone2\n",10);
  exit(-5);
}

static void clone_func1(){
  write("in clone1\n",10);
  write("in clone1\n",10);
  write("in clone1\n",10);
  write("in clone1\n",10);write("in clone1\n",10);
  write("in clone1\n",10);
  exit(-5);
}

static int main()
{
  #if 0
  void *ptr1;
  char *ptr = (char *) expand(8, MAP_WR);
  
  if(ptr == NULL)
              write("FAILED\n", 7);
  
  *(ptr + 8192) = 'A';   /*Page fault will occur and handled successfully*/
   #endif
  #if 1
  unsigned long i, j;
  unsigned long buff[4096];
  i = getpid();
 signal(SIGFPE,sigfpehandler);
  for(i=0; i<4096; ++i){
      j = buff[i];
  }
  i=0x100034;
  j = i / (i-0x100034);
  #endif

  #if 0
  write("in main1\n",9);
  signal(SIGFPE,sigfpehandler);
  write("in main2\n",9);
  int i=10;
  int j=100;
  i=10/0;
  write("in main4\n",9);
  if(j==100)
  write("in main5\n",9);
  
  #endif
  #if 0
  write("in main1\n",9);
  signal(SIGSEGV,sigsegvhandler);
  write("in main2\n",9);
  int ar[10];
  ar[110]=1;
  write("in main2\n",9);
  #endif
  #if 0
  write("in main1\n",9);
  signal(SIGALRM,sigalrmhandler);
  write("in main2\n",9);
  alarm(1);
  while(1){

  }
  write("in main2\n",9);
  #endif
  #if 0
  write("in main1\n",9);
  sleep(10);
  write("in main2\n",9);
  sleep(10);
  write("in main3\n",9);
  func();
  write("in main4\n",9);
  
  #endif

  #if 0
  write("in main1\n",9);
  u64 clone1_ustack_end_va = expand(10,MAP_WR);
  u64 clone1_ustack_start_va = clone1_ustack_end_va + 4096;
  clone(clone_func1, clone1_ustack_start_va);
  write("in main1\n",9);
  u64 clone1_ustack_end_va2 = expand(10,MAP_WR);
  u64 clone1_ustack_start_va2 = clone1_ustack_end_va2 + 4096;
  clone(clone_func2, clone1_ustack_start_va2);
  
  write("in main2\n",9);
  write("in main3\n",9);
  
  
  #endif
  #if 0
  u64 * ptr = expand(10,MAP_WR);
  *ptr='A';
  write("main\n",5);
  write("main\n",5);
  
  ptr = expand(10,MAP_WR);
  *ptr='A';
  
  
  #endif
  

  exit(-5);
  return 0;
}

// // // // // #include<init.h>
// // // // // #include<memory.h>
// // // // // static void exit(int);
// // // // // static int main(void);


// // // // // void init_start()
// // // // // {
// // // // //   int retval = main();
// // // // //   exit(0);
// // // // // }

// // // // // /*Invoke system call with no additional arguments*/
// // // // // static long _syscall0(int syscall_num)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }

// // // // // /*Invoke system call with one argument*/

// // // // // static long _syscall1(int syscall_num, int exit_code)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }
// // // // // /*Invoke system call with two arguments*/

// // // // // static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }



// // // // // static void exit(int code)
// // // // // {
// // // // //   _syscall1(SYSCALL_EXIT, code);
// // // // // }

// // // // // static long getpid()
// // // // // {
// // // // //   return(_syscall0(SYSCALL_GETPID));
// // // // // }

// // // // // static long write(char *ptr, int size)
// // // // // {
// // // // //    return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// // // // // }

// // // // // static void signal(u64 signum, void* addr)
// // // // // {
// // // // //   _syscall2(SYSCALL_SIGNAL, signum,(long)addr) ;
// // // // // }
// // // // // static void alarm(u32 num)
// // // // // {
// // // // //   _syscall1(SYSCALL_ALARM, num) ;
// // // // // }
// // // // // static void sleep(u32 ticks)
// // // // // {
// // // // //   _syscall1(SYSCALL_SLEEP, ticks) ;
// // // // // }
// // // // // static void clone(void* func_addr,void* st_addr)
// // // // // {
// // // // //   _syscall2(SYSCALL_CLONE, (long)func_addr,(long)st_addr) ;
// // // // // }
// // // // // static char* expand(u64 size,u64 flags)
// // // // // {
// // // // //   return (char*)_syscall2(SYSCALL_EXPAND,size,flags);
// // // // // }

// // // // // static void fun2(){
// // // // //   write("Bye Bye\n",9);
// // // // //   exit(0);
// // // // // }

// // // // // static void fun3(){
// // // // //   write("I am 3\n",9);
// // // // //   exit(0);
// // // // // }
// // // // // static void fun1(){
// // // // //   write("Hello Hello\n",12);
// // // // //   exit(0);
// // // // // }

// // // // // static void fun(){
// // // // //   write("ALARM\n",12);
// // // // //   exit(0);
// // // // // }
// // // // // static int main()
// // // // // {
// // // // //   signal(SIGALRM,&fun);  
// // // // //   char* ptr1 = expand(20,MAP_WR);
// // // // //   // char* ptr2 = expand(20,MAP_WR);
// // // // //   // char* ptr3 = expand(20,MAP_WR);
// // // // //   // char* ptr4 = expand(20,MAP_WR);
// // // // //    sleep(6);
// // // // //   clone(&fun1,(char*)(((((u64)ptr1)>>12)+2)<<12)-1);
// // // // //   // alarm(6);
// // // // //   // while(1);
// // // // //   // clone(&fun2,(char*)(((((u64)ptr2)>>12)+2)<<12)-1);
// // // // //   // clone(&fun3,(char*)(((((u64)ptr3)>>12)+2)<<12)-1);
// // // // //   // clone(&fun,(char*)(((((u64)ptr4)>>12)+2)<<12)-1);
// // // // //   // exit(2);
  
// // // // //   alarm(3);
// // // // //   while(1);
// // // // //   // write("back to main\n",20);
// // // // //   exit(0);

// // // // //   //signal(SIGFPE,&fun);
// // // // //   //int a =1/0;
// // // // //   //exit(0);
// // // // //   //char *ptr = (char *)expand(20, MAP_WR);
// // // // //   //clone(&fun,ptr);
// // // // //   //write("a\n",2);
// // // // //   //return 0;
// // // // //   /*unsigned long i, j;
// // // // //   unsigned long buff[4096];
// // // // //   i = getpid();

// // // // //   for(i=0; i<4096; ++i){
// // // // //       j = buff[i];
// // // // //   }
// // // // //   i=0x100034;
// // // // //   j = i / (i-0x100034);
// // // // //   exit(-5);*/
// // // // // }



// // // // // #include<init.h>
// // // // // #include<memory.h>
// // // // // static void exit(int);
// // // // // static int main(void);


// // // // // void init_start()
// // // // // {
// // // // //   int retval = main();
// // // // //   exit(0);
// // // // // }

// // // // // /*Invoke system call with no additional arguments*/
// // // // // static long _syscall0(int syscall_num)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }

// // // // // /*Invoke system call with one argument*/

// // // // // static long _syscall1(int syscall_num, int exit_code)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }
// // // // // /*Invoke system call with two arguments*/

// // // // // static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// // // // // {
// // // // //   asm volatile ( "int $0x80;"
// // // // //                  "leaveq;"
// // // // //                  "retq;"
// // // // //                 :::"memory");
// // // // //   return 0;   /*gcc shutup!*/
// // // // // }



// // // // // static void exit(int code)
// // // // // {
// // // // //   _syscall1(SYSCALL_EXIT, code);
// // // // // }

// // // // // static long getpid()
// // // // // {
// // // // //   return(_syscall0(SYSCALL_GETPID));
// // // // // }

// // // // // static long write(char *ptr, int size)
// // // // // {
// // // // //    return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// // // // // }

// // // // // static void signal(u64 signum, void* addr)
// // // // // {
// // // // //   _syscall2(SYSCALL_SIGNAL, signum,(long)addr) ;
// // // // // }
// // // // // static void alarm(u32 num)
// // // // // {
// // // // //   _syscall1(SYSCALL_ALARM, num) ;
// // // // // }
// // // // // static void sleep(u32 ticks)
// // // // // {
// // // // //   _syscall1(SYSCALL_SLEEP, ticks) ;
// // // // // }
// // // // // static void clone(void* func_addr,void* st_addr)
// // // // // {
// // // // //   _syscall2(SYSCALL_CLONE, (long)func_addr,(long)st_addr) ;
// // // // // }
// // // // // static char* expand(u64 size,u64 flags)
// // // // // {
// // // // //   return (char*)_syscall2(SYSCALL_EXPAND,size,flags);
// // // // // }

// // // // // static void fun(){
// // // // //  // write("Hello Hello\n",12);
// // // // //  //  write("Hello 2\n",12);
// // // // //  //  //sleep(2);
// // // // //  //  write("Hello 3\n",12);
// // // // //   write("Hey\n",4);
// // // // //   exit(0);
// // // // // }
// // // // // static int main()
// // // // // {
// // // // //   // char* ptr = (char*)expand(20,MAP_WR);
// // // // //   // signal(SIGALRM,&fun);
// // // // //   // // sleep(10);
// // // // //   // alarm(5);
// // // // //   // while(1);

  
// // // // //   // clone(&fun,(char*)(((((u64)ptr)>>12)+2)<<12)-1);
// // // // //   sleep(3);
// // // // //   // write("back to main\n",20);
// // // // //   exit(0);

// // // // //   // signal(SIGFPE,&fun);
// // // // //   // int a =1/0;
// // // // //   // exit(0);
// // // // //   // char *ptr = (char *)expand(20, MAP_WR);
// // // // //   // clone(&fun,ptr);
// // // // //   // write("a\n",2);
// // // // //   // return 0;
// // // // //   // unsigned long i, j;
// // // // //   // unsigned long buff[4096];
// // // // //   // i = getpid();

// // // // //   // for(i=0; i<4096; ++i){
// // // // //   //     j = buff[i];
// // // // //   // }
// // // // //   // i=0x100034;
// // // // //   // j = i / (i-0x100034);
// // // // //   // exit(-5);
// // // // //   exit(0);
// // // // // }










































// // // #include<init.h>
// // // #include<memory.h>
// // // static void exit(int);
// // // static int main(void);


// // // void init_start()
// // // {
// // //   int retval = main();
// // //   exit(0);
// // // }

// // // /*Invoke system call with no additional arguments*/
// // // static long _syscall0(int syscall_num)
// // // {
// // //   asm volatile ( "int $0x80;"
// // //                  "leaveq;"
// // //                  "retq;"
// // //                 :::"memory");
// // //   return 0;   /*gcc shutup!*/
// // // }

// // // /*Invoke system call with one argument*/

// // // static long _syscall1(int syscall_num, int exit_code)
// // // {
// // //   asm volatile ( "int $0x80;"
// // //                  "leaveq;"
// // //                  "retq;"
// // //                 :::"memory");
// // //   return 0;   /*gcc shutup!*/
// // // }
// // // /*Invoke system call with two arguments*/

// // // static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// // // {
// // //   asm volatile ( "int $0x80;"
// // //                  "leaveq;"
// // //                  "retq;"
// // //                 :::"memory");
// // //   return 0;   /*gcc shutup!*/
// // // }



// // // static void exit(int code)
// // // {
// // //   _syscall1(SYSCALL_EXIT, code);
// // // }

// // // static long getpid()
// // // {
// // //   return(_syscall0(SYSCALL_GETPID));
// // // }

// // // static long write(char *ptr, int size)
// // // {
// // //    return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// // // }

// // // static void signal(u64 signum, void* addr)
// // // {
// // //   _syscall2(SYSCALL_SIGNAL, signum,(long)addr) ;
// // // }
// // // static void alarm(u32 num)
// // // {
// // //   _syscall1(SYSCALL_ALARM, num) ;
// // // }
// // // static void sleep(u32 ticks)
// // // {
// // //   _syscall1(SYSCALL_SLEEP, ticks) ;
// // // }
// // // static void clone(void* func_addr,void* st_addr)
// // // {
// // //   _syscall2(SYSCALL_CLONE, (long)func_addr,(long)st_addr) ;
// // // }
// // // static char* expand(u64 size,u64 flags)
// // // {
// // //   return (char*)_syscall2(SYSCALL_EXPAND,size,flags);
// // // }

// // // static void fun2(){
// // //   write("Bye Bye\n",9);
// // //   exit(0);
// // // }

// // // static void fun3(){
// // //   write("I am 3\n",9);
// // //   exit(0);
// // // }
// // // static void fun1(){
// // //   write("Hello Hello\n",12);
// // //   exit(0);
// // // }

// // // static void fun(){
// // //   write("ALARM\n",12);
// // //   exit(0);
// // // }
// // // static int main()
// // // {
// // //   signal(SIGALRM,&fun);  
// // //   char* ptr1 = expand(20,MAP_WR);
// // //   // char* ptr2 = expand(20,MAP_WR);
// // //   // char* ptr3 = expand(20,MAP_WR);
// // //   // char* ptr4 = expand(20,MAP_WR);
// // //    sleep(6);
// // //   clone(&fun1,(char*)(((((u64)ptr1)>>12)+2)<<12)-1);
// // //   // alarm(6);
// // //   // while(1);
// // //   // clone(&fun2,(char*)(((((u64)ptr2)>>12)+2)<<12)-1);
// // //   // clone(&fun3,(char*)(((((u64)ptr3)>>12)+2)<<12)-1);
// // //   // clone(&fun,(char*)(((((u64)ptr4)>>12)+2)<<12)-1);
// // //   // exit(2);
  
// // //   alarm(3);
// // //   while(1);
// // //   // write("back to main\n",20);
// // //   exit(0);

// // //   //signal(SIGFPE,&fun);
// // //   //int a =1/0;
// // //   //exit(0);
// // //   //char *ptr = (char *)expand(20, MAP_WR);
// // //   //clone(&fun,ptr);
// // //   //write("a\n",2);
// // //   //return 0;
// // //   /*unsigned long i, j;
// // //   unsigned long buff[4096];
// // //   i = getpid();

// // //   for(i=0; i<4096; ++i){
// // //       j = buff[i];
// // //   }
// // //   i=0x100034;
// // //   j = i / (i-0x100034);
// // //   exit(-5);*/
// // // }



// #include<init.h>
// #include<memory.h>
// static void exit(int);
// static int main(void);


// void init_start()
// {
//   int retval = main();
//   exit(0);
// }

// /*Invoke system call with no additional arguments*/
// static long _syscall0(int syscall_num)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }

// /*Invoke system call with one argument*/

// static long _syscall1(int syscall_num, int exit_code)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }
// /*Invoke system call with two arguments*/

// static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }



// static void exit(int code)
// {
//   _syscall1(SYSCALL_EXIT, code);
// }

// static long getpid()
// {
//   return(_syscall0(SYSCALL_GETPID));
// }

// static long write(char *ptr, int size)
// {
//    return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// }

// static void signal(u64 signum, void* addr)
// {
//   _syscall2(SYSCALL_SIGNAL, signum,(long)addr) ;
// }
// static void alarm(u32 num)
// {
//   _syscall1(SYSCALL_ALARM, num) ;
// }
// static void sleep(u32 ticks)
// {
//   _syscall1(SYSCALL_SLEEP, ticks) ;
// }
// static void clone(void* func_addr,void* st_addr)
// {
//   _syscall2(SYSCALL_CLONE, (long)func_addr,(long)st_addr) ;
// }
// static char* expand(u64 size,u64 flags)
// {
//   return (char*)_syscall2(SYSCALL_EXPAND,size,flags);
// }

// static void fun(){
//  // write("Hello Hello\n",12);
//  //  write("Hello 2\n",12);
//  //  //sleep(2);
//  //  write("Hello 3\n",12);
//   write("Hey\n",4);
// }
// static int main()
// {
//   // char* ptr = (char*)expand(20,MAP_WR);
//   // signal(SIGALRM,&fun);
//   // // sleep(10);
//   // alarm(5);
//   // // while(1);

  
//   // // clone(&fun,(char*)(((((u64)ptr)>>12)+2)<<12)-1);
//   // sleep(3);
//   // // write("back to main\n",20);
//   // exit(0);

//   signal(SIGFPE,&fun);
//   int a =1/0;
//   exit(0);

// }



// #include<init.h>
// #include<memory.h>
// static void exit(int);
// static int main(void);


// void init_start()
// {
//   int retval = main();
//   exit(0);
// }

// /*Invoke system call with no additional arguments*/
// static long _syscall0(int syscall_num)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }

// /*Invoke system call with one argument*/

// static long _syscall1(int syscall_num, int exit_code)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }
// /*Invoke system call with two arguments*/

// static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }



// static void exit(int code)
// {
//   _syscall1(SYSCALL_EXIT, code);
// }

// static long getpid()
// {
//   return(_syscall0(SYSCALL_GETPID));
// }

// static long write(char *ptr, int size)
// {
//    return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// }

// static void signal(u64 signum, void* addr)
// {
//   _syscall2(SYSCALL_SIGNAL, signum,(long)addr) ;
// }

// static void alarm(u32 num)
// {
//   _syscall1(SYSCALL_ALARM, num) ;
// }

// static void sleep(u32 ticks)
// {
//   _syscall1(SYSCALL_SLEEP, ticks) ;
// }

// static void clone(void* func_addr,void* st_addr)
// {
//   _syscall2(SYSCALL_CLONE, (long)func_addr,(long)st_addr) ;
// }

// static char* expand(u64 size,u64 flags)
// {
//   return (char*)_syscall2(SYSCALL_EXPAND,size,flags);
// }

// static void fun2()
// {
//   write("Bye Bye\n",9);
//     exit(0);
// }

// static void fun1()
// {
//   write("Hello Hello\n",12);
//   sleep(15);
//   char* ptr = expand(5, MAP_WR);
//     ptr[3] = 'A';
//     ptr[4] = '\n';
//     write(ptr + 3, 2);
//     exit(0);
// }

// static int main()
// {
//     char* ptr1 = expand(20,MAP_WR);
//     clone(&fun1,(char*)(((((u64)ptr1)>>12)+2)<<12)-1);
//     char* ptr2 = expand(20,MAP_WR);
//     clone(&fun2,(char*)(((((u64)ptr2)>>12)+2)<<12)-1);
//     char* ptr3 = expand(20,MAP_WR);
//     ptr3[0] = 'Y';
//     ptr3[1] = 'o';
//     ptr3[2] = '\n';
//     write(ptr3, 3);
//     write("back to main\n",20);
//     exit(0);
// }


// #include<init.h>
// #include<memory.h>
// static void exit(int);
// static int main(void);


// void init_start()
// {
//   int retval = main();
//   exit(0);
// }

// /*Invoke system call with no additional arguments*/
// static long _syscall0(int syscall_num)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }

// /*Invoke system call with one argument*/

// static long _syscall1(int syscall_num, int exit_code)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }
// /*Invoke system call with two arguments*/

// static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// {
//   asm volatile ( "int $0x80;"
//                  "leaveq;"
//                  "retq;"
//                 :::"memory");
//   return 0;   /*gcc shutup!*/
// }



// static void exit(int code)
// {
//   _syscall1(SYSCALL_EXIT, code);
// }

// static long getpid()
// {
//   return(_syscall0(SYSCALL_GETPID));
// }

// static long write(char *ptr, int size)
// {
//    return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// }

// static void signal(u64 signum, void* addr)
// {
//   _syscall2(SYSCALL_SIGNAL, signum,(long)addr) ;
// }
// static void alarm(u32 num)
// {
//   _syscall1(SYSCALL_ALARM, num) ;
// }
// static void sleep(u32 ticks)
// {
//   _syscall1(SYSCALL_SLEEP, ticks) ;
// }
// static void clone(void* func_addr,void* st_addr)
// {
//   _syscall2(SYSCALL_CLONE, (long)func_addr,(long)st_addr) ;
// }
// static char* expand(u64 size,u64 flags)
// {
//   return (char*)_syscall2(SYSCALL_EXPAND,size,flags);
// }

// static void fun2(){
//   write("Bye Bye\n",9);
//   exit(0);
// }

// static void fun1(){
//   write("Hello Hello\n",12);
//   exit(0);
// }

// static void fun3(){
//   write("Once Again\n",12);
//   exit(0);
// }

// static int main()
// {
//   char* ptr1 = expand(20,MAP_WR);
//   char* ptr2 = expand(20,MAP_WR);
//   char* ptr3 = expand(20,MAP_WR);
//   clone(&fun1,(char*)(((((u64)ptr1)>>12)+2)<<12)-1);
//   clone(&fun2,(char*)(((((u64)ptr2)>>12)+2)<<12)-1);
//   clone(&fun3,(char*)(((((u64)ptr3)>>12)+2)<<12)-1);
//   write("back to main\n",20);
//   exit(0);

//   //signal(SIGFPE,&fun);
//   //int a =1/0;
//   //exit(0);
//   //char *ptr = (char *)expand(20, MAP_WR);
//   //clone(&fun,ptr);
//   //write("a\n",2);
//   //return 0;
//   /*unsigned long i, j;
//   unsigned long buff[4096];
//   i = getpid();

//   for(i=0; i<4096; ++i){
//       j = buff[i];
//   }
//   i=0x100034;
//   j = i / (i-0x100034);
//   exit(-5);*/
// }






// #include<init.h>
// static void exit(int);
// static int main(void);


// void init_start()
// {
//     int retval = main();
//     exit(0);
// }

// /*Invoke system call with no additional arguments*/
// static long _syscall0(int syscall_num)
// {
//     asm volatile ("int $0x80;"
//                   "leaveq;"
//                   "retq;"
//                   :::"memory");
//     return 0;   /*gcc shutup!*/
// }

// /*Invoke system call with one argument*/

// static long _syscall1(int syscall_num, int exit_code)
// {
//     asm volatile ("int $0x80;"
//                   "leaveq;"
//                   "retq;"
//                   :::"memory");
//     return 0;   /*gcc shutup!*/
// }
// /*Invoke system call with two arguments*/

// static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
// {
//     asm volatile ("int $0x80;"
//                   "leaveq;"
//                   "retq;"
//                   :::"memory");
//     return 0;   /*gcc shutup!*/
// }

// static void exit(int code)
// {
//     _syscall1(SYSCALL_EXIT, code);
// }

// static void alarm(int ticks)
// {
//     _syscall1(SYSCALL_ALARM, ticks);
// }

// static void reg_handler(int signo, void* handler)
// {
//     _syscall2(SYSCALL_SIGNAL, signo, (unsigned long) handler);
// }

// static long getpid()
// {
//     return(_syscall0(SYSCALL_GETPID));
// }

// static long write(char *ptr, int size)
// {
//     return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
// }

// static void sleep(int ticks)
// {
//     _syscall1(SYSCALL_SLEEP, ticks);
// }

// static void clone(void *th_func, void *user_stack)
// {
//     _syscall2(SYSCALL_CLONE, (u64) th_func, (u64) user_stack);
// }

// static void alarm_handler()
// {
//     write("ping\n", 5);
// }
// int main()
// {
    

//     reg_handler(SIGALRM, alarm_handler);
//     unsigned long i, j;
//     unsigned long buff[4096];
//     i = getpid();
//     write("alarm\n", 6);
//     alarm(3);

//     sleep(4);
//     write("woke up\n", 8);

//     sleep(6);
//     write("woke up\n", 8);

//     for(i = 0; i < 4096; ++i)
//         j = buff[i];
//     i = 0x100034;
//     j = i / (i - 0x100034);
//     exit(-5);
//     return 0;
// }























