#include<context.h>
#include<memory.h>
#include<schedule.h>
#include<apic.h>
#include<lib.h>
#include<idt.h>
static u64 numticks;
static u64 regs_location_for_do_exit;
static u64 to_free_pfn_for_do_exit;

static void save_current_context_user_regs(struct exec_context * current, u64 user_reg_location, u64 entry_reg_location, u64  urbp_location){
    u64 * t_entry_reg_location = entry_reg_location;u64 * t_urbp_location=urbp_location; u64 * t_user_reg_location=user_reg_location;
    current->regs.r15 = *(t_user_reg_location);
    current->regs.r14 = *(t_user_reg_location + 1);
    current->regs.r13 = *(t_user_reg_location + 2);
    current->regs.r12 = *(t_user_reg_location + 3);
    current->regs.r11 = *(t_user_reg_location + 4);
    current->regs.r10 = *(t_user_reg_location + 5);
    current->regs.r9 = *(t_user_reg_location + 6);
    current->regs.r8 = *(t_user_reg_location + 7);
    current->regs.rdi = *(t_user_reg_location + 8);
    current->regs.rsi = *(t_user_reg_location + 9);
    current->regs.rdx = *(t_user_reg_location + 10);
    current->regs.rcx = *(t_user_reg_location + 11);
    current->regs.rbx = *(t_user_reg_location + 12);
    current->regs.rax = *(t_user_reg_location + 13);
}

static void save_current_context_entry_regs(struct exec_context * current, u64 user_reg_location, u64 entry_reg_location, u64  urbp_location){
    u64 * t_entry_reg_location = entry_reg_location;u64 * t_urbp_location=urbp_location; u64 * t_user_reg_location=user_reg_location;
    current->regs.rbp = *(t_urbp_location);
    current->regs.entry_rip = *(t_entry_reg_location);
    current->regs.entry_cs = *(t_entry_reg_location+1);
    current->regs.entry_rflags = *(t_entry_reg_location+2);
    current->regs.entry_rsp = *(t_entry_reg_location+3);
    current->regs.entry_ss = *(t_entry_reg_location+4);
}

static void save_current_context(struct exec_context * current, u64 user_reg_location, u64 entry_reg_location, u64  urbp_location)
{
    save_current_context_user_regs(current,user_reg_location,entry_reg_location,urbp_location);
    save_current_context_entry_regs(current,user_reg_location,entry_reg_location,urbp_location);
} 

static void load_next_context_user_regs(struct exec_context * next, u64 user_reg_location, u64 entry_reg_location, u64  urbp_location){
    u64 * t_entry_reg_location = entry_reg_location;u64 * t_urbp_location=urbp_location; u64 * t_user_reg_location=user_reg_location;

  *(t_user_reg_location)= next->regs.r15;
  *(t_user_reg_location+1)=next->regs.r14;
  *(t_user_reg_location+2)=next->regs.r13;
  *(t_user_reg_location+3)=next->regs.r12;
  *(t_user_reg_location+4)=next->regs.r11;
  *(t_user_reg_location+5)=next->regs.r10;
  *(t_user_reg_location+6)=next->regs.r9;
  *(t_user_reg_location+7)=next->regs.r8;
  *(t_user_reg_location+8)=next->regs.rdi;
  *(t_user_reg_location+9)=next->regs.rsi;
  *(t_user_reg_location+10)=next->regs.rdx;
  *(t_user_reg_location+11)=next->regs.rcx;
  *(t_user_reg_location+12)=next->regs.rbx;
  *(t_user_reg_location+13)=next->regs.rax;
}

static void load_next_context_entry_regs(struct exec_context * next, u64 user_reg_location, u64 entry_reg_location, u64  urbp_location){
    u64 * t_entry_reg_location = entry_reg_location;u64 * t_urbp_location=urbp_location; u64 * t_user_reg_location=user_reg_location;
    *(t_urbp_location) = next->regs.rbp;
  *(t_entry_reg_location) = next->regs.entry_rip;
  *(t_entry_reg_location + 1) = next->regs.entry_cs;
  *(t_entry_reg_location + 2) = next->regs.entry_rflags;
  *(t_entry_reg_location + 3) = next->regs.entry_rsp;
  *(t_entry_reg_location + 4) = next->regs.entry_ss;
}

static void load_next_context(struct exec_context * next, u64 user_reg_location, u64 entry_reg_location, u64  urbp_location)
{
    load_next_context_user_regs(next,user_reg_location,entry_reg_location,urbp_location);
    load_next_context_entry_regs(next,user_reg_location,entry_reg_location,urbp_location);
}

