# SPIM S20 MIPS simulator.
# The default exception handler for spim.
#
# Copyright (C) 1990-2004 James Larus, larus@cs.wisc.edu.
# ALL RIGHTS RESERVED.
#
# SPIM is distributed under the following conditions:
#
# You may make copies of SPIM for your own use and modify those copies.
#
# All copies of SPIM must retain my name and copyright notice.
#
# You may not sell SPIM or distributed SPIM in conjunction with a commerical
# product or service without the expressed written consent of James Larus.
#
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE.
#

# $Header: $


# Define the exception handling code.  This must go first!

	.kdata
__m1_:	.asciiz "  Exception "
__m2_:	.asciiz " occurred and ignored\n"
__e0_:	.asciiz "  [Interrupt] "
__e1_:	.asciiz	"  [TLB]"
__e2_:	.asciiz	"  [TLB]"
__e3_:	.asciiz	"  [TLB]"
__e4_:	.asciiz	"  [Address error in inst/data fetch] "
__e5_:	.asciiz	"  [Address error in store] "
__e6_:	.asciiz	"  [Bad instruction address] "
__e7_:	.asciiz	"  [Bad data address] "
__e8_:	.asciiz	"  [Error in syscall] "
__e9_:	.asciiz	"  [Breakpoint] "
__e10_:	.asciiz	"  [Reserved instruction] "
__e11_:	.asciiz	""
__e12_:	.asciiz	"  [Arithmetic overflow] "
__e13_:	.asciiz	"  [Trap] "
__e14_:	.asciiz	""
__e15_:	.asciiz	"  [Floating point] "
__e16_:	.asciiz	""
__e17_:	.asciiz	""
__e18_:	.asciiz	"  [Coproc 2]"
__e19_:	.asciiz	""
__e20_:	.asciiz	""
__e21_:	.asciiz	""
__e22_:	.asciiz	"  [MDMX]"
__e23_:	.asciiz	"  [Watch]"
__e24_:	.asciiz	"  [Machine check]"
__e25_:	.asciiz	""
__e26_:	.asciiz	""
__e27_:	.asciiz	""
__e28_:	.asciiz	""
__e29_:	.asciiz	""
__e30_:	.asciiz	"  [Cache]"
__e31_:	.asciiz	""
__excp:	.word __e0_, __e1_, __e2_, __e3_, __e4_, __e5_, __e6_, __e7_, __e8_, __e9_
	.word __e10_, __e11_, __e12_, __e13_, __e14_, __e15_, __e16_, __e17_, __e18_,
	.word __e19_, __e20_, __e21_, __e22_, __e23_, __e24_, __e25_, __e26_, __e27_,
	.word __e28_, __e29_, __e30_, __e31_
s1:	.word 0
s2:	.word 0

# This is the exception handler code that the processor runs when
# an exception occurs. It only prints some information about the
# exception, but can server as a model of how to write a handler.
#
# Because we are running in the kernel, we can use $k0/$k1 without
# saving their old values.

# This is the exception vector address for MIPS-1 (R2000):
#	.ktext 0x80000080
# This is the exception vector address for MIPS32:
	.ktext 0x80000180
# Select the appropriate one for the mode in which SPIM is compiled.
	.set noat
	move $k1 $at		# Save $at
	.set at
	sw $v0 s1		# Not re-entrant and we can't trust $sp
	sw $a0 s2		# But we need to use these registers

	mfc0 $k0 $13		# Cause register
	srl $a0 $k0 2		# Extract ExcCode Field
	andi $a0 $a0 0x1f

	# Print information about exception.
	#
	li $v0 4		# syscall 4 (print_str)
	la $a0 __m1_
	syscall

	li $v0 1		# syscall 1 (print_int)
	srl $a0 $k0 2		# Extract ExcCode Field
	andi $a0 $a0 0x1f
	syscall

	li $v0 4		# syscall 4 (print_str)
	andi $a0 $k0 0x3c
	lw $a0 __excp($a0)
	nop
	syscall

	bne $k0 0x18 ok_pc	# Bad PC exception requires special checks
	nop

	mfc0 $a0 $14		# EPC
	andi $a0 $a0 0x3	# Is EPC word-aligned?
	beq $a0 0 ok_pc
	nop

	li $v0 10		# Exit on really bad PC
	syscall

ok_pc:
	li $v0 4		# syscall 4 (print_str)
	la $a0 __m2_
	syscall

	srl $a0 $k0 2		# Extract ExcCode Field
	andi $a0 $a0 0x1f
	bne $a0 0 ret		# 0 means exception was an interrupt
	nop

# Interrupt-specific code goes here!
# Don't skip instruction at EPC since it has not executed.


ret:
# Return from (non-interrupt) exception. Skip offending instruction
# at EPC to avoid infinite loop.
#
	mfc0 $k0 $14		# Bump EPC register
	addiu $k0 $k0 4		# Skip faulting instruction
				# (Need to handle delayed branch case here)
	mtc0 $k0 $14


# Restore registers and reset procesor state
#
	lw $v0 s1		# Restore other registers
	lw $a0 s2

	.set noat
	move $at $k1		# Restore $at
	.set at

	mtc0 $0 $13		# Clear Cause register

	mfc0 $k0 $12		# Set Status register
	ori  $k0 0x1		# Interrupts enabled
	mtc0 $k0 $12

