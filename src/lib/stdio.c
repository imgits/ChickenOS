/* ChickenOS - Standard I/O functions
 * TODO:
 * Cleanup
 */
#include <common.h>
#include <device/console.h>
#include <device/tty.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void putc(char c)
{
	tty_putc(c);
}

void putchar(int c)
{
	tty_putc(c);
}

char getchar()
{
	return kbd_getc();
}

char *gets(char *str)
{
	char c;
	char *tmp = str;
	while((c = getchar()) != '\n')
	{
		*tmp++ = c;
	}

	*tmp++ = '\0';
	return str;
}

int puts(char *string)
{
	int cnt = 0;
	if(string == NULL)
	{
		return puts("(null)");
	}
	while(*string != '\0')
	{
		putc(*string++);
		cnt++;
	}

	return cnt;
}
/* this could be better */
static char *strip_zeros(char *str)
{
	char *tmp = str;
	if(str[0] != '0')
		return str;
	if(str[1] == 0)
		return str;
	if(str[0] == '-')
	{
		return str;
	}
	while(*++tmp == '0');// && (*tmp + 2) != 0);
	return tmp;
}

char neg[2] = {'-','0'};
char dp[256];
static char *int_to_string(int num, int base, int size)
{
	int i;
	char *tmp = NULL;//allocp;//alloc(size);
	for(i = 0; i < 100; i++)
		tmp[i] = 0;
	char * ascii = {"0123456789ABCDEF"};
	memset(dp, 0, 256);
//	if(sign)
//		tmp++;
	/*int start = 0;
	int temp = num;
	if((num < 0) && (base == 10))
	{
	//	start = 1;
	//	size += 1;
		*tmp++ = '-';
		num = -1 * num;
	}*/
	if(num < 0 && base == 10)
	{
		strcat(dp, "-");
		num = -1 * num;
	}
	if(num == 0)
	{
		tmp[0] = '0';
		tmp[1] = 0;
		return tmp;
	}


	switch(base)
	{
		case 2:
			for(i = size-1; i >= 0; i--)
			{
				tmp[i] = ascii[num & 0x1];
				num >>= 1;
			}
			break;
		case 10:
			for(i = size-1; i >= 0; i--)
			{
				tmp[i] = ascii[num % 10];
				num /= 10;
			}
			break;
		case 16:
			for(i = 7; i >= 0; i--)
			{
				tmp[i] = ascii[num & 0xF];
				num >>= 4;
			}
			break;
		default:
			puts("invalid base given to int_to_string");

			break;
	}
//	if(temp < 0)
	//	tmp--;
//	tmp[size+1] = '\0';
	tmp = strip_zeros(tmp);
	strcat(dp, tmp);
	return dp;
}

/* based on minprintf from K&R page 156 */
void oprintf(char *fmt, ...)
{
	va_list ap;
	char *p;
	char *s_val;
	char *strip;
	char c_val;
	int i_val;
	double d_val;
	(void)d_val;
	va_start(ap, fmt);
	for(p = fmt; *p; p++)
	{
		if(*p != '%'){
			putc(*p);
			continue;
		}
		switch(*++p)
		{
			case 'b':
				i_val = va_arg(ap, int);
				s_val = int_to_string(i_val, 2, 32);
				strip = strip_zeros(s_val);
				puts(strip);
			//	afree(s_val);
				break;

			case 'c':
				c_val = va_arg(ap, int);
				putc(c_val);
				break;
			case 'd':
			case 'i':
				i_val = va_arg(ap, int);
				s_val = int_to_string(i_val, 10, 10);
				strip = strip_zeros(s_val);
				puts(strip);
			//	afree(s_val);
				break;
			case 'f':
				d_val = va_arg(ap,double);
				break;
			case 's':
				s_val = va_arg(ap, char *);
				puts(s_val);
			//	afree(s_val);
				break;
			case 'X':
				puts("0x");
			case 'x':
				i_val = va_arg(ap, int);
				s_val = int_to_string(i_val, 16, 8);
				strip = strip_zeros(s_val);
				puts(strip);
			//	afree(s_val);
				break;

			default:
				putc(*p);
				break;
		}
	//	for(int i= 0; i < 100; i++)
	//		allocp[i] = 0;
	}

	va_end(ap);


}


