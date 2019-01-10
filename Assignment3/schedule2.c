#include<context.h>
#include<memory.h>
#include<schedule.h>
#include<apic.h>
#include<lib.h>
#include<idt.h>
static u64 numticks;

static void save_current_context(struct exec_context *current,u64 top,u64 e_regs)
{
  /*Your code goes in here*/
  u64* rsp=top;
  u64* rbp=e_regs;
  current->regs.r15=*(rsp);
  current->regs.r14=*(rsp+1);
  current->regs.r13=*(rsp+2);
  current->regs.r12=*(rsp+3);
  current->regs.r11=*(rsp+4);
  current->regs.r10=*(rsp+5);
  current->regs.r9=*(rsp+6);
  current->regs.r8=*(rsp+7);
  current->regs.rdi=*(rsp+8);
  current->regs.rsi=*(rsp+9);
  current->regs.rdx=*(rsp+10);
  current->regs.rcx=*(rsp+11);
  current->regs.rbx=*(rsp+12);
  current->regs.rax=*(rsp+13);
  current->regs.rbp=*(rbp);
  current->regs.entry_rip=*(rbp+1);
  current->regs.entry_cs=*(rbp+2);
  current->regs.entry_rflags=*(rbp+3);
  current->regs.entry_rsp=*(rbp+4);
  current->regs.entry_ss=*(rbp+5);
  printf("saving current context\n");
}

long schedule_context(struct exec_context *next,u64 top,u64 e_regs)
{
  /*Your code goes in here. get_current_ctx() still returns the old context*/
  struct exec_context *current = get_current_ctx();
  printf("schedluing: old pid = %d  new pid  = %d\n", current->pid, next->pid); /*XXX: Don't remove*/
 /*These two lines must be executed*/
  set_tss_stack_ptr(next);
  set_current_ctx(next);
 /*Your code for scheduling context*/
  // printf("yo\n");
  save_current_context(current,top,e_regs);
  // printf("hyo\n");
  u64 r15=next->regs.r15;
  u64 r14=next->regs.r14;
  u64 r13=next->regs.r13;
  u64 r12=next->regs.r12;
  u64 r11=next->regs.r11;
  u64 r10=next->regs.r10;
  u64 r9=next->regs.r9;
  u64 r8=next->regs.r8;
  u64 rbp=next->regs.rbp;
  u64 rdi=next->regs.rdi;
  u64 rsi=next->regs.rsi;
  u64 rdx=next->regs.rdx;
  u64 rcx=next->regs.rcx;
  u64 rbx=next->regs.rbx;
  u64 rax=next->regs.rax;//added
  u64 entry_rip=next->regs.entry_rip;
  u64 entry_cs=next->regs.entry_cs;
  u64 entry_rflags=next->regs.entry_rflags;
  u64 entry_rsp=next->regs.entry_rsp;
  u64 entry_ss=next->regs.entry_ss;
  asm volatile(
    "push %0;"
    "push %1;"
    "push %2;"
    "push %3;"
    "push %4;"
    "push %5"
    ::"r"(rax),"r"(rbx),"r"(rcx),"r"(rdx),"r"(rsi),"r"(rdi)
  );
  asm volatile(
    "push %0;"
    "push %1;"
    "push %2;"
    "push %3;"
    "push %4;"
    "push %5;"
    "push %6;"
    "push %7;"
    "mov %%rsp, %8;"
    ::"r"(r8),"r"(r9),"r"(r10),"r"(r11),"r"(r12),"r"(r13),"r"(r14),"r"(r15),"r"(top)
  );
  // u64* temp_urbp=urbp;
  // *(temp_urbp)=rbp;
  u64* temp_e_regs=e_regs;
  *(temp_e_regs)=rbp;
  *(temp_e_regs+1)=entry_rip;
  *(temp_e_regs+2)=entry_cs;
  *(temp_e_regs+3)=entry_rflags;
  *(temp_e_regs+4)=entry_rsp;
  *(temp_e_regs+5)=entry_ss;
  return top;
}

static struct exec_context *pick_next_context(struct exec_context *list)
{
  /*Your code goes in here*/
  struct exec_context *current = get_current_ctx();
  u32 pid=current->pid;
  // printf("hi %d\n",pid);
  int flag=0;
  for(int i=1;i<16;i++){
    if ((list+i)->state==READY){
      flag=1;
      // printf("flag cnalscn %d %d\n",current->state,current->pid);
      break;
    }
  }
  if(flag==0){
    // printf("%d\n",current->pid );
    return current;
  }
  // else{
  for(int i=1;i<16;i++){
    if((pid+i)%16!=0 && (list+(pid+i)%16)->state==READY){
        return (list+(pid+i)%16);
    }
  }







