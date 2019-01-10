#include<init.h>
#include<lib.h>
#include<context.h>
#include<memory.h>

void setup(u64 VA,u32 pfn,int R_W)
{
  int valid_bit=5 + R_W*2 ;  //setting of valid bit // does flag=1 always 
  u64 ad= VA;
  u64* VA4=osmap(pfn);

  u64* L4_entry=0;
  L4_entry= VA4 + (ad>>39);
  u32 pfe_2=0;
  
  if((*L4_entry)&5)   //compare with  5 or 0
  {
    pfe_2=(*L4_entry)>>12;
  }
  else
  {
    *L4_entry=0x0;
    pfe_2=os_pfn_alloc(OS_PT_REG);
  
    *L4_entry+=pfe_2<<12;
    *L4_entry+= valid_bit;
  }
  u64* VA3=osmap(pfe_2);

  u64* L3_entry=0;
  L3_entry= VA3 + ((ad>>30)&((1<<9)-1));;
  
  u32 pfe_3;
  if(*L3_entry&5)   //compare with  5 or 0
  {
    pfe_3=(*L3_entry)>>12;
  }
  else
  {
      *L3_entry=0x0;
       pfe_3=os_pfn_alloc(OS_PT_REG);

      *L3_entry+=pfe_3<<12;
      *L3_entry+= valid_bit;
  }

  u64* VA2=osmap(pfe_3);

  u64* L2_entry=0;
  L2_entry= VA2 + ((ad>>21)&((1<<9)-1));

  u32 pfe_4;

  if(*L2_entry&5)   //compare with  5 or 0
  {
    pfe_4=(*L2_entry)>>12;
  }
  else{

      *L2_entry=0x0;
      pfe_4=os_pfn_alloc(OS_PT_REG);

      *L2_entry+=pfe_4<<12;
      *L2_entry+= valid_bit;
  
  }
  
  u64* VA1=osmap(pfe_4);

  u64* L1_entry=0;
  L1_entry= VA1 + ((ad>>12)&((1<<9)-1));

  u32 data=0;
  if(*L1_entry&5)   //compare with  5 or 0
  {
    data=(*L1_entry)>>12;
  }

else{
  
  *L1_entry=0x0;

   data=os_pfn_alloc (USER_REG);

  *L1_entry+=data<<12; // or use arg_pfn
  *L1_entry+= valid_bit;
 }

 return;
  
}

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
                               u64 buff= param1;
                               char* string= (char*) param1;
                               u64 length= param2;

                               if(length>1024)
                                   return -1; 

                               // if((buff>>0)&((1<<12)-1)+length>4095)
                               //      u64 buff2= buff+length;
                               // else
                               //      u64* buff2= buff;

                                //check for validity of the addresses

                                u32 pfn=current->pgd;
                                u64* adress= osmap(pfn);

                                // //long long* adress=osmap(pfe_1);
                                // printf("The page frame number 1 is :");
                                // printf("%x \n ",pfn);
                      
                                long long* L4_entry=(adress + (buff>>39));
                                int pfe_2=*L4_entry>>12;
                                    

                                     
                                   // printf("The page frame number 2 is :");
                                   // printf("%x \n ",pfe_2);
                                   
                   
                                long long* va_3=osmap((*L4_entry)>>12);
                             
                                long long* L3_entry=0x0;
                                    // long long* L3_entry_data=0x0;

                                    
                                    // long long* L2_entry_stack=0x0;
                                long long* L2_entry=0x0;

                                long long* L1_entry_buff=0x0;
                                long long* L1_entry_buff2=0x0;
                                // long long* L1_entry_stack=0x0;
                                    // long long* L1_entry_data=0x0;

                                    //if(flag==0)
                                    
                                      

                                      
                                L3_entry =   va_3 + ((buff>>30)&((1<<9)-1));
                                // L3_entry_data  =   va_3 + ((data_start>>30)&((1<<9)-1));

                                      


                                      
                                int pfe_3=*L3_entry>>12;
                                  
                                
                                // int pfe_32=*L3_entry_data>>12;
                              

                             //  printf("The page frame number 3 are :");
                             // printf("%x \n %x \n ",pfe_31,pfe_32);
                             

                                long long* va_2=osmap((*L3_entry)>>12);
                                  // long long* va_22=osmap((*L3_entry_data)>>12);

                                  
                                L2_entry =   va_2 + ((buff>>21)&((1<<9)-1));
                                // L2_entry_data  =   va_22 + ((data_start>>21)&((1<<9)-1));
                                      
                                int pfe_4=*L2_entry>>12;
                                      
                                // int pfe_42=*L2_entry_data>>12;
                                 
                                // printf("The page frame number 4 are :");
                                //    printf("%x \n %x \n ",pfe_41,pfe_42);



                                long long* va_1=osmap((*L2_entry)>>12);
                                // long long* va_12=osmap((*L2_entry)>>12);

                                L1_entry_buff  =   va_1 + ((buff>>12)&((1<<9)-1));
                                L1_entry_buff2 =   L1_entry_buff+1;

                                if(((*L1_entry_buff)&5)&&((*L1_entry_buff2)&5))   //orr compare with 1????
                                          
                                {
                                
                                    for(int i=0;i<length;i++)
                                        {
                                          printf("%c",*(string+i));

                                        } //run for loop for printing

                                      return length; 
                                      }

                                 else 
                                   return -1; 
                                  

                                     /*Your code goes here*/
                             }
          case SYSCALL_EXPAND:
                             { 
                                
                                u32 size=param1;
                                if(size>512)
                                  return -1;

                                u64 start;
                                u64 end;
                                u64 next_free;
                                u32 flags;

                                if(param2==MAP_RD)
                                  {
                                     start=current->mms[MM_SEG_RODATA].start;
                                     end=current->mms[MM_SEG_RODATA].end;
                                     next_free=current->mms[MM_SEG_RODATA].next_free;
                                     flags=current->mms[MM_SEG_RODATA].access_flags;

                                  } 

                                else if(param2==MAP_WR)
                                {

                                     start=current->mms[MM_SEG_DATA].start;
                                     end=current->mms[MM_SEG_DATA].end;
                                     next_free=current->mms[MM_SEG_DATA].next_free;
                                     flags=current->mms[MM_SEG_DATA].access_flags;

                                }


                                if((next_free>>12)+size<=(end>>12))
                                    {
                                      if(param2==MAP_WR)
                                        current->mms[MM_SEG_DATA].next_free=((next_free>>12)+size)<<12;
                                      else 
                                        current->mms[MM_SEG_RODATA].next_free=((next_free>>12)+size)<<12;
                                        
                                        return next_free;    //check with the return type
                                          

                                    }
                                 
                                 else
                                  return -1; 

 



                                     /*Your code goes here*/
                             }
          case SYSCALL_SHRINK:
                             {  


                              int pfn=current->pgd;
                              u64* adress=osmap(pfn);

                            
                              int size=param1;


                              if(size>512)
                                return -1;


                              u64 start;
                              u64 end;
                              u64 next_free;
                              u32 flags;

                              if(param2==MAP_RD)
                                  {
                                     start=current->mms[MM_SEG_RODATA].start;
                                     end=current->mms[MM_SEG_RODATA].end;
                                     next_free=current->mms[MM_SEG_RODATA].next_free;
                                     flags=current->mms[MM_SEG_RODATA].access_flags;

                                  } 

                              else if(param2==MAP_WR) 
                                {

                                     start=current->mms[MM_SEG_DATA].start;
                                     end=current->mms[MM_SEG_DATA].end;
                                     next_free=current->mms[MM_SEG_DATA].next_free;
                                     flags=current->mms[MM_SEG_DATA].access_flags;

                                }

                              if((next_free>>12)-size>=(start>>12))    //start ko cross nahi krna chaiye
                                    {
                                      u64 ad=0;
                                      u64* L4_entry=0;
                                      u64* L3_entry=0;
                                      u64* L2_entry=0;
                                      u64* L1_entry=0;
                                      u64* va_3=0;
                                      u64* va_2=0;
                                      u64* va_1=0;
                                      int pfe_2=0;
                                      int pfe_3=0;
                                      int pfe_4=0;
                                      int data_page=0;


                                      while(size--)
                                      {

                                       ad=((next_free>>12) -1)<<12;

                                       L4_entry=(adress + (ad>>39));
                                       pfe_2=*L4_entry>>12;
                             
                                       va_3=(u64*)osmap(pfe_2);
                                       
                                       L3_entry =   va_3 + ((ad>>30)&((1<<9)-1));
                                      
                                       pfe_3=*L3_entry>>12;
                                      
                                       va_2=(u64 *)osmap(pfe_3);
                                        
                                       L2_entry =   va_2 + ((ad>>21)&((1<<9)-1));
                                      
                                       pfe_4=*L2_entry>>12;
                                    
                                       va_1=(u64 *)osmap(pfe_4);
                                        // long long* va_12=osmap((*L2_entry)>>12);

                                       L1_entry  =   va_1 + ((ad>>12)&((1<<9)-1));
                                        

                                       if((*L1_entry)&1)
                                       {
                                        *L1_entry=*L1_entry-1;
                                        data_page=(*L1_entry)>>12;
                                        os_pfn_free(USER_REG,data_page);
                                       } 

                                       next_free=ad;


                                      }


                                      if(param2==MAP_WR)
                                          current->mms[MM_SEG_DATA].next_free=next_free;

                                      else
                                          current->mms[MM_SEG_RODATA].next_free=next_free;

                                      return next_free;


                                    }

                                 else
                                 return -1; 





                                     /*Your code goes here*/
                             }
                             
          default:
                              return -1;
                                
    }
    return 0;   /*GCC shut up!*/
}

