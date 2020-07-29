
/* AUTO-GENERATED by gen_isr_tables.py, do not edit! */

#include <toolchain.h>
#include <linker/sections.h>
#include <sw_isr_table.h>
#include <arch/cpu.h>

#if defined(CONFIG_GEN_SW_ISR_TABLE) && defined(CONFIG_GEN_IRQ_VECTOR_TABLE)
#define ISR_WRAPPER ((u32_t)&_isr_wrapper)
#else
#define ISR_WRAPPER NULL
#endif

u32_t __irq_vector_table _irq_vector_table[65] = {
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	130737,
	229629,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	229659,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
};
struct _isr_table_entry __sw_isr_table _sw_isr_table[65] = {
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)0x1a17d},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x20020534, (void *)0x37edb},
	{(void *)0x20020524, (void *)0x37edb},
	{(void *)0x2b42d, (void *)0x38a65},
	{(void *)0x2ae15, (void *)0x38a65},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)0x1a2f9},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x2b7b9, (void *)0x38a65},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)0x1f27d},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
	{(void *)0x0, (void *)&z_irq_spurious},
};
