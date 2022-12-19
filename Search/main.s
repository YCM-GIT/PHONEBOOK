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
	.align	3
.LC3:
	.string	"\nSearched data"
	.align	3
.LC4:
	.string	"ID\tIndex\tName\tNumber\t\tGroup"
	.align	3
.LC5:
	.string	"No matched date"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	mov	x29, sp
	str	w0, [sp, 28]
	str	x1, [sp, 16]
	str	xzr, [sp, 40]
	str	xzr, [sp, 48]
	str	xzr, [sp, 32]
	ldr	w0, [sp, 28]
	cmp	w0, 1
	bgt	.L2
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	str	x0, [sp, 56]
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
	str	x0, [sp, 56]
.L3:
	ldr	x0, [sp, 56]
	bl	getData
	str	x0, [sp, 40]
	ldr	x0, [sp, 40]
	str	x0, [sp, 48]
	b	.L5
.L6:
	ldr	x0, [sp, 48]
	ldr	w1, [x0]
	ldr	x0, [sp, 48]
	ldr	w2, [x0, 4]
	ldr	x0, [sp, 48]
	add	x3, x0, 8
	ldr	x0, [sp, 48]
	add	x4, x0, 108
	ldr	x0, [sp, 48]
	add	x5, x0, 208
	ldr	x0, [sp, 48]
	ldr	w6, [x0, 308]
	ldr	x0, [sp, 48]
	ldr	w0, [x0, 312]
	mov	w7, w0
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	printf
	ldr	x0, [sp, 48]
	ldr	x0, [x0, 328]
	str	x0, [sp, 48]
.L5:
	ldr	x0, [sp, 48]
	cmp	x0, 0
	bne	.L6
	ldr	x0, [sp, 40]
	bl	searchDisplay
	sxtw	x0, w0
	str	x0, [sp, 48]
	ldr	x0, [sp, 32]
	cmp	x0, 0
	beq	.L7
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	bl	puts
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	puts
	b	.L8
.L7:
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	puts
.L8:
	mov	w0, 0
	ldp	x29, x30, [sp], 64
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
