.global log2
log2:
	movaps %xmm0, -0x10(%rsp)
	fldln2
	fld -0x10(%rsp)
	fyl2x
	movsd %xmm0, %xmm1
	ret
