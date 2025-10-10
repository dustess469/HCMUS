.data
inputArray: .asciiz "Input size array: "
inputElement: .asciiz "Input elements in array: "
output: .asciiz "Sum of odd elements in array: "


int_array: .word 0:100



.text
main:

# Input size array
la $a0, inputArray
li $v0, 4
syscall


# Move to registers $t0
li $v0, 5
syscall
move $t0, $v0


# Input elements in array
la $a0, inputElement
li $v0, 4
syscall


xor $t1, $t1, $t1
la $t2, int_array

loop_input:
	li $v0, 5
	syscall

sw $v0, ($t2)
addi $t1, $t1, 1
addi $t2, $t2, 4
blt $t1, $t0, loop_input


# Sum of odd elements in array
xor $t1, $t1, $t1
la $t2, int_array
li $t4, 0
li $t5, 2

loop_sum:
	lw $t3, ($t2)
	div $t3, $t5
	mfhi $t6
	beqz $t6, end_if
	add $t4, $t4, $t3

end_if:
	addi $t1, $t1, 1
	addi $t2, $t2, 4

blt $t1, $t0, loop_sum
la $a0, output
li $v0,4
syscall

move $a0, $t4
li $v0, 1
syscall

li $v0, 10
syscall