void schedule_context(struct exec_context *next, u64  user_reg_location, u64  entry_reg_location, u64  urbp_location)
{
  /*Your code goes in here. get_current_ctx() still returns the old context*/
  struct exec_context *current = get_current_ctx();
  printf("schedluing: old pid = %d  new pid  = %d\n", current->pid, next->pid); /*XXX: Don't remove*/
  /*These two lines must be executed*/
  set_tss_stack_ptr(next);
  set_current_ctx(next);
  /*Your code for scheduling context*/
  save_current_context(current, user_reg_location, entry_reg_location, urbp_location);

  load_next_context(next, user_reg_location, entry_reg_location, urbp_location);
  u64 * t_entry_reg_location = entry_reg_location;u64 * t_urbp_location=urbp_location; u64 * t_user_reg_location=user_reg_location;

}

static struct exec_context * pick_next_context(struct exec_context *list, struct exec_context *current)
{
  int i;
  for(i = current->pid+1;i<16;i++) {
    struct exec_context * c = list+i;
    if(c==NULL) continue;
    if(c->state == READY){
      return c;
    }
  } 
  for(i=1;i<=current->pid;i++){
    struct exec_context * c = list+i;
    if(c==NULL) continue;
    if(c->state == READY){
      return c;
    }
  }
  return list;
}

static void schedule(u64 user_reg_location, u64 entry_reg_location, u64 urbp_location)
{
  struct exec_context *next;
  struct exec_context *current = get_current_ctx();
  struct exec_context *list = get_ctx_list();
  next = pick_next_context(list,current);
  next->state=RUNNING;
  schedule_context(next,user_reg_location, entry_reg_location, urbp_location);     
}

/*The five functions above are just a template. You may change the signatures as you wish*/
void handle_timer_tick()
{
  /*
      This is the timer interrupt handler. 
      You should account timer ticks for alarm and sleep
      and invoke schedule
  */ 
  u64 user_reg_location, entry_reg_location,urbp_location;
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
  asm volatile ("mov %%rsp, %0;":"=r"(user_reg_location));
  asm volatile ("mov %%rbp, %0;":"=r"(entry_reg_location));

  
  printf("Got a tick. #ticks = %u\n", numticks++);   /*XXX Do not modify this line*/ 
  urbp_location = entry_reg_location;
  entry_reg_location += 8;
  /*accounting alarm for init process*/
  
  struct exec_context * ctx= get_current_ctx();
  ctx->state=READY;
  struct exec_context * init_ctx = get_ctx_by_pid(1);
  if(init_ctx->alarm_config_time>0){
    init_ctx->ticks_to_alarm -=1;
    if(init_ctx->ticks_to_alarm == 0){
      init_ctx->pending_signal_bitmap |= (0x1 << 2);
      u64 * ustackp; u64 * urip;
      urip = entry_reg_location;
      ustackp = entry_reg_location;
      ustackp+=3;
      init_ctx->alarm_config_time=0;
      invoke_sync_signal(SIGALRM, ustackp, urip);
    }
  }
  struct exec_context *list = get_ctx_list();
  for(int i = 1;i<16;i++) {
   struct exec_context * c = list+i;
    if(c->ticks_to_sleep>0){
      c->ticks_to_sleep -=1;
      if(c->ticks_to_sleep == 0){
        c->state=READY;
      }
    } 
  } 

  schedule(user_reg_location,entry_reg_location,urbp_location);

  ack_irq();  /*acknowledge the interrupt, before calling iretq */
  asm volatile ("mov %0, %%rsp;"::"r"(user_reg_location));
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
  asm volatile("mov %%rbp, %%rsp;"
             "pop %%rbp;"
             "iretq;"
             :::"memory");
}

static void  load_regs_to_next_proc_stack(struct exec_context * next){
  u64 * next_os_stack_va = (osmap((u64)(next->os_stack_pfn))+4096);
  *(next_os_stack_va-1) = next->regs.entry_ss;
  *(next_os_stack_va-2) = next->regs.entry_rsp;
  *(next_os_stack_va-3) = next->regs.entry_rflags;
  *(next_os_stack_va-4) = next->regs.entry_cs;
  *(next_os_stack_va-5) = next->regs.entry_rip;
  *(next_os_stack_va-6) = next->regs.rbp;
  *(next_os_stack_va-7) =  next->regs.rax;
  *(next_os_stack_va-8) =  next->regs.rbx;
  *(next_os_stack_va-9) =  next->regs.rcx;
  *(next_os_stack_va-10) = next->regs.rdx;
  *(next_os_stack_va-11) = next->regs.rsi;
  *(next_os_stack_va-12) = next->regs.rdi;
  *(next_os_stack_va-13) = next->regs.r8;
  *(next_os_stack_va-14) = next->regs.r9;
  *(next_os_stack_va-15) = next->regs.r10;
  *(next_os_stack_va-16) = next->regs.r11;
  *(next_os_stack_va-17) = next->regs.r12;
  *(next_os_stack_va-18) = next->regs.r13;
  *(next_os_stack_va-19) = next->regs.r14;
  *(next_os_stack_va-20) = next->regs.r15;
  regs_location_for_do_exit = next_os_stack_va-20;
}