  // while(1){
  //   printf("hi %d\n",pid);
  //   i=i%16;
  //   if(i==0 && cnt==0){
  //     cnt=1;
  //     i++;
  //     continue;
  //   }
  //   else if(i==0 && cnt==1){
  //     return list;
  //   }
  //   if(i==pid && ((list+i)->state==READY || (list+i)->state==RUNNING)){
  //     // printf("hi %d\n",pid);
  //       return (list+i);
  //   }
  //   else if(i==pid){
  //     break;
  //   }
  //   if((list+i)->state==READY){
  //     return (list+i);
  //   }
  //   i++;
  // }
}
long schedule(u64 top,u64 e_regs)
{

 struct exec_context *next;
 struct exec_context *current = get_current_ctx();
 struct exec_context *list = get_ctx_list();
 // printf("yo1\n");
 next = pick_next_context(list);
 // printf("yo2\n");
 current->state = READY;
 next->state=RUNNING;
 // printf("yo2wqdwqd %d\n",next->pid);
 return schedule_context(next,top,e_regs);
}

static void do_sleep_and_alarm_account(u64 e_regs)
{
 /*All processes in sleep() must decrement their sleep count*/
 struct exec_context *init = get_ctx_by_pid(1);
 if(init->alarm_config_time>0){
   if(init->ticks_to_alarm>0){
     init->ticks_to_alarm=init->ticks_to_alarm-1;
   }
   else if(init->ticks_to_alarm==0){
        init->pending_signal_bitmap = (init->pending_signal_bitmap | 0x4);
        u64* ustackp=e_regs;
        ustackp=ustackp+4;
        u64* urip=e_regs;
        urip=urip+1;
        printf("hi inside do_sleep_and_alarm_account\n");
        invoke_sync_signal(SIGALRM,ustackp,urip);
        init->alarm_config_time=0;
   }
 }

 if(init->ticks_to_sleep>0){
   init->ticks_to_sleep = (init->ticks_to_sleep)-1;
   if(init->ticks_to_sleep==0){
     init->state = READY;
   }
 }

}

/*The five functions above are just a template. You may change the signatures as you wish*/
void handle_timer_tick()
{
 /*
   This is the timer interrupt handler.
   You should account timer ticks for alarm and sleep
   and invoke schedule
 */
 u64 top;
 u64 e_regs;
 // u64 urbp;
 asm volatile(
     "push %%rax;"
     "push %%rbx;"
     "push %%rcx;"
     "push %%rdx;"
     "push %%rsi;"
     "push %%rdi;"
     "push %%r8;"
     "push %%r9;"
     "push %%r10;"
     "push %%r11;"
     "push %%r12;"
     "push %%r13;"
     "push %%r14;"
     "push %%r15;"
      //////////
     "mov %%rsp, %0;"
     "mov %%rbp, %1;"
     : "=r" (top),"=r" (e_regs)
   );
   // e_regs+=8;
   // urbp=e_regs-8;

  do_sleep_and_alarm_account(e_regs);
  // top=schedule(top,e_regs,urbp);//change the function scheduler
  printf("before schedule %x\n",top);
  top=schedule(top,e_regs);
  // printf("after schedule %x\n",top);

  printf("Got a tick. #ticks = %u\n", numticks++);   /*XXX Do not modify this line*/
  ack_irq();  /*acknowledge the interrupt, before calling iretq */
  asm volatile(
    "mov %0,%%rsp;"
    "pop %%r15;"
    "pop %%r14;"
    "pop %%r13;"
    "pop %%r12;"
    "pop %%r11;"
    "pop %%r10;"
    "pop %%r9;"
    "pop %%r8;"
    "pop %%rdi;"
    "pop %%rsi;"
    "pop %%rdx;"
    "pop %%rcx;"
    "pop %%rbx;"
    "pop %%rax;"
    //////////
    ::"r"(top)
    );

  asm volatile(
              "mov %%rbp, %%rsp;"
              "pop %%rbp;"
               "iretq;"
               :::"memory");
}

void do_exit()
{
  /*You may need to invoke the scheduler from here if there are
    other processes except swapper in the system. Make sure you make
    the status of the current process to UNUSED before scheduling
    the next process. If the only process alive in system is swapper,
    invoke do_cleanup() to shutdown gem5 (by crashing it, huh!)
    */
    do_cleanup();  /*Call this conditionally, see comments above*/
}

