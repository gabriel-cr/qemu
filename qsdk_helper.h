#ifndef QSDK_HELPER_H
#define QSDK_HELPER_H

void * QSDK_alloc_memory_region(void);
void * get_qemu_sys_bus_device(void * device);
void * get_qemu_device(void * device);
void * init_memory_region_ops(void * readfunc, void * writefunc);
void load_elf_from_disk(char * kernel_filename, int mem_size, int endian);

#endif
