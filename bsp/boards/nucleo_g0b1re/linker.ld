ENTRY(Reset_Handler)

MEMORY
{
	FLASH (rx)	:	ORIGIN = 0X08000000, LENGTH = 512K
	RAM (rwx)	:	ORIGIN = 0X20000000, LENGTH = 144K
}

_estack = ORIGIN(RAM) + LENGTH(RAM); 

__max_heap_size = 0x400;
__max_stack_size = 0x200;

SECTIONS
{
	.text :
	{
		*(.isr_vector)
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_etext = .;
	} > FLASH

	.data :
	{
		_sdata = .;
		*(.data)
		. = ALIGN(4);
		_edata = .;
	} > RAM AT> FLASH

	.bss :
	{
		_sbss = .;
		*(.bss)
		_ebss = .;
	} > RAM
	
}
