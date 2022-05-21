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
.align 16

hw_bswap16:
    rev r0, r0
    mov r0, r0, lsr #16
    bx lr

hw_bswap32:
    rev r0, r0
    bx lr

hw_bswap64:
    rev r2, r0
    rev r0, r1
    mov r0, r2
    bx lr

_cu_memcpy:
    // r0 - dst, r1 - src, r2 - size
    str r4, [sp, #-4]!

    mov r3, r2, lsr #2
    tst r3, r3
    beq .cpy1_
.cpy4:
    ldr r4, [r1], #4
    str r4, [r0], #4
    subs r3, r3, #1
    bne .cpy4
.cpy1_:
    ands r3, r2, #3
    beq .cpy0
.cpy1:
    ldrb r4, [r1], #1
    strb r4, [r0], #1
    subs r3, r3, #1
    bne .cpy1
.cpy0:
    ldr r4, [sp], #4
    bx lr

_cu_memmove:
    // r0 - dst, r1 - src, r2 - size
    cmp r0, r1
    beq .move0
    blt .less1

    add r0, r0, r2
    add r1, r1, r2
    sub r0, r0, #1
    sub r1, r1, #1
.greater1:
    ldrb r3, [r1], #-1
    strb r3, [r0], #-1
    subs r2, r2, #1
    bne .greater1
    b .move0
.less1:
    ldrb r3, [r1], #1
    strb r3, [r0], #1
    subs r2, r2, #1
    bne .less1
.move0:
    bx lr

_cu_memcmp:
    bx lr

_cu_memset:
    bx lr

cu_memzero:
    bx lr

cu_memtest:
    bx lr

cu_va_start:
    bx lr

cu_va_arg:
    bx lr
