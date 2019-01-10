#include<init.h>
#include<lib.h>
#include<context.h>
#include<memory.h>


/*System Call handler*/
long do_syscall(int syscall, u64 param1, u64 param2, u64 param3, u64 param4)
{
    struct exec_context *current = get_current_ctx();
    printf("[GemOS] System call invoked. syscall no  = %d\n", syscall);
    switch(syscall)
    {
          case SYSCALL_EXIT:
                              printf("[GemOS] exit code = %d\n", (int) param1);
                              do_exit();
                              break;
          case SYSCALL_GETPID:
                              printf("[GemOS] getpid called for process %s, with pid = %d\n", current->name, current->id);
                              return current->id;      
          case SYSCALL_WRITE:
                             {    
                                int length = param2;
                                if(param2>1024 || param2<0){
                                  return -1;
                                }
                                //validation of virtual address
                                u64 l4_mask = 0x0000FF8000000000;
                  u64 l3_mask = 0x0000007FC0000000;
                  u64 l2_mask = 0x000000003FE00000;
                  u64 l1_mask = 0x00000000001FF000;
                  u64 * addr;
                  u64 pdindex4,pdindex3,pdindex2,pdindex1;
                                u64 virtual_addr;
                                for(int i=0;i<length;i++){
                                  virtual_addr = param1+i;
                                  pdindex4 = (l4_mask & virtual_addr ) >> 39;
                    pdindex2 = (l2_mask & virtual_addr ) >> 21;
                    pdindex1 = (l1_mask & virtual_addr ) >> 12;
                    pdindex3 = (l3_mask & virtual_addr ) >> 30;
                    addr= osmap(current->pgd);
                    addr += pdindex4;
                    if((*addr & 0x05) != 0x05){return -1;}
                    addr= osmap((u32)(*addr >> 12));
                    addr += pdindex3;
                    if((*addr & 0x05) != 0x05){return -1;}
                    addr= osmap((u32)(*addr >> 12));
                    addr += pdindex2;
                    if((*addr & 0x05) != 0x05){return -1;}
                    addr= osmap((u32)(*addr >> 12));
                    addr += pdindex1;
                    if((*addr & 0x05) != 0x05){return -1;}
                    
                                }

                                char * buffer = param1;
                                for (int i = 0; i < length; ++i){
                              printf("%c",*(buffer+i));
                            }
                            return param2;
                      
                             }
          case SYSCALL_EXPAND:
                             {    if(param1>512 || param1<0){
                                  return NULL;
                                }
                                u64 returnval;
                                if(param2 == MAP_RD){
                                  returnval = current->mms[MM_SEG_RODATA].next_free;
                                  if((returnval+param1*4096-1)>current->mms[MM_SEG_RODATA].end) 
                                    return NULL;
                                  
                                  current->mms[MM_SEG_RODATA].next_free += param1*4096;
                                }
                                else if(param2 ==MAP_WR){
                                  returnval = current->mms[MM_SEG_DATA].next_free;
                                  if((returnval+param1*4096-1)>current->mms[MM_SEG_DATA].end) 
                                    return NULL;
                                  
                                  current->mms[MM_SEG_DATA].next_free += param1*4096; 
                                }
                                return returnval;
                             }
          case SYSCALL_SHRINK:
                             {    u64 old_next_free,returnval;
                                u64 l4_mask = 0x0000FF8000000000;
                  u64 l3_mask = 0x0000007FC0000000;
                  u64 l2_mask = 0x000000003FE00000;
                  u64 l1_mask = 0x00000000001FF000;
                  u64 * addr;
                  u64 pdindex4,pdindex3,pdindex2,pdindex1;
                  if(param2 == MAP_RD){
                                  old_next_free = current->mms[MM_SEG_RODATA].next_free;
                                  if((old_next_free-param1*4096)<current->mms[MM_SEG_RODATA].start) 
                                    return NULL;
                                  
                                  current->mms[MM_SEG_RODATA].next_free -= param1*4096;
                                  for(u64 virtual_addr = (current->mms[MM_SEG_RODATA].next_free);virtual_addr<old_next_free;virtual_addr+=4096){

                                    pdindex4 = (l4_mask & virtual_addr ) >> 39;
                      pdindex2 = (l2_mask & virtual_addr ) >> 21;
                      pdindex1 = (l1_mask & virtual_addr ) >> 12;
                      pdindex3 = (l3_mask & virtual_addr ) >> 30;
                      addr= osmap(current->pgd);
                      addr += pdindex4;
                      if((*addr & 0x1)==0x0){
                        continue;
                      }
                      addr= osmap((u32)(*addr >> 12));
                      addr += pdindex3;
                      if((*addr & 0x1)==0x0){
                        continue;
                      }
                      addr= osmap((u32)(*addr >> 12));
                      addr += pdindex2;
                      if((*addr & 0x1)==0x0){
                        continue;
                      }
                      addr= osmap((u32)(*addr >> 12));
                      addr += pdindex1;
                      u64 new_pfn=((u64)(*addr >> 12));
                      if((*addr & 0x1)==0x1){
                        os_pfn_free(USER_REG,new_pfn);
                      } 
                      *addr = 0;
                      asm volatile("invlpg (%0);"::"r"(virtual_addr):"memory");
                                  }

                                  returnval = current->mms[MM_SEG_RODATA].next_free;

                                }
                                else if(param2 ==MAP_WR){
                                  old_next_free = current->mms[MM_SEG_DATA].next_free;
                                  if((old_next_free-param1*4096)<current->mms[MM_SEG_DATA].start) 
                                    return NULL;
                                  
                                  current->mms[MM_SEG_DATA].next_free -= param1*4096;
                                  for(u64 virtual_addr = (current->mms[MM_SEG_DATA].next_free);virtual_addr<old_next_free;virtual_addr+=4096){
                                    pdindex4 = (l4_mask & virtual_addr ) >> 39;
                      pdindex2 = (l2_mask & virtual_addr ) >> 21;
                      pdindex1 = (l1_mask & virtual_addr ) >> 12;
                      pdindex3 = (l3_mask & virtual_addr ) >> 30;
                      addr= osmap(current->pgd);
                      addr += pdindex4;
                      if((*addr & 0x1)==0x0){
                        continue;
                      }
                      addr= osmap((u32)(*addr >> 12));
                      addr += pdindex3;
                      if((*addr & 0x1)==0x0){
                        continue;
                      }
                      addr= osmap((u32)(*addr >> 12));
                      addr += pdindex2;
                      if((*addr & 0x1)==0x0){
                        continue;
                      }
                      addr= osmap((u32)(*addr >> 12));
                      addr += pdindex1;
                      if((*addr & 0x1)==0x1){
                        u64 new_pfn=((u64)(*addr >> 12));
                        os_pfn_free(USER_REG,new_pfn);
                      }
                      *addr = (*addr & 0x0);
                      asm volatile("invlpg (%0);"::"r"(virtual_addr):"memory");
                                  } 

                                  returnval = current->mms[MM_SEG_DATA].next_free;
                      
                                  
                                } 
                                return returnval; 
                             }
                             
          default:
                              return -1;
                                
    }
    return 0;   /*GCC shut up!*/
}



