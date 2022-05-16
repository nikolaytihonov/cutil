#ifndef __CUTIL_STRING_H
#define __CUTIL_STRING_H

#include "cutypes.h"

#define DBCS2SBCS(dbcs) ((char)(dbcs&0xFF))

typedef u16 dbcs_t;

size_t cu_strlen(const char* str);

void cu_strcpy(char* dst,const char* src);
void cu_strncpy(char* dst,const char* src, size_t maxLen);

const char* cu_strchr(const char* src,char chr);
const char* cu_strrchr(const char* src,char chr);

int cu_strcmp(const char* src,const char* dst);
int cu_strncmp(const char* haystack,char* needle);
int cu_strcasecmp(const char* src,const char* dst);

char cu_toupper(char c);
char cu_tolower(char c);

size_t cu_chrlen(char chr);
dbcs_t cu_chr2dbcs(const char* chr);

size_t cu_dbcslen(dbcs_t chr);
void cu_dbcs2str(dbcs_t* dbcs,char* str, size_t maxStr);

#endif