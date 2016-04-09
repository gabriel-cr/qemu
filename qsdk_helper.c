#include "hw/sysbus.h"
#include "hw/hw.h"
#include "hw/boards.h"
#include "hw/loader.h"
#include <stdio.h>
#include <elf.h>
#include "qemu/error-report.h"
#include "qsdk_helper.h"

extern void launch_board(const char * board_name, const char * kernel);
extern void lib_qsdk_init(void*);
void register_qsdk_board(const char * name);

void * QSDK_alloc_memory_region(void)
{
    MemoryRegion * new_mr = g_new(MemoryRegion, 1);
    return new_mr;
}

void * get_qemu_sys_bus_device(void * device)
{
    return SYS_BUS_DEVICE(device);
}

void * get_qemu_device(void * device)
{
    return DEVICE(device);
}

void * init_memory_region_ops(void * readfunc, void * writefunc)
{
    MemoryRegionOps * ops = calloc(1, sizeof(MemoryRegionOps));
    ops->write = writefunc;
    ops->read = readfunc;

    return ops;
}

void load_elf_from_disk(char * kernel_filename, int mem_size, int endian)
{
    int image_size;
    uint64_t entry;
    uint64_t lowaddr;
    int big_endian = endian;

    if (kernel_filename) {
        image_size = load_elf(kernel_filename, NULL, NULL, &entry, &lowaddr,
                              NULL, big_endian, EM_ARM, 1);
        if (image_size < 0) {
            image_size = load_image_targphys(kernel_filename, 0, mem_size);
            lowaddr = 0;
        }
        if (image_size < 0) {
            error_report("Could not load kernel '%s'", kernel_filename);
            exit(1);
        }
    }
}

static void qsdk_init(MachineState *machine)
{
    const char * machine_name = object_class_get_name(OBJECT_CLASS(machine->parent_obj.class));

    /* Removing '-machine' */
    int mname_len = strlen(machine_name) - strlen(TYPE_MACHINE_SUFFIX);
    char * original_name = calloc(1, mname_len);

    memcpy(original_name, machine_name, mname_len);

    launch_board(original_name, machine->kernel_filename);

    free(original_name);
}

static void qsdk_class_init(ObjectClass *oc, void *data)
{
    MachineClass *mc = MACHINE_CLASS(oc);

    mc->desc = (char*)data;
    mc->init = qsdk_init;
    mc->desc = "QSDK dynamic machine";
}

void register_qsdk_board(const char * name)
{
    TypeInfo * new_mach = calloc(1, sizeof(TypeInfo));

    char * new_name = calloc(1, strlen(name) + strlen(TYPE_MACHINE_SUFFIX));
    sprintf(new_name, "%s%s", name, TYPE_MACHINE_SUFFIX);

    new_mach->name = new_name;
    new_mach->class_init = qsdk_class_init;
    new_mach->parent = TYPE_MACHINE;
    new_mach->class_data = strdup(name);

    type_register_static(new_mach);
}

static void qsdk_machine_init(void)
{
    lib_qsdk_init(NULL);
}

machine_init(qsdk_machine_init)
