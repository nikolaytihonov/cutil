.globl hw_bswap16
.globl hw_bswap32
.globl hw_bswap64
.globl cu_memtest

.text

hw_bswap16:
    mov %edi, %eax
    xchg %al, %ah
    ret

hw_bswap32:
    mov %edi, %eax
    bswap %eax
    ret

hw_bswap64:
    mov %rdi, %rax
    bswap %rax
    ret

cu_memtest:
    // RDI - ptr, RSI - size
    xchg %rsi, %rdi
    
    mov %rdi, %rcx
    shr $3, %rcx
    je .testok
.testq:
    lodsq
    test %rax, %rax
    jnz .testfail
    loop .testq

    mov %rdi, %rcx
    and $7, %rcx
    je .testok
.testb:
    lodsb
    test %al, %al
    jnz .testfail
    loop .testb

.testok:
    xor %rax, %rax
    ret
.testfail:
    mov %rsi, %rax
    ret