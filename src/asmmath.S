.global log
.type log,@function
log:
	sub $24, %rsp
	movaps %xmm0, -0x10(%rsp)
	fldln2
	fldl -0x10(%rsp)
	fyl2x
	mov $0, -0x10(%rsp)
	fstl -0x10(%rsp)
	movq -0x10(%rsp), %xmm0
	add $24, %rsp
	ret

.global log2
.type log2,@function
log2:
	sub $24, %rsp
	movaps %xmm0, -0x10(%rsp)
	fld1
	fldl -0x10(%rsp)
	fyl2x
	mov $0, -0x10(%rsp)
	fstl -0x10(%rsp)
	movq -0x10(%rsp), %xmm0
	add $24, %rsp
	ret

.global atan
.type atan,@function
atan:
	sub $24, %rsp
	movaps %xmm0, -0x10(%rsp)
	fldl -0x10(%rsp)
	fld1
	fpatan
	mov $0, -0x10(%rsp)
	fstl -0x10(%rsp)
	movq -0x10(%rsp), %xmm0
	add $24, %rsp
	ret

.global __pow2m1
.type __pow2m1,@function
__pow2m1:
	sub $24, %rsp
	movaps %xmm0, -0x10(%rsp)
	fldl -0x10(%rsp)
	f2xm1	
	mov $0, -0x10(%rsp)
	fstl -0x10(%rsp)
	movq -0x10(%rsp), %xmm0
	add $24, %rsp
	ret