/* based on minprintf from K&R page 156 */
int vsprintf(char *buf, const char *fmt, va_list args)
{
	va_list ap = args;
	char *p;
	char *s_val;
	char *strip;
	char c_val;
	int i_val;
	double d_val;
	char cbuf[2] = {0,0};
	(void)d_val;
	for(p = (char *)fmt; *p; p++)
	{
		if(*p != '%'){
			cbuf[0]  = *p;
			strcat(buf, cbuf);
			continue;
		}

		switch(*++p)
		{
			case 'b':
				i_val = va_arg(ap, int);
				s_val = int_to_string(i_val, 2, 32);
				strip = strip_zeros(s_val);
				strcat(buf,strip);
				//puts(strip);
			//	afree(s_val);
				break;

			case 'c':
				c_val = va_arg(ap, int);
				//putc(c_val);
				cbuf[0]  = c_val;
				strcat(buf, cbuf);

				break;
			case 'u':
			case 'd':
			case 'i':
				i_val = va_arg(ap, int);
				s_val = int_to_string(i_val, 10, 10);
				strip = strip_zeros(s_val);
				//puts(strip);
				strcat(buf,strip);
			//	afree(s_val);
				break;
			case 'f':
				d_val = va_arg(ap,double);
				break;
			case 's':
				s_val = va_arg(ap, char *);
				//puts(s_val);
				if(s_val != NULL)
					strcat(buf,s_val);
				else
					strcat(buf,"(null)");
			//	afree(s_val);
				break;
			case 'X':
				//puts("0x");
				strcat(buf,"0x");
			case 'x':
				i_val = va_arg(ap, int);
				s_val = int_to_string(i_val, 16, 8);
				strip = strip_zeros(s_val);
				//puts(strip);
				strcat(buf,strip);
			//	afree(s_val);
				break;
			default:
				//console_puts("ASFZSDFSDAF");
				//putc(*p);
				break;
		}
//		for(int i= 0; i < 100; i++)
//			allocp[i] = 0;
	}
	return 0;//buf - _buf;
}

int kvprintf(char const *fmt, void (*func)(int, void*), void *arg, int radix, va_list ap);

void testc(int c, void *aux UNUSED)
{
	putc(c);
	serial_putc(c);
}

void serial_testc(int c, void *aux UNUSED)
{
	serial_putc(c);
}

int printf(const char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = kvprintf(fmt, testc, NULL, 10, ap);
	va_end(ap);
	return ret;
}
int serial_printf(const char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = kvprintf(fmt, serial_testc, NULL, 10, ap);
	va_end(ap);
	return ret;
}

int sprintf(char *buf, const char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsprintf(buf, fmt, ap);
//	puts(buf);
	va_end(ap);
	return ret;
}
//FIXME: doesn't use size
int snprintf(char *buf, size_t size UNUSED, const char *fmt, ...)
{
	va_list ap;
	int ret;
	va_start(ap, fmt);
	ret = vsprintf(buf, fmt, ap);
//	puts(buf);
	va_end(ap);
	return ret;
}

void hex_dump(void *ptr, int n)
{
	uint8_t *p = ptr;
	for(int j =0; j < n; j++)
	{
		printf("%X ",p);
		for(int i = 0; i < 16; i++)
		{
			printf("%.2X ",p[i]);
		}
		printf("|");
		for(int i = 0; i < 16; i++)
		{
			printf("%c",isprint(p[i]) == 0 ? '.' : p[i]);
		}
		printf("|");
		printf("\n");
		p+=16;
	}
}

