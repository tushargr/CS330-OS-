#include<context.h>
#include<memory.h>
#include<lib.h>



void setzero(unsigned long * dummy){
	int i;
	for(i=0;i<512;i++){
		*dummy = 0;
		dummy+=1;
	}
	return;
}

void prepare_context_mm(struct exec_context *ctx)
{

	unsigned long virtual_addr_code = (ctx->mms[MM_SEG_CODE]).start;
	unsigned long virtual_addr_stack = ctx->mms[MM_SEG_STACK].end-4096;
	unsigned long virtual_addr_data = ctx->mms[MM_SEG_DATA].start;

	unsigned long flag_mask_code= 0x0000000000000000;
	unsigned long flag_mask_data= 0x0000000000000000;
	unsigned long flag_mask_stack=0x0000000000000000;

	if((ctx->mms[MM_SEG_CODE].access_flags & 0x02) == 0x02){
		flag_mask_code= 0x0000000000000002;
	}
	if((ctx->mms[MM_SEG_STACK].access_flags & 0x02) == 0x02){
		flag_mask_stack= 0x0000000000000002;
	}
	if((ctx->mms[MM_SEG_DATA].access_flags & 0x02) == 0x02){
		flag_mask_data= 0x0000000000000002;
	}

	unsigned long l4_mask = 0x0000FF8000000000;
	unsigned long l3_mask = 0x0000007FC0000000;
	unsigned long l2_mask = 0x000000003FE00000;
	unsigned long l1_mask = 0x00000000001FF000;


	unsigned int i;
	unsigned long * addr;
	unsigned long * dummy;
	unsigned int new_pfn;



	//code
	
	unsigned long pdindex4 = (l4_mask & virtual_addr_code ) >> 39;
	unsigned long pdindex3 = (l3_mask & virtual_addr_code ) >> 30;
	unsigned long pdindex2 = (l2_mask & virtual_addr_code ) >> 21;
	unsigned long pdindex1 = (l1_mask & virtual_addr_code ) >> 12;

	
	
	//level4
	ctx->pgd = os_pfn_alloc(OS_PT_REG);
	dummy = osmap(ctx->pgd);
	setzero(dummy);
	addr= osmap(ctx->pgd);
	addr += pdindex4;
	new_pfn = os_pfn_alloc(OS_PT_REG);
	dummy = osmap(new_pfn);
	setzero(dummy);
	*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
	*addr = ((*addr)| flag_mask_code);

	//level3
	addr= osmap(new_pfn);
	addr += pdindex3;
	new_pfn = os_pfn_alloc(OS_PT_REG);
	dummy = osmap(new_pfn);
	setzero(dummy);
	*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
	*addr = ((*addr)| flag_mask_code);

	//level2
	addr= osmap(new_pfn);
	addr += pdindex2;
	new_pfn = os_pfn_alloc(OS_PT_REG);
	dummy = osmap(new_pfn);
	setzero(dummy);
	*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
	*addr = ((*addr)| flag_mask_code);

	//level1
	addr= osmap(new_pfn);
	addr += pdindex1;
	new_pfn = os_pfn_alloc(USER_REG);
	dummy = osmap(new_pfn);
	setzero(dummy);
	*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
	*addr = ((*addr)| flag_mask_code);
	


	
	//stack

	pdindex4 = ((l4_mask & virtual_addr_stack ) >> 39);
	pdindex3 = (l3_mask & virtual_addr_stack ) >> 30;
	pdindex2 = (l2_mask & virtual_addr_stack ) >> 21;
	pdindex1 = (l1_mask & virtual_addr_stack ) >> 12;

	
	//level4
	addr= osmap(ctx->pgd);
	addr += pdindex4;
	if((*addr & 0x0000000000000001) == 0x0){
		new_pfn = os_pfn_alloc(OS_PT_REG);
		dummy = osmap(new_pfn);
		setzero(dummy);
		*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
		*addr = ((*addr)| flag_mask_stack);

		addr= osmap(new_pfn);
	}
	else{
		*addr = ((*addr)| flag_mask_stack);

		addr= osmap((unsigned int)(*addr >> 12));	
	}

	
	//level3


	addr += pdindex3;

	if((*addr & 0x0000000000000001) == 0x0){
		new_pfn = os_pfn_alloc(OS_PT_REG);
		dummy = osmap(new_pfn);
		setzero(dummy);
		*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
		*addr = ((*addr)| flag_mask_stack);

		addr= osmap(new_pfn);
	}
	else{
		*addr = ((*addr)| flag_mask_stack);

		addr= osmap((unsigned int)(*addr >> 12));	
	}

	//level2


	addr += pdindex2;


	if((*addr & 0x0000000000000001) == 0x0){
		new_pfn = os_pfn_alloc(OS_PT_REG);
		dummy = osmap(new_pfn);
		setzero(dummy);
		*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
		*addr = ((*addr)| flag_mask_stack);

		addr= osmap(new_pfn);
	}
	else{
		*addr = ((*addr)| flag_mask_stack);

		addr= osmap((unsigned int)(*addr >> 12));	
	}

	//level1

	addr += pdindex1;

	new_pfn = os_pfn_alloc(USER_REG);
	dummy = osmap(new_pfn);
	setzero(dummy);
	*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
	*addr = ((*addr)| flag_mask_stack);





	//data
	pdindex4 = (l4_mask & virtual_addr_data ) >> 39;
	pdindex3 = (l3_mask & virtual_addr_data ) >> 30;
	pdindex2 = (l2_mask & virtual_addr_data ) >> 21;
	pdindex1 = (l1_mask & virtual_addr_data ) >> 12;

	//level4
	addr= osmap(ctx->pgd);


	addr += pdindex4;


	if((*addr & 0x0000000000000001) == 0x0){
		new_pfn = os_pfn_alloc(OS_PT_REG);
		dummy = osmap(new_pfn);
		setzero(dummy);
		*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
		*addr = ((*addr)| flag_mask_data);

		addr= osmap(new_pfn);
	}
	else{
		*addr = ((*addr)| flag_mask_data);


		addr= osmap((unsigned int)(*addr >> 12));	
	}


	//level3
	addr += pdindex3;

	if((*addr & 0x0000000000000001) == 0x0){
		new_pfn = os_pfn_alloc(OS_PT_REG);
		dummy = osmap(new_pfn);
		setzero(dummy);
		*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
		*addr = ((*addr)| flag_mask_data);

		addr= osmap(new_pfn);
	}
	else{
		*addr = ((*addr)| flag_mask_data);

		addr= osmap((unsigned int)(*addr >> 12));	
	}
	

	//level2
	addr += pdindex2;
	if((*addr & 0x0000000000000001) == 0x0){
		new_pfn = os_pfn_alloc(OS_PT_REG);
		dummy = osmap(new_pfn);
		setzero(dummy);
		*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
		*addr = ((*addr)| flag_mask_data);
		addr= osmap(new_pfn);
	}
	else{
		*addr = ((*addr)| flag_mask_data);
		addr= osmap((unsigned int)(*addr >> 12));	
	}


	//level1
	addr += pdindex1;
	new_pfn = ctx->arg_pfn;
	*addr = ((((unsigned long)new_pfn) << 12) | 0x0000000000000005);
	*addr = ((*addr)| flag_mask_data);
	return;
}


