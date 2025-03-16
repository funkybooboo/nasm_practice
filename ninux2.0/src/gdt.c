#include "gdt.h"

extern void gdt_flush(addr_t);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;

void initGdt() {
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 5) - 1;
    gdt_ptr.base = &gdt_entries;

    setGdtGate(0, 0, 0, 0, 0); // Null segment
    setGdtGate(1, 0, 0xffffffff, 0x9a, 0xcf); // Kernel code segment
    setGdtGate(2, 0, 0xffffffff, 0x92, 0xcf); // Kernel data segment
    setGdtGate(3, 0, 0xffffffff, 0xfa, 0xcf); // User code segment
    setGdtGate(4, 0, 0xffffffff, 0xf2, 0xcf); // User data segment

    gdt_flush(&gdt_ptr);
}

void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low = (base & 0xffff);
    gdt_entries[num].base_middle = (base >> 16) & 0xff;
    gdt_entries[num].base_high = (base >> 24) & 0xff;

    gdt_entries[num].limit = (limit & 0xffff);
    gdt_entries[num].flags = (limit >> 16) & 0x0f;
    gdt_entries[num].flags |= (gran & 0xf0);

    gdt_entries[num].access = access;
}
