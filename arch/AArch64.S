.globl hw_bswap16
.globl hw_bswap32
.globl hw_bswap64
.globl _cu_memcpy
.globl _cu_memmove
.globl _cu_memcmp
.globl _cu_memset
.globl cu_memzero
.globl cu_memtest
.globl cu_va_start
.globl cu_va_arg

.text

hw_bswap16:
    rev w0, w0
    mov w0, w0, lsr #16
    ret

hw_bswap32:
    rev w0, w0
    ret

hw_bswap64:
    rev x0, x0
    ret

_cu_memcpy:
    // x0 - dst, x1 - src, x2 - size
    mov x3, x2, lsr #3
    tst x3, x3
    beq .cpy1_
.cpy8:
    ldr x4, [x1], #8
    str x4, [x0], #8
    subs x3, x3, #1
    bne .cpy8
.cpy1_:
    and x3, x2, #7
    beq .cpy0
.cpy1:
    ldrb w4, [x1], #1
    strb w4, [x0], #1
    subs x3, x3, #1
    bne .cpy1
.cpy0:
    ret

_cu_memmove:
    ret

_cu_memcmp:
    ret

_cu_memset:
    ret

cu_memzero:
    ret

cu_memtest:
    ret

cu_va_start:
    ret

cu_va_arg:
    ret
