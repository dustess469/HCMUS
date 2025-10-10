
.data
	strA: .asciiz "Enter A: "
	strB: .asciiz "Enter B: "
	strADD: .asciiz "\nA + B = "
	strSUB: .asciiz "\nA - B = "
	strMUL: .asciiz "\nA * B = "
	strDIV: .asciiz "\nA / B = "
	strMOD: .asciiz "\nA % B = "
.text
main:

	
	li $v0, 4
	la $a0, strA
	syscall
	
	
	li $v0, 5
	syscall
	
	
	move $s0, $v0 
	
	li $v0, 4
	la $a0, strB
	syscall
	
	
	li $v0,5
	syscall 
	
	
	move $s1, $v0 
	
	add $s2,$s0,$s1 
	
	li $v0, 4
	la $a0, strADD
	syscall
	
	
	li $v0, 1
	move $a0, $s2
	syscall
	
	
	sub $s3, $s0, $s1 

	li $v0, 4
	la $a0, strSUB
	syscall
	
	
	li $v0,1
	move $a0, $s3
	syscall
	
	
	mult $s0, $s1 
	mflo $t1

	li $v0, 4
	la $a0, strMUL
	syscall
	

	li $v0, 1
	move $a0, $t1
	syscall

	li $v0, 4
	la $a0, strDIV
	syscall
	

	div $s5, $s0, $s1 
	mflo $t2
	add $a0, $0, $t2
	add $v0, $0, 1
	syscall
	
	
	li $v0, 4
	la $a0, strMOD
	syscall
	

	mfhi $t2
	add $a0, $0, $t2
	add $v0, $0, 1
	syscall