# Return from exception on MIPS32:
	eret

# Return sequence for MIPS-I (R2000):
#	rfe			# Return from exception handler
				# Should be in jr's delay slot
#	jr $k0
#	 nop



# Standard startup code.  Invoke the routine "main" with arguments:
#	main(argc, argv, envp)
#
	.text
	.globl __start
__start:
	lw $a0 0($sp)		# argc
	addiu $a1 $sp 4		# argv
	addiu $a2 $a1 4		# envp
	sll $v0 $a0 2
	addu $a2 $a2 $v0
	jal main
	nop

	li $v0 10
	syscall			# syscall 10 (exit)


	#  From here down is the standard library which is linked into all
	#  programs. It contains the assembly for the built-in library
	#  functions (Print, Read, Alloc)
	#  Where possible built-ins are frameless (don't set up fp, etc.)
	#  Each expects args to be in $sp + 4, +8, etc.
	#  Return value (if any) assigned to v0
	#  May trash a0-a3 registers, uses no others


	#  Library function ptr = Alloc(int size)
	#  -----------------------------------------
	#  Used for New and NewArray.
	#  Allocates space in heap and returns address in $v0
	.globl _Alloc
_Alloc:
	  
        lw $a0, 4($sp)        # get number of bytes
        li $v0, 9             # 9 is code for srbk sys call
        syscall
        beqz $v0, _AFail
        jr $ra
    _AFail:
        .data
        _memErrStr:  .asciiz "Allocate failed: out of memory"
        .text
        la $a0, _memErrStr    # print error message
        li $v0, 4	
        syscall
        li $v0, 10            # 10 is code for exit syscall
        syscall

	  
	#  Library function PrintInt(int n)
	#  --------------------------------
	#  Prints number given as argument to console
	.globl _PrintInt
  _PrintInt:
        lw $a0, 4($sp)        # syscall expects arg in a0
        li $v0, 1             # 1 is code for print int syscall
        syscall
        jr $ra

	#  Library function PrintBool(bool b)
	#  ----------------------------------
	#  Prints true/false value given to console
	.globl _PrintBool
  _PrintBool:
        .data
        _trueStr:  .asciiz "true" # string constants for true/false
        _falseStr: .asciiz "false"
        .text
        lw $a0, 4($sp)
        li $v0, 4                # 4 is print string syscall
        beqz $a0 _PBFalse
        la $a0, _trueStr
        syscall
        jr $ra
    _PBFalse:
        la $a0, _falseStr
        syscall
        jr $ra

	#  Library function PrintString(address str)
	#  -----------------------------------------
	#  Prints string located at the address to console
	.globl _PrintString
  _PrintString:
        lw $a0, 4($sp)        # syscall expects arg in a0
        li $v0, 4             # 4 is code for print string syscall
        syscall
        jr $ra

	#  Library function n = ReadInteger()
	#  ----------------------------------
	#  Reads a number from the console and returns it in $v0
	.globl _ReadInteger
  _ReadInteger:
        li $v0, 5             # 5 is code for read int syscall
        syscall
        jr $ra

	#  Library function s = ReadLine()
	#  -------------------------------
	#  Reads a line from the console into heap-allocated buffer and
	#  returns its address in $v0
	.globl _ReadLine
  _ReadLine:
        li $a0, 64       # allocate space, fixed size 64
        li $v0, 9        # make sbrk syscall
        syscall
        move $a0, $v0    # copy return value from sbrk as 1st arg
        li $a1, 64       # push size of buffer
        li $v0, 8        # read_string syscall
        syscall
        move $v0, $a0    # put result in v0
                         # now go find \n and terminate over it
    _RLLoopTop:
        lb $a1, ($a0)           # use a1 to hold next char
        beqz $a1, _RLLoopDone  # halt if find null terminator
        addi $a1, $a1, -10      # subtract ASCII newline
        beqz $a1, _RLLoopDone  # halt if find newline
        addi $a0, $a0, 1        # advance by one
        j _RLLoopTop
   _RLLoopDone:
        sb $a1, ($a0)           # store 0 over newline
        jr $ra

	  
	#  Library function if (StringEqual(addr s, addr t)) ... 
	#  ----------------------------------------------------
	#  Compares two strings for equality (case-sensitive)
	#  returns true/false in $v0
	.globl _StringEqual
 _StringEqual:
        lw $a0, 4($sp)
        lw $a2, 8($sp)
    _SELoopTop:
        lb $a1, ($a0)              # load next 2 chars
        lb $a3, ($a2)              #
        bne $a1, $a3, _SEnoMatch   # return false if chars don't match
        beqz $a1, _SEmatch         # return true if at null terminator
        addi $a0, $a0, 1           # advance both by one
        addi $a2, $a2, 1      
        j _SELoopTop
    _SEnoMatch:
        li $v0, 0
        jr $ra
    _SEmatch:
        li $v0, 1
        jr $ra


	#  Library function Halt()
	#  -----------------------
	#  Exits process
	.globl _Halt
  _Halt:
	li $v0, 10			  # 10 is code for exit syscall
	syscall


	.globl __eoth
__eoth:
