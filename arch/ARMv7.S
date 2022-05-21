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
    push {r4, r5}

    mov r3, r2, lsr #2
    tst r3, r3
    beq .cmp1_
.cmp4:
    ldr r4, [r0], #4
    ldr r5, [r1], #4
    cmp r4, r5
    bne .cmpnot
    subs r3, r3, #1
    bne .cmp4
.cmp1_:
    ands r3, r2, #3
    beq .cmpok
.cmp1:
    ldrb r4, [r0], #1
    ldrb r5, [r1], #1
    cmp r4, r5
    bne .cmpnot
    subs r3, r3, #1
    bne .cmp1
.cmpok:
    eor r0, r0, r0
    pop {r4, r5}
    bx lr
.cmpnot:
    pop {r4, r5}
    bx lr

_cu_memset:
    // r0 - dst, r1 - val, r2 - size
    push {r4}

    orr r4, r1, r1, lsl #0
    orr r4, r4, r1, lsl #8
    orr r4, r4, r1, lsl #16
    orr r4, r4, r1, lsl #24

    mov r3, r2, lsr #2
    tst r3, r3
    beq .set1_
.set4:
    str r4, [r0], #4
    subs r3, r3, #1
    bne .set4
.set1_:
    ands r3, r2, #3
    beq .set0
.set1:
    strb r4, [r0], #1
    subs r3, r3, #1
    bne .set1
.set0:
    pop {r4}
    bx lr

cu_memzero:
    // r0 - dst, r1 - size
    eor r3, r3, r3

    mov r2, r1, lsr #2
    tst r2, r2
    beq .zero1_
.zero4:
    str r3, [r0], #4
    subs r2, r2, #1
    bne .zero4
.zero1_:
    ands r2, r1, #3
    beq .zero0
.zero1:
    strb r3, [r0], #1
    subs r2, r2, #1
    bne .zero1
.zero0:
    bx lr

cu_memtest:
    // r0 - src, r1 - size
    mov r2, r1, lsr #2
    tst r2, r2
    beq .test1_
.test4:
    ldr r3, [r0], #4
    tst r3, r3
    bne .testnot
    subs r2, r2, #1
    bne .test4
.test1_:
    ands r2, r1, #3
    beq .testok
.test1:
    ldrb r3, [r0], #1
    tst r3, r3
    bne .testnot
    subs r2, r2, #1
    bne .test1
.testok:
    eor r0, r0, r0
    bx lr
.testnot:
    bx lr

cu_va_start:
    add r1, r11, #8
    str r1, [r0]
    bx lr

cu_va_arg:
    // r0 - va_list, r1 - index
    mov r1, r1, lsl #2
    ldr r0, [r0]
    add r0, r0, r1
    ldr r0, [r0]
    bx lr