void do_exit()
{
  /*You may need to invoke the scheduler from here if there are
    other processes except swapper in the system. Make sure you make 
    the status of the current process to UNUSED before scheduling 
    the next process. If the only process alive in system is swapper, 
    invoke do_cleanup() to shutdown gem5 (by crashing it, huh!)
    */
    struct exec_context * ctx= get_current_ctx();
    ctx->state = UNUSED;

    struct exec_context *list = get_ctx_list();
    int i,flag=0;
  for(i = 1;i<16;i++) {
   struct exec_context * c = list+i;
   if(c==NULL) continue;
   if(c->state == READY || c->state == WAITING){
     flag=1;break;
   }
  }
  if(flag == 0){
    do_cleanup();  /*Call this conditionally, see comments above*/  
  }

   struct exec_context * next= pick_next_context(list,ctx);
   printf("schedluing: old pid = %d  new pid  = %d\n", ctx->pid, next->pid); /*XXX: Don't remove*/
  /*These two lines must be executed*/
  set_tss_stack_ptr(next);
  set_current_ctx(next);

  load_regs_to_next_proc_stack(next);
  u64 * next_os_stack_va = (osmap((u64)(next->os_stack_pfn))+4096);
  to_free_pfn_for_do_exit = ctx->os_stack_pfn;
  asm volatile ("mov %0, %%rsp;"::"r"(next_os_stack_va-20));
  asm volatile ("mov %0, %%rbp;"::"r"(next_os_stack_va));
  
  os_pfn_free(OS_PT_REG,(u64)to_free_pfn_for_do_exit);
  
  asm volatile ("mov %0, %%rsp;"::"r"(regs_location_for_do_exit));
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
  asm volatile("pop %%rbp;"
             "iretq;"
             :::"memory");
}

/*system call handler for sleep*/
long do_sleep(u32 ticks)
{
  struct exec_context * ctx= get_current_ctx();
  ctx->state=WAITING;
  ctx->ticks_to_sleep = ticks;
  u64 * os_stack_va = (osmap((u64)(ctx->os_stack_pfn))+4096);
  u64 user_reg_location, entry_reg_location,urbp_location;
  asm volatile ("push %0;"::"r"(*(os_stack_va - 6)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 7)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 8)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 9)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 10)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 12)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 13)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 14)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 15)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 16)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 17)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 18)));
  asm volatile ("push %0;"::"r"(*(os_stack_va - 19)));
  asm volatile ("mov %%rsp, %0;":"=r"(user_reg_location));
  asm volatile ("mov %0, 40(%%rbp);"::"r"(*(os_stack_va - 1)));
  asm volatile ("mov %0, 32(%%rbp);"::"r"(*(os_stack_va - 2)));
  asm volatile ("mov %0, 24(%%rbp);"::"r"(*(os_stack_va - 3)));
  asm volatile ("mov %0, 16(%%rbp);"::"r"(*(os_stack_va - 4)));
  asm volatile ("mov %0, 8(%%rbp);"::"r"(*(os_stack_va - 5)));
  asm volatile ("mov %0, 0(%%rbp);"::"r"(*(os_stack_va - 11)));
  asm volatile ("mov %%rbp, %0;":"=r"(entry_reg_location));
  urbp_location = entry_reg_location;
  entry_reg_location +=8;

  schedule(user_reg_location,entry_reg_location,urbp_location);

  asm volatile ("mov %0, %%rsp;"::"r"(user_reg_location));
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
  asm volatile("mov %%rbp, %%rsp;"
             "pop %%rbp;"
             "iretq;"
             :::"memory");
}

