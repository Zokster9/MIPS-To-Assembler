.globl main

.data
m1:	.word 6
m2:	.word 5

.text
main:
	li	$t4, 8
	li	$t3, 3
	addi	$t4, $t3, 7
	la	$t0, m1
	lw	$t2, 0($t0)
	la	$t0, m2
	lw	$t1, 0($t0)
lab:
	sub	$t0, $t2, $t4
	add	$t2, $t3, $t1
	bltz	$t0, probica
	sub	$t0, $t0, $t2
nzm:
	sw	$t1, 0($t0)
	b	lab
probica:
	li	$t0, 9
	nop
