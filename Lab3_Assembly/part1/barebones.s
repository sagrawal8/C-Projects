# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
					# (1) What are we setting up here?
					# Ans:
	pushq %rbp			# Pushing quadword of %rbp which points to base of stack.
	movq  %rsp, %rbp		# Moves a quadword of %rsp and %rbp, which is the top of stack and bottom of stack.
					# Command<src , dest> top of stack is copied to bottom of stack? I'm guessing we are
					# initializing a stack here?

					# (2) What is going on here
					# Ans:
	movq $1, %rax			# stores literal value 1 at %rax (accumulator register) (temp = $1)
	movq $1, %rdi			# stores literal value 1 at %rdi register. (We are defining capacity of stack? or first program argument (%rdi = $1))
	leaq .hello.str,%rsi		# stores address of hello.str at register %rsi. ->loading address of string?


					# (3) What is syscall? We did not talk about this
					# in class.
					# Ans:  A computer program makes a system call when it makes a request to the operating system’s kernel. 
					# System call provides the services of the operating system to the user programs via Application Program Interface(API)
	syscall				# Which syscall is being run?
					# Ans: syscall(1)

					# (4) What would another option be instead of 
					# using a syscall to achieve this?
					# Ans: printf();

	movq	$60, %rax		# (5) We are again setting up another syscall
	movq	$0, %rdi		# What command is it?
					# Ans:	syscall(60) to exit?
	syscall

	popq %rbp			# (Note we do not really need
					# this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans:	lenth of string is 13