void cleanup_context_mm(struct exec_context *ctx)
{	
	unsigned long virtual_addr_code = (ctx->mms[MM_SEG_CODE]).start;
	unsigned long virtual_addr_stack = ctx->mms[MM_SEG_STACK].end-4096;
	unsigned long virtual_addr_data = ctx->mms[MM_SEG_DATA].start;
	unsigned long l4_mask = 0x0000FF8000000000;
	unsigned long l3_mask = 0x0000007FC0000000;
	unsigned long l2_mask = 0x000000003FE00000;
	unsigned long l1_mask = 0x00000000001FF000;


	unsigned int i;
	unsigned long * addr;
	unsigned long * dummy;
	

	//code
	unsigned long c_pdindex4 = (l4_mask & virtual_addr_code ) >> 39;
	unsigned long c_pdindex3 = (l3_mask & virtual_addr_code ) >> 30;
	unsigned long c_pdindex2 = (l2_mask & virtual_addr_code ) >> 21;
	unsigned long c_pdindex1 = (l1_mask & virtual_addr_code ) >> 12;
	//stack

	unsigned long s_pdindex4 = ((l4_mask & virtual_addr_stack ) >> 39);
	unsigned long s_pdindex3 = (l3_mask & virtual_addr_stack ) >> 30;
	unsigned long s_pdindex2 = (l2_mask & virtual_addr_stack ) >> 21;
	unsigned long s_pdindex1 = (l1_mask & virtual_addr_stack ) >> 12;
	//data
	unsigned long d_pdindex4 = (l4_mask & virtual_addr_data ) >> 39;
	unsigned long d_pdindex3 = (l3_mask & virtual_addr_data ) >> 30;
	unsigned long d_pdindex2 = (l2_mask & virtual_addr_data ) >> 21;
	unsigned long d_pdindex1 = (l1_mask & virtual_addr_data ) >> 12;

	unsigned long new_pfn;

	//clean physical
	addr= osmap(ctx->pgd);
	addr += c_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += c_pdindex3;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += c_pdindex2;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += c_pdindex1;
	*addr= ((*addr >>1)<<1);
	new_pfn=((unsigned long)(*addr >> 12));
	os_pfn_free(USER_REG,new_pfn);

	addr= osmap(ctx->pgd);
	addr += s_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += s_pdindex3;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += s_pdindex2;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += s_pdindex1;
	*addr= ((*addr >>1)<<1);
	new_pfn=((unsigned long)(*addr >> 12));
	os_pfn_free(USER_REG,new_pfn);

	addr= osmap(ctx->pgd);
	addr += d_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += d_pdindex3;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += d_pdindex2;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += d_pdindex1;
	*addr= ((*addr >>1)<<1);
	new_pfn=((unsigned long)(*addr >> 12));
	os_pfn_free(USER_REG,new_pfn);
	
	// clean level1
	addr= osmap(ctx->pgd);
	addr += c_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += c_pdindex3;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += c_pdindex2;
	*addr= ((*addr >>1)<<1);
	new_pfn=((unsigned long)(*addr >> 12));
	os_pfn_free(OS_PT_REG,new_pfn);

	addr= osmap(ctx->pgd);
	addr += s_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += s_pdindex3;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += s_pdindex2;
	if((*addr & 0x01)==0x01){
		*addr= ((*addr >>1)<<1);
		new_pfn=((unsigned long)(*addr >> 12));
		os_pfn_free(OS_PT_REG,new_pfn);
	}

	addr= osmap(ctx->pgd);
	addr += d_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += d_pdindex3;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += d_pdindex2;
	if((*addr & 0x01)==0x01){
		*addr= ((*addr >>1)<<1);
		new_pfn=((unsigned long)(*addr >> 12));
		os_pfn_free(OS_PT_REG,new_pfn);
	}

	//clean level2
	addr= osmap(ctx->pgd);
	addr += c_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += c_pdindex3;
	*addr= ((*addr >>1)<<1);
	new_pfn=((unsigned long)(*addr >> 12));
	os_pfn_free(OS_PT_REG,new_pfn);

	addr= osmap(ctx->pgd);
	addr += s_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += s_pdindex3;
	if((*addr & 0x01)==0x01){
		*addr= ((*addr >>1)<<1);
		new_pfn=((unsigned long)(*addr >> 12));
		os_pfn_free(OS_PT_REG,new_pfn);
	}

	addr= osmap(ctx->pgd);
	addr += d_pdindex4;
	addr= osmap((unsigned int)(*addr >> 12));
	addr += d_pdindex3;
	if((*addr & 0x01)==0x01){
		*addr= ((*addr >>1)<<1);
		new_pfn=((unsigned long)(*addr >> 12));
		os_pfn_free(OS_PT_REG,new_pfn);
	}

	//clean level3
	addr= osmap(ctx->pgd);
	addr += c_pdindex4;
	*addr= ((*addr >>1)<<1);
	new_pfn=((unsigned long)(*addr >> 12));
	os_pfn_free(OS_PT_REG,new_pfn);

	addr= osmap(ctx->pgd);
	addr += s_pdindex4;
	if((*addr & 0x01)==0x01){
		*addr= ((*addr >>1)<<1);
		new_pfn=((unsigned long)(*addr >> 12));
		os_pfn_free(OS_PT_REG,new_pfn);
	}

	addr= osmap(ctx->pgd);
	addr += d_pdindex4;
	if((*addr & 0x01)==0x01){
		*addr= ((*addr >>1)<<1);
		new_pfn=((unsigned long)(*addr >> 12));
		os_pfn_free(OS_PT_REG,new_pfn);
	}

	//clean level4
	new_pfn=((unsigned long)ctx->pgd);	
	os_pfn_free(OS_PT_REG,new_pfn);
	

   return;
}