/*
  system call handler for clone, create thread like 
  execution contexts
*/
long do_clone(void *th_func, void *user_stack)
{
   struct exec_context * parent= get_current_ctx();
   struct exec_context * child= get_new_ctx();
   child->type=parent->type;
   child->used_mem= parent->used_mem;
   child->pgd=parent->pgd;
   child->os_stack_pfn = os_pfn_alloc(OS_PT_REG);
   child->os_rsp = osmap((u64)child->os_stack_pfn)+4096;
   child->mms[MM_SEG_CODE].start = parent->mms[MM_SEG_CODE].start;
   child->mms[MM_SEG_CODE].next_free = parent->mms[MM_SEG_CODE].next_free;
   child->mms[MM_SEG_CODE].end = parent->mms[MM_SEG_CODE].end;
   child->mms[MM_SEG_CODE].access_flags = parent->mms[MM_SEG_CODE].access_flags;
   child->mms[MM_SEG_DATA].start = parent->mms[MM_SEG_DATA].start;
   child->mms[MM_SEG_DATA].next_free = parent->mms[MM_SEG_DATA].next_free;
   child->mms[MM_SEG_DATA].end = parent->mms[MM_SEG_DATA].end;
   child->mms[MM_SEG_DATA].access_flags = parent->mms[MM_SEG_DATA].access_flags;
   child->mms[MM_SEG_RODATA].start = parent->mms[MM_SEG_RODATA].start;
   child->mms[MM_SEG_RODATA].next_free = parent->mms[MM_SEG_RODATA].next_free;
   child->mms[MM_SEG_RODATA].end = parent->mms[MM_SEG_RODATA].end;
   child->mms[MM_SEG_RODATA].access_flags = parent->mms[MM_SEG_RODATA].access_flags;
   child->mms[MM_SEG_STACK].start = parent->mms[MM_SEG_STACK].start;
   child->mms[MM_SEG_STACK].next_free = parent->mms[MM_SEG_STACK].next_free;
   child->mms[MM_SEG_STACK].end = parent->mms[MM_SEG_STACK].end;
   child->mms[MM_SEG_STACK].access_flags = parent->mms[MM_SEG_STACK].access_flags;

   /*name of the new child process*/
   int i=0;
   while(parent->name[i]!='\0'){
     child->name[i]=parent->name[i];
     i++;
   }
   char dummy[64];
   int j=-1;
   u32 child_pid = child->pid;
   while(child_pid!=0){
     j++;
     dummy[j]=48+(child_pid%10);
     child_pid/=10;
   }
   while(j>=0){
     child->name[i]=dummy[j];
     j--;i++;
   }

   child->regs.entry_rip = th_func;
   child->regs.entry_cs = 0X23;
   u64 * os_stack_va = (osmap((u64)(parent->os_stack_pfn))+4096);
   child->regs.entry_rflags = *(os_stack_va - 3);
   child->regs.entry_rsp = user_stack;
   child->regs.entry_ss = 0x2b;
   child->regs.rbp = user_stack;
   
   child->state = READY;
}

long invoke_sync_signal(int signo, u64 *ustackp, u64 *urip)
{ 
  /*If signal handler is registered, manipulate user stack and RIP to execute signal handler*/
  /*ustackp and urip are pointers to user RSP and user RIP in the exception/interrupt stack*/
  printf("Called signal with ustackp=%x urip=%x\n", *ustackp, *urip);
  struct exec_context * ctx= get_current_ctx();

  /*custom handler for SIGFPE and SIGSEGV*/
  if(ctx->sighandlers[signo]!=NULL && (signo==SIGFPE || signo==SIGSEGV|| signo==SIGALRM)){
    *ustackp = *ustackp - 8;
    u64 * ustack_pointer = *ustackp;
    *ustack_pointer = *urip;
    *urip = ctx->sighandlers[signo];
    ctx->pending_signal_bitmap &= ~(0x1 << signo);
  }

  /*Default behavior is exit( ) if sighandler is not registered for SIGFPE or SIGSEGV.
  Ignore for SIGALRM*/
    else if(signo != SIGALRM){
        do_exit();
    }
}

/*system call handler for signal, to register a handler*/
long do_signal(int signo, unsigned long handler)
{ 
  if(signo>=3 || signo<0){
    printf("signo not valid\n");
    do_exit();
  }
  struct exec_context * ctx= get_current_ctx();
  long prev_handler = ctx->sighandlers[signo];
  ctx->sighandlers[signo] = handler;
  return prev_handler;
}

/*system call handler for alarm*/
long do_alarm(u32 ticks)
{
    struct exec_context * ctx= get_current_ctx();
    u32 prev_ticks = ctx->ticks_to_alarm; 
    ctx->ticks_to_alarm = ticks;
    ctx->alarm_config_time = ticks;
    return prev_ticks;
}
