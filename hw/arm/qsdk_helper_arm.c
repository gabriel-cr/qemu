#include "hw/arm/arm.h"
void set_nvic(void * nvic, void * cpu);

void set_nvic(void * nvic, void * cpu)
{
    ARMCPU * pcpu = (ARMCPU*)cpu;
    pcpu->env.nvic = nvic;
}
