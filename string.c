#include "string.h"
#include "cutil.h"
#include "va_list.h"

size_t cu_strlen(const char* str)
{
    u32 len = 0;
    while(*str++) len++;
    return len;
}

void cu_strcpy(char* dst, const char* src)
{
    while((*dst++ = *src++)){}
}

void cu_strncpy(char* dst, const char* src, size_t maxLen)
{
    maxLen=-1;
    while((*dst++ = *src++) && --maxLen){}
    if(!maxLen) dst[maxLen] = '\0';
}

const char* cu_strchr(const char* src, char chr)
{
    while(*src)
    {
        if(*src == chr) return src;
        src++;
    }
    return NULL;
}

const char* cu_strrchr(const char* src, char chr)
{
    const char* ptr;
    
    ptr = src+cu_strlen(src)-1;
    while(ptr != src)
    {
        if(*ptr == chr) return ptr;
        ptr--;
    }
    return NULL;
}

int cu_strcmp(const char* src, const char* dst)
{
    if(cu_strlen(src) != cu_strlen(dst)) return 1;
    while(*src)
        if(*src++ != *dst++) return 1;
    return 0;
}

int cu_strncmp(const char* haystack, char* needle)
{
    return !!cu_memcmp(haystack,needle,cu_strlen(needle));
}

int cu_strcasecmp(const char* src, const char* dst)
{
    if(cu_strlen(src) != cu_strlen(dst)) return 1;
    while(*src)
    {
        if(cu_tolower(*src++) != cu_tolower(*dst++))
            return 1;
    }
    return 0;
}

char cu_toupper(char c)
{
    if(c >= 0x61 && c <= 0x7A) return c&0xDF;
    return c;
}

char cu_tolower(char c)
{
    if(c >= 0x41 && c <= 0x5A) return c|(1<<5);
    return c;
}

size_t cu_chrlen(char cchr)
{
    u8 chr = (u8)cchr;
    
    if(chr & 0b10000000)
    {
        if((chr>>5) == 0b110) return 2;
        else if((chr>>4) == 0b1110) return 3;
        else if((chr>>5) == 0b11110) return 4;
    }
    return 1;
}

dbcs_t cu_chr2dbcs(const char* ptr)
{
    const u8* chr = (u8*)ptr;
    
    switch(cu_chrlen(chr[0]))
    {
        case 1: return chr[0]&0x7F;
        case 2: return ((chr[0]&0x1F)<<6)|(chr[1]&0x3F);
        case 3: return ((chr[0]&0x0F)<<12)|((chr[1]&0x3F)<<6)|(chr[2]&0x3F);
        default: return 0x003F;
    }
}

size_t cu_dbcslen(dbcs_t chr)
{
    if(chr > 0x7FF) return 3;
    else if(chr > 0x7F) return 2;
    return 1;
}

void cu_dbcs2str(dbcs_t* dbcs, char* str, size_t maxStr)
{
    char* end = str + maxStr - 1;
    dbcs_t wc;
    
    while((wc = *dbcs++) && str != end)
    {
        size_t len = cu_dbcslen(wc);
        if((str+len) >= end) break;
        switch(len)
        {
            case 1:
                *str++ = wc&0x7F;
                break;
            case 2:
                *str++ = 0b11000000|((wc>>6)&0x1F);
                *str++ = 0b10000000|((wc)&0x3F);
                break;
            case 3:
                *str++ = 0b11100000|((wc>>12)&0x0F);
                *str++ = 0b10000000|((wc>>6)&0x3F);
                *str++ = 0b10000000|((wc)&0x3F);
                break;
            default: *str++ = '?';
        }
    }
    *str++ = '\0';
}

static char* xnums = "0123456789ABCDEF";

void cu_iprints(char* outs, iword number)
{
    //18446744073709551615
    char num[32];
    char* s = num;
    int uns = 0;
    
    if(number < 0)
    {
        uns = 1;
        number *= -1;
    }
    while(number >= 10)
    {
        *s++ = '0'+(number%10);
        number/=10;
    }
    *s++ = '0'+(number%10);
    if(uns) *s++ = '-';
    while(s >= num) *outs++ = *--s;
    *outs++ = '\0';
}

void cu_uprints(char* outs, uword number)
{
    //18446744073709551615
    char num[32];
    char* s = num;
    while(number >= 10)
    {
        *s++ = '0'+(number%10);
        number/=10;
    }
    *s++ = '0'+(number%10);
    while(s >= num) *outs++ = *--s;
    *outs++ = '\0';
}

void cu_xprints(char* outs, uword number)
{
    //FFFFFFFFFFFFFFFF
    char num[32];
    char* s = num;
    
    while(s-num < 15)
    {
        *s++ = xnums[(number%16)];
        number/=16;
    }
    *s++ = xnums[(number%16)];
    *s++ = 'x';
    *s++ = '0';
    while(s >= num) *outs++ = *--s;
    *outs++ = '\0';
}

