	.file	1 "bubble.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.module	arch=mips1
	.text
	.align	2
	.globl	bubbleSort
	.set	nomips16
	.set	nomicromips
	.ent	bubbleSort
	.type	bubbleSort, @function
bubbleSort:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	sw	$5,20($fp)
	sw	$0,0($fp)
	b	$L2
	nop

$L6:
	sw	$0,4($fp)
	b	$L3
	nop

$L5:
	lw	$2,4($fp)
	nop
	sll	$2,$2,2
	lw	$3,16($fp)
	nop
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,4($fp)
	nop
	addiu	$2,$2,1
	sll	$2,$2,2
	lw	$4,16($fp)
	nop
	addu	$2,$4,$2
	lw	$2,0($2)
	nop
	slt	$2,$2,$3
	beq	$2,$0,$L4
	nop

	lw	$2,4($fp)
	nop
	sll	$2,$2,2
	lw	$3,16($fp)
	nop
	addu	$2,$3,$2
	lw	$4,0($2)
	lw	$2,4($fp)
	nop
	addiu	$2,$2,1
	sll	$2,$2,2
	lw	$3,16($fp)
	nop
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,4($fp)
	nop
	sll	$2,$2,2
	lw	$5,16($fp)
	nop
	addu	$2,$5,$2
	xor	$3,$4,$3
	sw	$3,0($2)
	lw	$2,4($fp)
	nop
	addiu	$2,$2,1
	sll	$2,$2,2
	lw	$3,16($fp)
	nop
	addu	$2,$3,$2
	lw	$4,0($2)
	lw	$2,4($fp)
	nop
	sll	$2,$2,2
	lw	$3,16($fp)
	nop
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,4($fp)
	nop
	addiu	$2,$2,1
	sll	$2,$2,2
	lw	$5,16($fp)
	nop
	addu	$2,$5,$2
	xor	$3,$4,$3
	sw	$3,0($2)
	lw	$2,4($fp)
	nop
	sll	$2,$2,2
	lw	$3,16($fp)
	nop
	addu	$2,$3,$2
	lw	$4,0($2)
	lw	$2,4($fp)
	nop
	addiu	$2,$2,1
	sll	$2,$2,2
	lw	$3,16($fp)
	nop
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,4($fp)
	nop
	sll	$2,$2,2
	lw	$5,16($fp)
	nop
	addu	$2,$5,$2
	xor	$3,$4,$3
	sw	$3,0($2)
$L4:
	lw	$2,4($fp)
	nop
	addiu	$2,$2,1
	sw	$2,4($fp)
$L3:
	lw	$3,20($fp)
	lw	$2,0($fp)
	nop
	subu	$2,$3,$2
	addiu	$2,$2,-1
	lw	$3,4($fp)
	nop
	slt	$2,$3,$2
	bne	$2,$0,$L5
	nop

	lw	$2,0($fp)
	nop
	addiu	$2,$2,1
	sw	$2,0($fp)
$L2:
	lw	$2,20($fp)
	nop
	addiu	$2,$2,-1
	lw	$3,0($fp)
	nop
	slt	$2,$3,$2
	bne	$2,$0,$L6
	nop

	nop
	nop
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	bubbleSort
	.size	bubbleSort, .-bubbleSort
	.ident	"GCC: (GNU) 14.1.0"
