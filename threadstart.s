
.global threadstart

threadstart:

		pushq %rbx
		pushq %rbp
		pushq %r12
		pushq %r13
		pushq %r14
		pushq %r15
		
		movq %rsp, (%rdi)
		movq (%rsi), %rsp
		
		jmp thread_wrap
	
