#include <kernel/memory.h>

size_t kstrlen(uint8_t *str)
{
	uint8_t *tmp = str;
	while(*tmp != '\0')
		tmp++;
	return tmp - str;
}

uint8_t *kmemcpy(void *dest, const void *src, size_t count)
{
	uint8_t *tmp = dest;
	uint8_t *dest_ = dest;
	const uint8_t *src_ = src;
	while(count-- != 0)
		*dest_++ = *src_++;

	return tmp;
}

uint16_t *kmemcpyw(uint16_t *dest, uint16_t *src, size_t count)
{
	uint16_t *tmp = dest;
	while(count-- != 0)
		*dest++ = *src++;

	return tmp;
}

uint8_t *kmemset(void *dest, uint8_t val, size_t count)
{
	uint8_t *tmp = dest;
	while(count-- != 0)
		*tmp++ = val;

	return dest;
}

uint16_t *kmemsetw(uint16_t *dest, uint16_t val, size_t count)
{
	uint16_t *tmp = dest;
	while(count-- != 0)
		*dest++ = val;

	return tmp;
}

uint32_t *kmemsetl(uint32_t *dest, uint32_t val, size_t count)
{
	uint32_t *tmp = dest;
	while(count-- != 0)
		*dest++ = val;

	return tmp;
}