extern int handle_div_by_zero(void)
{
    u64 rip;
    asm volatile ( "mov 8(%%rbp), %0;"
                :"=r" (rip)::);
    printf("Div-by-zero detected at RIP=%x\n",rip);
    do_exit();
    return 0;
}

extern int handle_page_fault(void)
{ 
  u64 rip,cr2,errorcode,faulting_rip,oldrbp,rsp,pbp;

  asm volatile ("push %r8;");
  asm volatile ("push %r9;");
  asm volatile ("push %r10;");
  asm volatile ("push %r11;");
  asm volatile ("push %r12;");
  asm volatile ("push %r13;");
  asm volatile ("push %r14;");
  asm volatile ("push %r15;");
  asm volatile ("push %rdi;");
  asm volatile ("push %rcx;");
  asm volatile ("push %rax;");
  asm volatile ("push %rsi;");
  asm volatile ("push %rdx;");
  asm volatile ("mov %%rsp, %0;":"=r"(rsp));
  asm volatile ("mov %%cr2, %0;":"=r"(cr2));
  asm volatile ("mov %%rbp, %0;":"=r"(pbp));
  asm volatile ("mov 16(%%rbp), %0;":"=r"(rip));
  asm volatile ("mov 8(%%rbp), %0;":"=r"(errorcode));
  

  u64 * rbp;
  struct exec_context * ctx;
  u64 l4_mask = 0x0000FF8000000000;
  u64 l3_mask = 0x0000007FC0000000;
  u64 l2_mask = 0x000000003FE00000;
  u64 l1_mask = 0x00000000001FF000;
  u64 * addr;
  u32 new_pfn;
  u64 pdindex4,pdindex3,pdindex2,pdindex1;
  printf("Page Fault Handler: invoked\n");

    ctx = get_current_ctx();

    if(cr2>=ctx->mms[MM_SEG_RODATA].start  && cr2<=ctx->mms[MM_SEG_RODATA].end){
      if((cr2>=ctx->mms[MM_SEG_RODATA].start  && cr2<ctx->mms[MM_SEG_RODATA].next_free) && ((errorcode & 0x2) == 0x0)){
        pdindex4 = (l4_mask & cr2 ) >> 39;
      pdindex2 = (l2_mask & cr2 ) >> 21;
      pdindex1 = (l1_mask & cr2 ) >> 12;
      pdindex3 = (l3_mask & cr2 ) >> 30;
      addr= osmap(ctx->pgd);
      addr += pdindex4;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x05);
        addr= osmap(new_pfn);
      }
      else{
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex3;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x05);
        addr= osmap(new_pfn);
      }
      else {
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex2;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x05);
        addr= osmap(new_pfn);
      }
      else{
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex1;
      new_pfn=os_pfn_alloc(USER_REG);
      *addr = ((((u64)(new_pfn)) << 12) | 0x5);
      }
      else{
        printf("Error code= %x , RIP= %x , PageFaultVA=%x\n",errorcode,rip,cr2);
        do_exit();
      return 0;
      }
    }

    else if(cr2>=ctx->mms[MM_SEG_DATA].start  && cr2<=ctx->mms[MM_SEG_DATA].end){
      if(cr2>=ctx->mms[MM_SEG_DATA].start  && cr2<ctx->mms[MM_SEG_DATA].next_free){
        printf("%x %x %x %x\n",ctx->mms[MM_SEG_DATA].start,cr2,ctx->mms[MM_SEG_DATA].next_free, ctx->mms[MM_SEG_DATA].end);
        pdindex4 = (l4_mask & cr2 ) >> 39;
      pdindex2 = (l2_mask & cr2 ) >> 21;
      pdindex1 = (l1_mask & cr2 ) >> 12;
      pdindex3 = (l3_mask & cr2 ) >> 30;
      addr= osmap(ctx->pgd);
      addr += pdindex4;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x07);
        addr= osmap(new_pfn);
      }
      else{
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex3;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x07);
        addr= osmap(new_pfn);
      }
      else {
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex2;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x07);
        addr= osmap(new_pfn);
      }
      else{
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex1;
      new_pfn=os_pfn_alloc(USER_REG);
      *addr = ((((u64)(new_pfn)) << 12) | 0x7);
      }
      else{
        printf("Error code= %x , RIP= %x , PageFaultVA=%x\n",errorcode,rip,cr2);
        do_exit();
      return 0;
      }
    }

    else if(cr2>=ctx->mms[MM_SEG_STACK].start  && cr2<=ctx->mms[MM_SEG_STACK].end){
        pdindex4 = (l4_mask & cr2 ) >> 39;
      pdindex2 = (l2_mask & cr2 ) >> 21;
      pdindex1 = (l1_mask & cr2 ) >> 12;
      pdindex3 = (l3_mask & cr2 ) >> 30;
      addr= osmap(ctx->pgd);
      addr += pdindex4;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x07);
        addr= osmap(new_pfn);
      }
      else{
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex3;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x07);
        addr= osmap(new_pfn);
      }
      else {
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex2;
      if((*addr & 0x1) == 0x0){
        new_pfn = os_pfn_alloc(OS_PT_REG);
        *addr = ((((u64)new_pfn) << 12) | 0x07);
        addr= osmap(new_pfn);
      }
      else{
        addr= osmap((u32)(*addr >> 12));  
      }
      addr += pdindex1;
      new_pfn=os_pfn_alloc(USER_REG);
      *addr = ((((u64)(new_pfn)) << 12) | 0x7);
    }

    else{
      printf("Error code= %x , RIP= %x , PageFaultVA=%x\n",errorcode,rip,cr2);
      do_exit();
      return 0;
    }
    asm volatile ("mov %0, %%rsp;"::"r"(rsp));
  asm volatile ("pop %rdx;");
  asm volatile ("pop %rsi;");
  asm volatile ("pop %rax;");
  asm volatile ("pop %rcx;");
  asm volatile ("pop %rdi;");
  asm volatile ("pop %r15;");
  asm volatile ("pop %r14;");
  asm volatile ("pop %r13;");
  asm volatile ("pop %r12;");
  asm volatile ("pop %r11;");
  asm volatile ("pop %r10;");
  asm volatile ("pop %r9;");
  asm volatile ("pop %r8;");
  asm volatile ("mov %rbp, %rsp;");
  asm volatile ("pop %rbp;");
  asm volatile ("add $8, %rsp;");
  asm volatile ("iretq;");
    return 0;
}
