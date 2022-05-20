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
    bx lr

hw_bswap32:
    bx lr

hw_bswap64:
    bx lr

_cu_memcpy:
    bx lr

_cu_memmove:
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
