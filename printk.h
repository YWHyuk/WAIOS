#ifndef _PRINTK_H
#define _PRINTK_H
#include <stdint.h>
#include <stdarg.h>

void* memset(void* dest, int data, long unsigned int size);
void* memcpy(void* dest, const void* src, long unsigned int size);
int memcmp(const void* dest, const void* src, long unsigned int size);
long unsigned int strlen(const char* pcBuffer);
long atoi( const char* buffer, int radix, long* ret);
int itoa( long value, char* buffer, int iRadix);
void printk(const char* format_string, ...);

#define TRUE 	1
#define FALSE	0
typedef int bool;
#endif
