.globl hw_bswap16
.globl hw_bswap32
.globl hw_bswap64

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

