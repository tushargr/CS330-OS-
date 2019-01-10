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
static int _syscall0(int syscall_num)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

/*Invoke system call with one argument*/

static int _syscall1(int syscall_num, int exit_code)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

/*Invoke system call with two argument*/

static  u64 _syscall2(int syscall_num, unsigned long buf , unsigned long len)
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

static int getpid()
{
  return(_syscall0(SYSCALL_GETPID));
}

static void write(char * buf, int len)
{
  return(_syscall2(SYSCALL_WRITE ,buf, len));
}

static void * expand(int size)
{
  return(_syscall2(SYSCALL_EXPAND , size, MAP_RD));
}

static void * shrink(int size)
{
  return(_syscall2(SYSCALL_SHRINK , size, MAP_WR));
}


static int main()
{
  unsigned long i;
#if 0
  char *ptr = (char *) expand(8);
  *ptr = 'A';
  // i = *ptr;
#endif
#if 0
  
  char *ptr = (unsigned long *)0x7FF000001;
  *ptr='A';
#endif

#if 1
  write("FAILEE\n", 7);
  void *ptr1;
  char *ptr = (char *) expand(8,MAP_WR);
  // printf("%x\n",ptr);
  if(ptr == NULL)
      write("FAILED\n", 7);
  
  *(ptr + 8192) = 'A';   /*Page fault will occur and handled successfully*/
  
  ptr1 = (char *) shrink(7);
  *ptr = 'A';          /*Page fault will occur and handled successfully*/

  *(ptr + 4096) = 'A';   /*Page fault will occur and PF handler should termminate 
  //                  the process (gemOS shell should be back) by printing an error message*/
#endif

  exit(0);
  return 0;
}
