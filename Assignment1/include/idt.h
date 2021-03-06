#ifndef __IDT_H_
#define __IDT_H_

#include <types.h>

#pragma pack(1)


#define IDT_DESC_TYPE_UTRAP    0xEF
#define IDT_DESC_TYPE_KTRAP    0x8F
#define IDT_DESC_TYPE_INT_SW   0xEE
#define IDT_DESC_TYPE_INT_HW   0x8E
#define NUM_IDT_ENTRY 256

#define SYSCALL_IDT 0x80

struct idt_entry{
                               u16 offset_low;
                               u16 segment;
                               u8 zero;   /*includes IST, we are not using it*/
                               u8 flags_type;
                               u16 offset_mid;
                               u32 offset_high;
                               u32 unused;
};

struct IDTR{
               u16 limit;
               u64 base;
};

struct gdt_entry{
                    u16 limit_low;
                    u16 base_low;
                    u8  base_mid;
                    u8  ac_byte;
                    u8 limit_high:4,
                       flags:4;
                    u8  base_high;     
}; 

struct tss{
             u32 reserved;
             u32 rsp0_low;
             u32 rsp0_high;
             char unused[0];
};

extern void setup_idt();        
extern void setup_gdt_tss(struct IDTR *);
extern void set_tss_stack_ptr();
#endif
