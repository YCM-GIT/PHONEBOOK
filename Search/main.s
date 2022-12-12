	.arch armv8-a
	.file	"main.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"data.csv"
	.align	3
.LC1:
	.string	"Usage Error"
	.align	3
.LC2:
	.string	"%d %d %s %s %s %d %d\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	w0, [sp, 28]
	str	x1, [sp, 16]
	ldr	w0, [sp, 28]
	cmp	w0, 1
	bgt	.L2
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	str	x0, [sp, 40]
	b	.L3
.L2:
	ldr	w0, [sp, 28]
	cmp	w0, 3
	ble	.L4
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	puts
	b	.L3
.L4:
	ldr	x0, [sp, 16]
	ldr	x0, [x0, 8]
	str	x0, [sp, 40]
.L3:
	ldr	x0, [sp, 40]
	bl	getData
	str	x0, [sp, 32]
	b	.L5
.L6:
	ldr	x0, [sp, 32]
	ldr	w1, [x0]
	ldr	x0, [sp, 32]
	ldr	w2, [x0, 4]
	ldr	x0, [sp, 32]
	add	x3, x0, 8
	ldr	x0, [sp, 32]
	add	x4, x0, 108
	ldr	x0, [sp, 32]
	add	x5, x0, 208
	ldr	x0, [sp, 32]
	ldr	w6, [x0, 308]
	ldr	x0, [sp, 32]
	ldr	w0, [x0, 312]
	mov	w7, w0
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	printf
	ldr	x0, [sp, 32]
	ldr	x0, [x0, 328]
	str	x0, [sp, 32]
.L5:
	ldr	x0, [sp, 32]
	cmp	x0, 0
	bne	.L6
	mov	w0, 0
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