extern int handle_div_by_zero(void)
{

  u64 rip;

  asm volatile ( "mov 8(%%rbp), %0;":"=r"(rip)::);
  printf("Div-by zero detected at %x",rip);

  do_exit();





    /*Your code goes in here*/
    //printf("Div-by-zero handler: unimplemented!\n");
    return 0;
}

extern int handle_page_fault(void)
{
  

  struct exec_context *current = get_current_ctx();
  u32 pfn= current->pgd;

  u64 address;
  u32 error_code;
  u64 rip;
  u64 rsp;
  u64 rbp;
  // asm volatile("mov %%cr2 ,%0;"
  //               "mov 8(%%rbp),%1;" 
  //               "mov 16(%%rbp) %2;"
  //               :"=r"(address),"=r"(error_code),"=r"(rip)::);

   asm volatile ("push %r8;"
                 "push %r9;"
                 "push %r10;"
                 "push %r11;"
                 "push %r12;"
                 "push %r13;"
                 "push %r14;"
                 "push %r15;");
  
  asm volatile ("push %rdi;");
  asm volatile ("push %rcx;");
  asm volatile ("push %rax;");
  asm volatile ("push %rsi;");
  asm volatile ("push %rdx;");
 
  asm volatile ("mov 16(%%rbp), %0;":"=r"(rip));
  asm volatile ("mov 8(%%rbp), %0;":"=r"(error_code));
  asm volatile ("mov %%cr2, %0;":"=r"(address));
  asm volatile ("mov %%rsp, %0;":"=r"(rsp));
  asm volatile ("mov %%rbp, %0;":"=r"(rbp));



  printf("page fault address: %x \n ",address);
  printf("error code: %x \n ",error_code);

  u64 start_data     = current->mms[MM_SEG_DATA].start;
  u64 next_free_data = current->mms[MM_SEG_DATA].next_free;

  // printf(" access flags %x \n:",current->mms[MM_SEG_DATA].access_flags);
  // printf(" access flags %x \n:",current->mms[MM_SEG_RODATA].access_flags);
  // printf(" access flags %x \n :",current->mms[MM_SEG_STACK].access_flags);
  

  u64 start_rodata     = current->mms[MM_SEG_RODATA].start;
  u64 next_free_rodata = current->mms[MM_SEG_RODATA].next_free;


  u64 end_stack       = current->mms[MM_SEG_STACK].end-1;
  u64 next_free_stack = current->mms[MM_SEG_STACK].next_free;




  // u64 start=ctx->mms[MM_SEG_DATA]

  // printf("start and next_free VAs for data %x  and  %x \n",current->mms[MM_SEG_DATA].start,current->mms[MM_SEG_DATA].next_free);
  // printf("start and next_free VAs for RO data %x  and  %x \n",current->mms[MM_SEG_RODATA].start,current->mms[MM_SEG_RODATA].next_free);
  // printf("start and next_free VAs for stack %x  and  %x \n",current->mms[MM_SEG_STACK].end-1,current->mms[MM_SEG_STACK].next_free);
    if((start_data<=address) && (address<=next_free_data))
    {

      if(!(error_code&1))
      {
        printf(" Handled \n");
        //int flag=error_code&(1<<2);
        //setup(address,pfn,1);

        printf(" Entered Page table setup for data region \n");

            int valid_bit=7 ;  //setting of valid bit // does flag=1 always 
            u64 ad= address;
            u64* VA4=osmap(pfn);

            u64* L4_entry=0;
            L4_entry= VA4 + (ad>>39);
            u32 pfe_2=0;
            
            if((*L4_entry)&5)   //compare with  5 or 0
            {
              printf("Entered L4 \n");
              pfe_2=(*L4_entry)>>12;
            }
            else
            {
              *L4_entry=0x0;
              pfe_2=os_pfn_alloc(OS_PT_REG);
            
              *L4_entry+=pfe_2<<12;
              *L4_entry+= valid_bit;
            }
            u64* VA3=osmap(pfe_2);

            u64* L3_entry=0;
            L3_entry= VA3 + ((ad>>30)&((1<<9)-1));;
            
            u32 pfe_3;
            if(*L3_entry&5)   //compare with  5 or 0
            {
              printf("Entered L3 \n");
              pfe_3=(*L3_entry)>>12;
            }
            else
            {
                *L3_entry=0x0;
                 pfe_3=os_pfn_alloc(OS_PT_REG);

                *L3_entry+=pfe_3<<12;
                *L3_entry+= valid_bit;
            }

            u64* VA2=osmap(pfe_3);

            u64* L2_entry=0;
            L2_entry= VA2 + ((ad>>21)&((1<<9)-1));

            u32 pfe_4;

            if(*L2_entry&5)   //compare with  5 or 0
            {
              printf("Entered L2 \n");
              pfe_4=(*L2_entry)>>12;
            }
            else{

                *L2_entry=0x0;
                pfe_4=os_pfn_alloc(OS_PT_REG);

                *L2_entry+=pfe_4<<12;
                *L2_entry+= valid_bit;
            
            }
            
            u64* VA1=osmap(pfe_4);

            u64* L1_entry=0;
            L1_entry= VA1 + ((ad>>12)&((1<<9)-1));

            // u32 data=0;

            // if(*L1_entry&5)   //compare with  5 or 0
            // {
            //   printf("Entered L1 \n");
            //   data=(*L1_entry)>>12;
            // }

         
            *L1_entry=0x0;

            u32 data=os_pfn_alloc (USER_REG);

            *L1_entry+=data<<12; // or use arg_pfn
            *L1_entry+= valid_bit;
          
           printf("DONE setupping \n");
        
      }




      else 
      {
        printf("Not Handled \n");
        do_exit();
        //protection fault
      }


      // bit 2 tells waht to set in bit u/s in ptes
      // bit 1 doesnt have any impact on this section
      // bit 0 tells whether it is a protection or missing page table fault;

       // printf("found in data");

    }


    else if((start_rodata<=address) && (address<=next_free_rodata))
    {
      if(!(error_code&1))
      {


          if(!(error_code&(1<<1)))
          {
            printf("Handled \n");
            setup(address,pfn,0);
            printf("Page table setup for RO_DATA region \n");
            //get the user/supervisor bit
            //setup page table
          }

          else
          {
            printf("Not Handled \n");


            printf("access not allowed \n");
            printf("Accessed virtual address is %x \n ",address);
            printf("Error code is %x \n ",error_code);
            printf("RIP is %x \n ",rip);
            do_exit();

            //write access not allowed
          }
      }
      else 
      {
        printf("Not Handled \n");
        do_exit();
        //protection fault
      }


      // bit 2 tells waht to set in bit u/s in ptes
      // bit 1 doesnt with read only other wise cant return error
      // bit 0 tells whether it is a protection or missing page table fault;

        
      // printf("found in rodata");        

    }

    else if((end_stack>=address) && (address>=next_free_stack)  )

 {
        if(!(error_code&1))
          {
            printf("Handled \n");

            setup(address,pfn,1);
            printf("Page table setup for Stack region \n");
            //get the user/supervisor bit
            //setup page table
          }
        else 
            {
              printf("Not Handled \n");

              do_exit();


                //protection fault
            }


              // bit 2 tells waht to set in bit u/s in ptes
              // bit 1 doesnt have any impact on this section
              // bit 0 tells whether it is a protection or missing page table fault;

               

              // printf("found in Stack");
 }

 else
    {

            printf("Not Handled \n");
            printf("Accessed virtual address is %x \n ",address);
            printf("Error code is %x \n ",error_code);
            printf("RIP is %x \n ",rip);
            do_exit();


    }

    printf("Reached HERE \n");






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

  
  

    /*Your code goes in here*/
    // printf("page fault handler: implemented!\n");
    // return ;
}