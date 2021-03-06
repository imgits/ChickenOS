/* ChickenOS - device/chardevs.c
 * Implements /dev/(mem|kmem|null|port|zero|full|random|urandom)
 * TODO: Add proper random and implement port access
 * 		 Better access of physical/virtual kernel memory
 * 		 kmem/mem should probably do verification that given
 * 		 	memory is read/writeable (Check your privlege!)
 */
#include <kernel/common.h>
#include <kernel/hw.h>
#include <memory.h>
#include <mm/vm.h>
#include <fs/vfs.h>
#include <sys/ioctl.h>
#include <errno.h>

size_t chardevs_read(dev_t dev, void *buf, size_t count, off_t off)
{
	uintptr_t ptr = off;
	ASSERT(MAJOR(dev) == 1, "Bad device passed");
	switch(MINOR(dev))
	{
		case 1: //mem (Physical)
			ptr = P2V(ptr);
		case 2: //kmem (Virtual)
			kmemcpy(buf, (void *)ptr, count);
			return count;
		case 3: //null
			return 0;
		case 4: //port
			return -EINVAL;
		case 7: //full
		case 5: //zero
			kmemset(buf, 0x00, count);
			return count;
		//FIXME: Add random numbers
		case 8: case 9: //random | urandom
			kmemset(buf, 4, count);
			return count;
	}
	printf("Invalid read of character device 0x1%.2X\n", MINOR(dev));
	return -EINVAL;
}

size_t chardevs_write(dev_t dev, void *buf, size_t count, off_t off)
{
	uintptr_t ptr = off;
	ASSERT(MAJOR(dev) == 1, "Bad device passed");
	switch(MINOR(dev))
	{
		case 1: //mem (Physical)
			ptr = P2V(ptr);
		case 2: //kmem (Virtual)
			kmemcpy((void *)ptr, buf, count);
			return count;
		case 4: //port
			return -EINVAL;
		case 3: case 5: case 8: case 9:  //null | zero | random | urandom
			return count;
		case 7: //full
			return -ENOSPC;
	}
	printf("Invalid write of character device 0x1%.2X\n", MINOR(dev));
	return -EINVAL;
}

int chardevs_ioctl(dev_t dev, int request UNUSED, char *args UNUSED)
{
	ASSERT(MAJOR(dev) == 1, "Bad device passed");
	printf("Invalid ioctl of character device 0x1%.2X\n", MINOR(dev));
	return -EINVAL;
}

void chardevs_init()
{
	device_register(FILE_CHAR, 0x100, chardevs_read, chardevs_write, chardevs_ioctl);
}
