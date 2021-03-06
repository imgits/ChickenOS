#ifndef C_OS_ARCH_ARM_COMMON_H
#define C_OS_ARCH_ARM_COMMON_H

#define stackpointer_get(x)  asm volatile ("mov sp, %0": "=r"(x) )
 
static inline void kernel_halt()
{
	while(1)
		;
		//asm volatile ("hlt");
}
static inline void print_user_trace (uint32_t *ebp)
{
   /*   uint32_t *eip;
      asm volatile ("mov %%ebp, %0" : "=r" (ebp)); // Start with the current EBP value.
      while (ebp)
      {
        eip = ebp+1;
        printf ("[0x%x], ", *eip);
        ebp = (uint32_t*) *ebp;	
	//	if((uintptr_t)ebp < 0xC0000000)
		//	break;
      }*/

	(void)ebp;
}

static inline void print_stack_trace ()
{/*
      uint32_t *ebp, *eip;
      asm volatile ("mov %%ebp, %0" : "=r" (ebp)); // Start with the current EBP value.
      while (ebp)
      {
        eip = ebp+1;
        printf ("[0x%x], ", *eip);
        ebp = (uint32_t*) *ebp;	
	//	if((uintptr_t)ebp < 0xC0000000)
		//	break;
      }*/
}


#endif
