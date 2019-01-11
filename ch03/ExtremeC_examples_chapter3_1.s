	.arch armv5t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"ExtremeC_examples_chapter3_1.c"
	.global	__aeabi_i2d
	.global	__aeabi_dadd
	.global	__aeabi_ddiv
	.text
	.align	2
	.global	avg
	.syntax unified
	.arm
	.type	avg, %function
avg:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #36
	str	r0, [fp, #-32]
	str	r1, [fp, #-36]
	str	r2, [fp, #-40]
	ldr	r3, [fp, #-36]
	cmp	r3, #0
	ble	.L2
	ldr	r3, [fp, #-40]
	cmp	r3, #0
	bne	.L3
.L2:
	mov	r3, #0
	mov	r4, #0
	b	.L4
.L3:
	mov	r3, #0
	mov	r4, #0
	str	r3, [fp, #-20]
	str	r4, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-24]
	b	.L5
.L8:
	ldr	r3, [fp, #-40]
	cmp	r3, #1
	bne	.L6
	ldr	r3, [fp, #-24]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-32]
	add	r3, r2, r3
	ldr	r3, [r3]
	mov	r0, r3
	bl	__aeabi_i2d
	mov	r3, r0
	mov	r4, r1
	mov	r2, r3
	mov	r3, r4
	sub	r1, fp, #20
	ldmia	r1, {r0-r1}
	bl	__aeabi_dadd
	mov	r3, r0
	mov	r4, r1
	str	r3, [fp, #-20]
	str	r4, [fp, #-16]
	b	.L7
.L6:
	ldr	r3, [fp, #-40]
	cmp	r3, #2
	bne	.L7
	ldr	r3, [fp, #-24]
	lsl	r3, r3, #2
	ldr	r2, [fp, #-32]
	add	r3, r2, r3
	ldr	r3, [r3]
	ldr	r2, [fp, #-24]
	lsl	r2, r2, #2
	ldr	r1, [fp, #-32]
	add	r2, r1, r2
	ldr	r2, [r2]
	mul	r3, r2, r3
	mov	r0, r3
	bl	__aeabi_i2d
	mov	r3, r0
	mov	r4, r1
	mov	r2, r3
	mov	r3, r4
	sub	r1, fp, #20
	ldmia	r1, {r0-r1}
	bl	__aeabi_dadd
	mov	r3, r0
	mov	r4, r1
	str	r3, [fp, #-20]
	str	r4, [fp, #-16]
.L7:
	ldr	r3, [fp, #-24]
	add	r3, r3, #1
	str	r3, [fp, #-24]
.L5:
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-36]
	cmp	r2, r3
	blt	.L8
	ldr	r0, [fp, #-36]
	bl	__aeabi_i2d
	mov	r3, r0
	mov	r4, r1
	mov	r2, r3
	mov	r3, r4
	sub	r1, fp, #20
	ldmia	r1, {r0-r1}
	bl	__aeabi_ddiv
	mov	r3, r0
	mov	r4, r1
.L4:
	mov	r0, r3
	mov	r1, r4
	sub	sp, fp, #8
	@ sp needed
	pop	{r4, fp, pc}
	.size	avg, .-avg
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits
