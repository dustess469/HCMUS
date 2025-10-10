.data

	arr: .space 1000
	strArr: .asciiz "Input array size: "
	strEle1: .asciiz "a["
	strEle2: .asciiz "] = "
	strN: .asciiz "\n"
	strOut: .asciiz ">> Output array: "
	strS: .asciiz "  "
	strError: .asciiz "INVALID ARRAY! TRY AGAIN\n\n"


.text

addi $s0, $zero, 4

#INPUT ARRAY
whileArr:
	#print strArr
	li $v0, 4
	la $a0, strArr
	syscall
	
	#input array
	li $v0 ,5
	syscall

	
	move $s0, $v0
	sle $t6, $s0, $zero
	beq $t6, 0, exitArr
	
	beq $t6, 1, exitEr
	
	exitEr:
		li $v0, 4
		la $a0, strError
		syscall
		
	
	j whileArr


exitArr:
	move $t2, $s0
	mul $t2, $t2, 4




#INPUT ELEMENT OF ARRAY
# $t0 is index
addi $t0, $zero, 0


whileEle:
	beq $t0, $t2, exitEle
	
	#print strEle1
	li $v0, 4
	la $a0, strEle1
	syscall
	
	div $t6, $t0, 4
	li $v0, 1
	move $a0, $t6
	syscall
	
	#print strEle2
	li $v0, 4
	la $a0, strEle2
	syscall
	
	#input a[i]
	li $v0, 5
	syscall
	
	move $t5, $v0
	sw $t5, arr($t0)
	
	
	addi $t0, $t0, 4
	
	j whileEle



exitEle:
	li $v0, 4
	la $a0, strOut
	syscall



#OUTPUT ARRAY
# $t0 is index
addi $t0, $zero, 0


whileOut:
	beq $t0, $t2, exitOut
	
	lw $t6, arr($t0)
	
	li $v0, 1
	move $a0, $t6
	syscall
	
	#print strS
	li $v0, 4
	la $a0, strS
	syscall
	
	
	addi $t0, $t0, 4
	
	
	j whileOut
	
	
	
exitOut:
	li $v0, 4
	syscall