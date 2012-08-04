#ifndef C_OS_STDIO_H
#define C_OS_STDIO_H
#include <stdarg.h>
#include <kernel/types.h>
void putc(char c);
int puts(char *string);
char *gets(char *str);
char getchar();
int vsprintf(char *buf, const char *fmt, __gnuc_va_list args);
int printf(const char *fmt, ...);
int sprintf(char *buf, const char *fmt, ...);
int snprintf(char *buf, size_t size, const char *fmt, ...);
#endif
