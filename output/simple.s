.globl main

.data
m1:	.word 6
m2:	.word 5

.text
main:
	lw	$t0, m1
	la	$t1, 0($t0)
	lw	$t0, m2
	la	$t0, 0($t0)
	add	$t0, $t1, $t0
