
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
  write("in func1\n",9);
  sleep(11);
  write("in func2\n",9);
}

static void clone_func1(){
  write("in new clone process\n",21);
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
  #if 0
  unsigned long i, j;
  unsigned long buff[4096];
  i = getpid();
 
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
  alarm(5);
  while(1){

  }
  write("in main2\n",9);
  #endif
  #if 0
  write("in main1\n",9);
  sleep(20);
  write("in main2\n",9);
  sleep(20);
  write("in main3\n",9);
  func();
  write("in main4\n",9);
  
  #endif

  #if 1
  void *ptr1;
  char *ptr = (char *) expand(1,MAP_WR);
  *(ptr) = 'A';



  // u64 clone1_ustack_end_va = expand(1,MM_WR);
  // u64 * dum = clone1_ustack_end_va;
  // dum-=1000;
  // *dum = 0x100034;
  // exit(-5);
  // u64 clone1_ustack_start_va = clone1_ustack_end_va + 4000;
  // clone(clone_func1, clone1_ustack_start_va);
  // write("in main2\n",9);
  
  #endif
  

  exit(-5);
  return 0;
}
