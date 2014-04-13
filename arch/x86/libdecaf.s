// File: libdecaf.s
// ================
// Linux x86 Decaf standard library
//
// Note: this file is written in x86 assembly and specifically for Linux since
// it uses the Linux system call numbers
//

	.text

// Standard startup code.  Invoke the routine "main" with arguments:
//	main(argc, argv, envp)
//
	.globl __start
__start:
	// FIXME Invoke main

	//  From here down is the standard library which is linked into all
	//  programs. It contains the assembly for the built-in library
	//  functions (Print, Read, Alloc)
	//  Where possible built-ins are frameless (don't set up fp, etc.)
	//  Each expects args to be in $sp + 4, +8, etc.
	//  Return value (if any) assigned to v0
	//  May trash a0-a3 registers, uses no others


	//  Library function ptr = Alloc(int size)
	//  -----------------------------------------
	//  Used for New and NewArray.
	//  Allocates space in heap and returns address in $v0
	.globl _Alloc
_Alloc:


	//  Library function PrintInt(int n)
	//  --------------------------------
	//  Prints number given as argument to console
	.globl _PrintInt
_PrintInt:


	//  Library function PrintBool(bool b)
	//  ----------------------------------
	//  Prints true/false value given to console
	.globl _PrintBool
_PrintBool:

	#  Library function PrintString(address str)
	#  -----------------------------------------
	#  Prints string located at the address to console
	.globl _PrintString
_PrintString:

	#  Library function n = ReadInteger()
	#  ----------------------------------
	#  Reads a number from the console and returns it in $v0
	.globl _ReadInteger
_ReadInteger:

  	#  Library function s = ReadLine()
	#  -------------------------------
	#  Reads a line from the console into heap-allocated buffer and
	#  returns its address in $v0
	.globl _ReadLine
_ReadLine:

	#  Library function if (StringEqual(addr s, addr t)) ...
	#  ----------------------------------------------------
	#  Compares two strings for equality (case-sensitive)
	#  returns true/false in $v0
	.globl _StringEqual
_StringEqual:

	#  Library function Halt()
	#  -----------------------
	#  Exits process by calling the exit() syscall
	.globl _Halt
_Halt:
