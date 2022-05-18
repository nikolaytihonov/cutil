#ifndef __CUTIL_STRING_H
#define __CUTIL_STRING_H

#include "cutypes.h"

#define DBCS2SBCS(dbcs) ((char)(dbcs&0xFF))

typedef u16 dbcs_t;

size_t cu_strlen(const char* str);

void cu_strcpy(char* dst, const char* src);
void cu_strncpy(char* dst, const char* src, size_t maxLen);

const char* cu_strchr(const char* src, char chr);
const char* cu_strrchr(const char* src, char chr);

int cu_strcmp(const char* src, const char* dst);
int cu_strncmp(const char* haystack, char* needle);
int cu_strcasecmp(const char* src, const char* dst);

char cu_toupper(char c);
char cu_tolower(char c);

size_t cu_chrlen(char chr);
dbcs_t cu_chr2dbcs(const char* chr);

size_t cu_dbcslen(dbcs_t chr);
void cu_dbcs2str(dbcs_t* dbcs, char* str, size_t maxStr);

void cu_iprints(char* str, iword number);
void cu_uprints(char* str, uword number);
void cu_xprints(char* str, uword number);

iword cu_atoi(char* str, int base);
uword cu_atou(char* str, int base);

// all integer arguments must be iword or uword, strings - pointers
// format: d - decimal signed, u - unsigned, x - hexadecimal
// p - pointer address, s - zero-terminated string.
// to print % use %% format 
void cu_sprintf(char* dst, size_t maxLen, const char* fmt, ...);

// all integer arguments must be iword or uword,
// for strings pass pointer and next size of the buffer
// example: cu_sscanf((char*)str4, "\"%s\" %d", str5, 8, &val5);
// where %s is str5 buffer pointer and 8 is size of buffer
// and &val5 is pointer to iword integer
void cu_sscanf(char* buf, char* fmt, ...);

#endif