static iword _cu_atoi(char* str, int base, size_t len)
{
    char* end;
    iword i, pow;
    iword num;
    
    i = 0;
    num = 0;
    pow = 1;
    end = str+len-1;
    while(1)
    {
        if(*end == '-')
        {
            num *= -1;
            break;
        }
        else if(*end == 'x') break;
        for(i = 0; i < base; i++)
            if(*end == xnums[i]) break;
        num += i*pow;
        pow *= base;
        
        if(end == str) break;
        end--;
    }
    
    return num;
}

static uword _cu_atou(char* str, int base, uword len)
{
    char* end;
    uword pow, num;
    iword i;
    
    i = 0;
    num = 0;
    pow = 1;
    end = str+len-1;
    while(1)
    {
        if(*end == 'x') break;
        for(i = 0; i < base; i++)
            if(*end == xnums[i]) break;
        num += i*pow;
        pow *= base;
        
        if(end == str) break;
        end--;
    }
    
    return num;
}

iword cu_atoi(char* str, int base)
{
    return _cu_atoi(str, base, cu_strlen(str));
}

uword cu_atou(char* str, int base)
{
    return _cu_atou(str, base, cu_strlen(str));
}

void cu_sprintf(char* dst, size_t maxLen, const char* fmt, ...)
{
    cu_va_list ap;
    cu_va_start(&ap);
    
    uword idx;
    char* cur,*end,c;
    char numbuf[64];
    
    idx = 3;
    cur = dst;
    end = dst+maxLen;
    while((c = *fmt++) && cur != end)
    {
        if(c == '%')
        {
            char* p = numbuf;
            c = *fmt++;
            if(c == 'd')
            {    
                cu_iprints(numbuf,(iword)cu_va_arg(&ap,idx++));
                while((*cur++ = *p++))
                    if(cur == end) break;
                cur--;
            }
            else if(c == 'u')
            {
                cu_uprints(numbuf,(iword)cu_va_arg(&ap,idx++));
                while((*cur++ = *p++))
                    if(cur == end) break;
                cur--;
            }
            else if(c == 'p' || c == 'x')
            {
                cu_xprints(numbuf,(uword)cu_va_arg(&ap,idx++));
                while((*cur++ = *p++))
                    if(cur == end) break;
                cur--;
            }
            else if(c == 's')
            {
                const char* str = (const char*)cu_va_arg(&ap,idx++);
                while((*cur++ = *str++))
                    if(cur == end) break;
                cur--;
            }
            else if(c == '%')
            {
                if(cur != end) *cur++ = '%';
            }
        }
        else
        {
            if(cur == end) break;
            *cur++ = c;
        }
    }
    if(cur == end)
        *(end-1) = '\0';
}

static uword _cu_strchr_delim(char* buf, u32 base)
{
    uword i,len;
    char c;
    
    len = 0;
    while(*buf)
    {
        c = *buf;
        for(i = 0; i < base; i++) 
        {
            if(c == xnums[i]) break;
        }
        if(i == base && c != '-') break;
        buf++;
        len++;
    }
    return len;
}

void cu_sscanf(char* buf, char* fmt, ...)
{
    //ulong* argp;
    cu_va_list ap;
    cu_va_start(&ap);
    
    uword idx;
    uword len, maxLen;
    union {
        iword* iptr;
        uword* uptr;
        char* sptr;
    } u;
    char c,*stk;
    
    idx = 2;
    while((c = *fmt))
    {
        //kprintf("%c %c\n",c,*buf);
        if(c == '%')
        {
            c = *++fmt;
            switch(c)
            {
                case 'u':
                case 'd':
                    len = _cu_strchr_delim(buf,10);
                    u.iptr = (i64*)(cu_va_arg(&ap,idx++));
                    *u.iptr = _cu_atoi(buf,10,len);
                    buf += len; //we decrement because it will +1
                    break;
                case 'p':
                case 'x':
                    buf += 2; //Skip 0x part
                    len = _cu_strchr_delim(buf,16);
                    u.iptr = (i64*)(cu_va_arg(&ap,idx++));
                    *u.iptr = _cu_atoi(buf,16,len);
                    buf += len; //we decrement because it will +1
                    break;
                case 's':
                    stk = (char*)cu_strchr(buf,*(fmt+1));
                    u.sptr = (char*)(cu_va_arg(&ap,idx++));
                    maxLen = (uword)(cu_va_arg(&ap,idx++));
                    if(!stk)
                    {
                        u.sptr[0] = '\0';
                        break;
                    }
                    len = (uword)stk-(uword)buf;
                    if(len > maxLen) len = maxLen;
                    cu_memcpy(u.sptr,buf,len);
                    u.sptr[len] = '\0';
                    buf += len;
                    break;
            }
            
        } else buf++;
        fmt++;
    }
}
