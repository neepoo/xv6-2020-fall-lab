# Context switch
#
#   void swtch(struct context *old, struct context *new);
#   a0:old a1:new
# Save current registers in old. Load from new.	
# https://msyksphinz-self.github.io/riscv-isadoc/html/rv64i.html#sd
# Register	ABI Name	Description	Saver
# x0	zero	hardwired zero	-
# x1	ra	return address	Caller
# x2	sp	stack pointer	Callee
# x3	gp	global pointer	-
# x4	tp	thread pointer	-
# x5-7	t0-2	temporary registers	Caller
# x8	s0 / fp	saved register / frame pointer	Callee
# x9	s1	saved register	Callee
# x10-11	a0-1	function arguments / return values	Caller
# x12-17	a2-7	function arguments	Caller
# x18-27	s2-11	saved registers	Callee
# x28-31	t3-6	temporary registers	Caller


.globl swtch
swtch:
# ra -> 0(a0)
        sd ra, 0(a0)
        sd sp, 8(a0)
        sd s0, 16(a0)
        sd s1, 24(a0)
        sd s2, 32(a0)
        sd s3, 40(a0)
        sd s4, 48(a0)
        sd s5, 56(a0)
        sd s6, 64(a0)
        sd s7, 72(a0)
        sd s8, 80(a0)
        sd s9, 88(a0)
        sd s10, 96(a0)
        sd s11, 104(a0)

        ld ra, 0(a1)
        ld sp, 8(a1)
        ld s0, 16(a1)
        ld s1, 24(a1)
        ld s2, 32(a1)
        ld s3, 40(a1)
        ld s4, 48(a1)
        ld s5, 56(a1)
        ld s6, 64(a1)
        ld s7, 72(a1)
        ld s8, 80(a1)
        ld s9, 88(a1)
        ld s10, 96(a1)
        ld s11, 104(a1)
        
        ret

	
