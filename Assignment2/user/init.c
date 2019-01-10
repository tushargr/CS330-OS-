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

static long _syscall2(int syscall_num, char* buff, int length)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

static long _syscall3(int syscall_num, u32 size, int flags)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

static long _syscall4(int syscall_num, u32 size, int flags)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}




static long getpid()
{
  return(_syscall0(SYSCALL_GETPID));
}

static void exit(int code)
{
  _syscall1(SYSCALL_EXIT, code);
}

static long write(char* buff, int length)
{
  return(_syscall2(SYSCALL_WRITE, buff, length));
}

static void* expand(u32 size, int flags)
{
  u64 temp=_syscall3(SYSCALL_EXPAND, size, flags);
  if(temp==0){
    return NULL;
  }
  else{
    return((void*)temp);
  }
}

static void* shrink(u32 size, int flags)
{
  u64 temp=_syscall4(SYSCALL_SHRINK, size, flags);
  if(temp==0){
    return NULL;
  }
  else{
    return((void*)temp);
  }
}


static int main()
{
  #if 0
  char* ptr = ( char* ) expand(8, MAP_WR);
  *(ptr + 4096) = 'X';
  write(ptr+4096,1);
  shrink(8, MAP_WR);
  *(ptr + 4096) = 'A';
  #endif  
  #if 0
    char* ptr = ( char* ) expand(8, MAP_WR);
  *(ptr + 4096) = 'X';
  write(ptr+4096,1);
  shrink(8, MAP_WR);
  // *(ptr + 4096) = 'A';
  int i = write(ptr + 4096,1);

  if( i ==-1)
  {
    write("FAILED\n",7);
  }
  else
  {
    write("SUCCESS\n",8);
  }
  char* ptr1 = (char*) expand(4,MAP_WR);
  *(ptr + 4096) = 'V';
  write(ptr + 4096,1);
  #endif
  
  #if 0
  void *ptr1;
  char *ptr = (char *) expand(20, MAP_WR);

  if(ptr == NULL)
              write("FAILED\n", 7);

  *(ptr + 8192) = 'A';   /*Page fault will occur and handled successfully*/

  write(ptr+8192,1); /*check if value is written properly */

  ptr1 = (char *) shrink(100, MAP_WR);

  if(ptr1 != NULL)
      write("Shrink not working\n",18);


  *ptr = 'A';          /*Page fault will occur and handled successfully*/

  ptr1 = (char*)shrink(20,MAP_WR);


  if(ptr1==NULL)
      write("shrink not working\n",18);

  char *ptr2 = (char *) expand(12, MAP_RD);

  if(ptr2==NULL)
    write("expand not working\n",18);

  ptr = (char*)expand(5,MAP_WR);

  long k =write(ptr+1,1);   /*write should get failed*/

  if(k!=-1)
    write("write not working\n",17);

  k=write("Hello\n",7);

  if(k!=-1)
    write("write working\n",14);

  u64* t = (u64*)(0x7FF000000+16);
  *t = 64;

  write("stack page fault handled\n",25);

  int* ptr3 = (int *) expand(20, MAP_RD);

  int x=*(ptr3+1);

  if(x==0){
    write("read only page fault handled\n",29);
  }

  *(ptr3 + 1024)  = 100;   /*page fault will occur and not handled successfully"*/
 #endif

  void *ptr1;
  char *ptr = (char *) expand(8, MAP_WR);
  
  if(ptr == NULL)
              write("FAILED\n", 7);
  
  *(ptr + 8192) = 'A';   /*Page fault will occur and handled successfully*/
  
  // ptr1 = (char *) shrink(7, MAP_WR);
  // *ptr = 'A';          /*Page fault will occur and handled successfully*/

  // *(ptr + 4096) = 'A';   //Page fault will occur and PF handler should termminate 
   exit(0);
}
