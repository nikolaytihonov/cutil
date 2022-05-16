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


_cu_memcpy:
    // RDI - dst, RSI - src, RDX - size
    mov %rdx, %rcx
    shr $3, %rcx
    je .cpy1
    rep movsq
.cpy1:
    mov %rdx, %rcx
    and $7, %rcx
    rep movsb
    ret

_cu_memmove:
    // RDI - dst, RSI - src, RDX - size
    cmp %rsi, %rdi
    je .retmove
    jl .lessmove
.greatermove:   // dst > src
    add %rdx, %rdi
    add %rdx, %rsi
    std
    dec %rdi
    dec %rsi
    mov %rdx, %rcx
    rep movsb
    cld
    jmp .retmove
.lessmove:      // dst < src
    mov %rdx, %rcx
    rep movsb
.retmove:
    ret

_cu_memcmp:
    mov %rdx, %rcx
    shr $3, %rcx
    jz .test1
.cmp8:
    cmpsq
    jnz .not_equal
    loop .cmp8
.test1:
    mov %rdx, %rcx
    and $7, %rcx
.cmp1:
    cmpsb
    jnz .not_equal
    loop .cmp1
    jmp .equal
.not_equal:
    xor %rax, %rax
    inc %rax
    ret
.equal:
    xor %rax, %rax
    ret

_cu_memset:
    // RDI - ptr, RSI - val, RDX - size
    mov %rdx, %rax

    mov %rsi, %rcx
    shr $3, %rcx
    je .set1
    rep stosq
.set1:
    mov %rsi, %rcx
    and $7, %rcx
    rep stosb

    ret

cu_memzero:
    xor %rax, %rax

    mov %rsi, %rcx
    shr $3, %rcx
    rep stosq

    mov %rsi, %rcx
    and $7, %rcx
    rep stosb

    ret

cu_memtest:
    // RDI - ptr, RSI - size
    xchg %rsi, %rdi
    
    mov %rdi, %rcx
    shr $3, %rcx
    je .skipq
.testq:
    lodsq
    test %rax, %rax
    jnz .testfail
    loop .testq
.skipq:
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


cu_va_start:
    // RDI - va
    mov %rsp, %rax
    mov %rdi, %rsp
    add $0x30, %rsp

    push %r9
    push %r8
    push %rcx
    push %rdx
    push %rsi
    push %rdi

    mov %rax, %rsp
    ret

cu_va_arg:
    // RDI - va, RSI - index
    push %rbx
    mov %rsi, %rbx
    shl $3, %rbx

    cmp $6, %rsi
    jge .va_stack

    mov (%rbx,%rdi),%rax

    pop %rbx
    ret
.va_stack:
    sub $0x30, %rbx
    add $0x10, %rbx
    mov (%rbx,%rbp),%rax

    pop %rbx
    ret
