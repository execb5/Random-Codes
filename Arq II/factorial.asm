#int fact (int n)
#{
#	if (n<1) return 1;
#		else return (n * fact(n - 1));
#}

		.text
		.globl main
main:	la		$a0, N
		lw		$a0, 0($a0)
		jal		fact
		la		$t0, FACTO
		sw		$v0, 0($t0)
		lw		$ra, 4($sp)
		jr		$ra
	

fact:	addi	$sp, $sp, -8
		sw		$ra, 4($sp)
		sw		$a0, 0($sp)
	
		slti	$t0, $a0, 1
		beq		$t0, $zero, L1
		
		addi	$v0, $zero, 1
		addi	$sp, $sp, 8
		jr		$ra
	
L1:		addi	$a0, $a0, -1
		jal		fact
		
		lw		$a0, 0($sp)
		lw		$ra, 4($sp)
		addi	$sp, $sp, 8
		
		mul		$v0, $a0, $v0
		
		jr		$ra
	
		.data
N:		.word	0x05
FACTO:	.word	0x00