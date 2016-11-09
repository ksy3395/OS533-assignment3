
#void threadswitch(struct thread *old, struct thread *new);

.global threadswitch


threadswitch:
		pushq %rbx
		pushq %rbp
		pushq %r12
		pushq %r13
		pushq %r14
		pushq %r15

		movq %rsp,(%rdi)
		movq (%rsi),%rsp

        	pop %r15
		pop %r14
		pop %r13
		pop %r12
		pop %rbp
		pop %rbx

		ret

