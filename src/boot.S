.section ".text.boot"

.global _start

_start:
	// Check if this is the first core
	mrs x1, mpidr_el1
	and x1, x1, #3
	cbz x1, init // Jump to init if it is

halt:
	// Otherwise halt this core
	wfe
	b halt

init:
	// Set stack
	ldr x1, =_start
	mov sp, x1

	// Clear bss
	ldr x1, =__bss_start
	ldr w2, =__bss_size

clear:
	cbz w2, call
	str xzr, [x1], #8
	sub w2, w2, #1
	cbnz w2, clear

call:
	// Call C code
	bl main
	b halt // Halt