/*system call handler for sleep*/
long do_sleep(u32 ticks)
{
  // struct exec_context *current = get_current_ctx();
  //   current->ticks_to_sleep = ticks;
  //   current->state = WAITING;
  //   u64* os_pfn = osmap((u64)current->os_stack_pfn);
  //   os_pfn+=512;
  //   u64 entry_ss = *(os_pfn-1);
  //   u64 entry_rsp = *(os_pfn-2);
  //   u64 entry_rflags = *(os_pfn-3);
  //   u64 entry_cs = *(os_pfn-4);
  //   u64 entry_rip = *(os_pfn-5);
  //   u64 rbx = *(os_pfn-6);
  //   u64 rcx = *(os_pfn-7);
  //   u64 rdx = *(os_pfn-8);
  //   u64 rsi = *(os_pfn-9);
  //   u64 rdi = *(os_pfn-10);
  //   u64 rbp = *(os_pfn-11);
  //   u64 r8 = *(os_pfn-12);
  //   u64 r9 = *(os_pfn-13);
  //   u64 r10 = *(os_pfn-14);
  //   u64 r11 = *(os_pfn-15);
  //   u64 r12 = *(os_pfn-16);
  //   u64 r13 = *(os_pfn-17);
  //   u64 r14 = *(os_pfn-18);
  //   u64 r15 = *(os_pfn-19);

  //   u64 top;
  //   u64 e_regs;
  //   // u64 urbp;
  //   asm volatile(
  //     "push %0;"
  //     "push %1;"
  //     "push %2;"
  //     "push %3;"
  //     "push %4;"
  //     ::"r"(rbx),"r"(rcx),"r"(rdx),"r"(rsi),"r"(rdi)
  //   );

  //   asm volatile(
  //     "push %0;"
  //     "push %1;"
  //     "push %2;"
  //     "push %3;"
  //     "push %4;"
  //     "push %5;"
  //     "push %6;"
  //     "push %7;"
  //     "mov %%rsp, %8;"
  //     ::"r"(r8),"r"(r9),"r"(r10),"r"(r11),"r"(r12),"r"(r13),"r"(r14),"r"(r15),"r"(top)
  //   );

  //   asm volatile(
  //     "mov %0,0(%%rbp);"
  //     "mov %1,8(%%rbp);"
  //     "mov %2,16(%%rbp);"
  //     "mov %3,24(%%rbp);"
  //     "mov %4,32(%%rbp);"
  //     "mov %5,40(%%rbp);"
  //     ::"r"(rbp),"r"(entry_rip),"r"(entry_cs),"r"(entry_rflags),"r"(entry_rsp),"r"(entry_ss)
  //   );

  //   asm volatile(
  //     "mov %%rbp,%0;"
  //     : "=r" (e_regs)
  //   );
  //   // e_regs+=8;
  //   // urbp=e_regs-8;
  //  // top=schedule(top,e_regs,urbp);
  //  do_sleep_and_alarm_account(e_regs);
  //  printf("Scheduling\n");
  //  top=schedule(top,e_regs);

  //  asm volatile(
  //    "mov %0,%%rsp;"
  //    "pop %%r15;"
  //    "pop %%r14;"
  //    "pop %%r13;"
  //    "pop %%r12;"
  //    "pop %%r11;"
  //    "pop %%r10;"
  //    "pop %%r9;"
  //    "pop %%r8;"
  //    "pop %%rdi;"
  //    "pop %%rsi;"
  //    "pop %%rdx;"
  //    "pop %%rcx;"
  //    "pop %%rbx;"
  //    "pop %%rax;"
  //    //////////
  //    ::"r"(top)
  //    );

  //  asm volatile(
  //              "mov %%rbp, %%rsp;"
  //              "pop %%rbp;"
  //               "iretq;"
  //               :::"memory");

}

/*
  system call handler for clone, create thread like
  execution contexts
*/
long do_clone(void *th_func, void *user_stack)
{
  // struct exec_context *parent = get_current_ctx();
  //   struct exec_context *new_ctx = get_new_ctx();
  //   new_ctx->os_stack_pfn = os_pfn_alloc(OS_PT_REG);
  //   u32 pid=new_ctx->pid;
  //   u32 i=0;
  //   while(1){
  //     if(parent->name[i]=='\0')break;
  //     new_ctx->name[i]=parent->name[i];
  //     i++;
  //   }
  //   if(pid<10){
  //     new_ctx->name[i]=pid+'0';
  //   }
  //   else{
  //       int res=pid%10;
  //       int d=pid/10;
  //       new_ctx->name[i]=d+'0';
  //       new_ctx->name[i+1]=res+'0';
  //   }
  //   new_ctx->regs.entry_rflags = parent->regs.entry_rflags;
  //   new_ctx->regs.entry_cs = 0x23;
  //   new_ctx->regs.entry_ss = 0x2b;
  //   new_ctx->regs.entry_rsp = user_stack;
  //   new_ctx->regs.entry_rip = th_func;
  //   new_ctx->regs.rbp = user_stack;
  //   new_ctx->state=READY;

  //   return;
}

