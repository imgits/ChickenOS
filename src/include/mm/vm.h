#ifndef C_OS_MM_VM_H
#define C_OS_MM_VM_H
#include <stdint.h>
#include <stddef.h>
#include <multiboot.h>

#define PAGE_SIZE 4096
#define PAGE_MASK 0xFFFFF000

#define PD_SIZE   4096

#define PAGE_VIOLATION 0x01
#define PAGE_WRITE	   0x02
#define PAGE_USER	   0x04

//#define PTE_PRESENT 0x00000001

#define KERNEL_SEG 0x10

typedef uintptr_t phys_addr_t;
typedef uintptr_t virt_addr_t;

#define PHYS_BASE 0xC0000000
#define V2P(p) ((virt_addr_t)((phys_addr_t)p - PHYS_BASE))
#define P2V(p) ((phys_addr_t)((virt_addr_t)p + PHYS_BASE))

/* mm/vm.c */
void vm_init(struct multiboot_info *mb);

/* mm.gdt.c */
void gdt_install();

/* mm/palloc.c */
void palloc_init(uint32_t page_count, uint32_t placement);
void *pallocn(uint32_t count);
void *palloc();
void palloc_free(void *addr);
int  pallocn_free(void *addr, int pages);
#endif