long invoke_sync_signal(int signo, u64 *ustackp, u64 *urip)
{
  /*If signal handler is registered, manipulate user stack and RIP to execute signal handler*/
  /*ustackp and urip are pointers to user RSP and user RIP in the exception/interrupt stack*/
  struct exec_context *current = get_current_ctx();
  if(current->sighandlers[signo]!=NULL && current->sighandlers[signo]!=MAX_SIGNALS){
/*------------------------
    u64 signum=current->sighandlers[signo];
    if(signo==0 && (current->pending_signal_bitmap & 0x1)){
       current->pending_signal_bitmap=((current->pending_signal_bitmap >> 1) << 1);
       // u64 *rsp=(*ustackp);
       // rsp-=1;
       // *ustackp=rsp;
       // u64 *d=(*ustackp);
       // *(d)=(*urip);
       u64 **var = (u64 **)ustackp;
       *var = *var - 1;
       **var = *urip;
       *urip=signum;
    }
    else if(signo==1 && ((current->pending_signal_bitmap & 0x2)>0)){
      u32 temp=(current->pending_signal_bitmap & 0x1);
      current->pending_signal_bitmap=(((current->pending_signal_bitmap >> 2) << 2) | temp);
      u64 **var = (u64 **)ustackp;
      *var = *var - 1;
      **var = *urip;
      // u64 *rsp=(*ustackp);
      // rsp-=1;
      // *ustackp=rsp;
      // // u64 *d=(*ustackp);
      // *(rsp)=(*urip);

      *urip=signum;
    }
    else if(signo==2 && ((current->pending_signal_bitmap & 0x4)>0)){
      u32 temp=(current->pending_signal_bitmap & 0x3);
      current->pending_signal_bitmap=(((current->pending_signal_bitmap >> 3) << 3) | temp);
      // u64 rsp=(*ustackp);
      // rsp-=8;
      // u64 *rsp=(*ustackp);
      // rsp-=1;
      // *ustackp=rsp;
      // u64 *d=(*ustackp);
      // *(d)=(*urip);
      u64 **var = (u64 **)ustackp;
      *var = *var - 1;
      **var = *urip;
      *urip=signum;
    }
---------------------*/
      u64 signum=current->sighandlers[signo];
      u64 **var = (u64 **)ustackp;
      *var = *var - 1;
      **var = *urip;
      *urip=signum;
      printf("hi inside invoke_sync_signal\n");
      // if(signo==0){
      //    // current->pending_signal_bitmap=((current->pending_signal_bitmap >> 1) << 1);
      //    // u64 *rsp=(*ustackp);
      //    // rsp-=1;
      //    // *ustackp=rsp;
      //    // u64 *d=(*ustackp);
      //    // *(d)=(*urip);
      //    u64 **var = (u64 **)ustackp;
      //    *var = *var - 1;
      //    **var = *urip;
      //    *urip=signum;
      // }
      // else if(signo==1){
      //   // u32 temp=(current->pending_signal_bitmap & 0x1);
      //   // current->pending_signal_bitmap=(((current->pending_signal_bitmap >> 2) << 2) | temp);
      //   u64 **var = (u64 **)ustackp;
      //   *var = *var - 1;
      //   **var = *urip;
      //   // u64 *rsp=(*ustackp);
      //   // rsp-=1;
      //   // *ustackp=rsp;
      //   // // u64 *d=(*ustackp);
      //   // *(rsp)=(*urip);
      //
      //   *urip=signum;
      // }
      // else if(signo==2){
      //   // u32 temp=(current->pending_signal_bitmap & 0x3);
      //   // current->pending_signal_bitmap=(((current->pending_signal_bitmap >> 3) << 3) | temp);
      //   // u64 rsp=(*ustackp);
      //   // rsp-=8;
      //   // u64 *rsp=(*ustackp);
      //   // rsp-=1;
      //   // *ustackp=rsp;
      //   // u64 *d=(*ustackp);
      //   // *(d)=(*urip);
      //   u64 **var = (u64 **)ustackp;
      //   *var = *var - 1;
      //   **var = *urip;
      //   *urip=signum;
      // }
  }

  printf("Called signal with ustackp=%x urip=%x\n", *ustackp, *urip);
  /*Default behavior is exit( ) if sighandler is not registered for SIGFPE or SIGSEGV.
   Ignore for SIGALRM*/
   if(signo != SIGALRM && current->sighandlers[signo]==NULL){
     printf("Exiting\n");
     do_exit();
   }
}
/*system call handler for signal, to register a handler*/
long do_signal(int signo, unsigned long handler)
{
  // struct exec_context *current = get_current_ctx();
  // current->sighandlers[signo]=handler;
  // // printf("hi i am handler %x\n",handler);
  // return handler;
}

/*system call handler for alarm*/
long do_alarm(u32 ticks)
{
  // struct exec_context *current = get_current_ctx();
  // current->alarm_config_time=ticks;
  // current->ticks_to_alarm=ticks;
  // printf("hi i am alarm %d\n",ticks);
  // return (u64)ticks;
}