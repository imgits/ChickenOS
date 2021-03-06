#ifndef C_OS_VFS_H
#define C_OS_VFS_H
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/uio.h>
typedef int64_t ino64_t;
typedef int64_t off64_t;
typedef uint64_t blkcnt64_t;


struct stat64
{
	dev_t st_dev;
	int __st_dev_padding;
	long __st_ino_truncated;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	int __st_rdev_padding;
	off64_t st_size;
	blksize_t st_blksize;
	blkcnt64_t st_blocks;
	struct timespec st_atim;
	struct timespec st_mtim;
	struct timespec st_ctim;
	ino64_t st_ino;
};
/* only define when STDIO is not included */
#ifndef _STDIO_H
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif
//default block/buffer size
#define SECTOR_SIZE 512
//modes, actually from ext2, will use them globally for ease
/*
#define S_IFMT 		0xF000 	//format mask
#define S_IFSOCK 	0xA000 	//socket
#define S_IFLNK 	0xC000 	//symbolic link
#define S_IFREG 	0x8000 	//regular file
#define S_IFBLK 	0x6000 	//block device
#define S_IFDIR 	0x4000 	//directory
#define S_IFCHR 	0x2000 	//character device
#define S_IFIFO 	0x1000 	//fifo
#define S_ISUID 	0x0800 	//SUID
#define S_ISGID 	0x0400 	//SGID
#define S_ISVTX 	0x0200 	//sticky bit
#define S_IRWXU 	0x01C0 	//user mask
#define S_IRUSR 	0x0100 	//read
#define S_IWUSR 	0x0080 	//write
#define S_IXUSR 	0x0040 	//execute
#define S_IRWXG 	0x0038 	//group mask
#define S_IRGRP 	0x0020 	//read
#define S_IWGRP 	0x0010 	//write
#define S_IXGRP 	0x0008 	//execute
#define S_IRWXO 	0x0007 	//other mask
#define S_IROTH 	0x0004 	//read
#define S_IWOTH 	0x0002 	//write
#define S_IXOTH 	0x0001 	//execute
*/
enum file_type { FILE_CHAR  = 0x2000,
	FILE_DIR   = 0x4000,
	FILE_BLOCK = 0x6000};

typedef struct vfs_fs vfs_fs_t;
struct inode;

typedef size_t (*vfs_read_inode_t) (struct inode *, void *_buf, size_t length, off_t offset);
typedef size_t (*vfs_write_inode_t) (struct inode *, void *_buf, size_t length, off_t offset);
typedef struct inode * (*vfs_namei_t) (struct inode *dir, char *path);
typedef int (*vfs_read_sb_t) (vfs_fs_t *fs, uint16_t dev);
typedef int (*vfs_mount_t) (uint16_t dev);

typedef struct vfs_superblock_ops {
	vfs_read_inode_t read;
	vfs_write_inode_t write;
	//vfs_creat_t creat;
	//vfs_mkdir_t mkdir;
	vfs_read_sb_t read_sb;
	vfs_namei_t namei;
} vfs_ops_t;

typedef struct vfs_sb {
	void *sb;
	struct inode *root;

} vfs_sb_t;

struct vfs_fs {
	vfs_sb_t *superblock;
	char name[10];
	void *aux;
	uint16_t dev;
	vfs_ops_t *ops;
};
struct inode {
	struct stat info;
	//if part of mount point,keep in cache
	uint32_t flags;
	void *storage;
	//may need parent
	vfs_fs_t *fs;
};
#define I_MOUNT 0x1

struct file {
	char name[256];
	struct inode *inode;
	uint32_t offset;
	vfs_fs_t *fs;
};


vfs_fs_t *vfs_alloc();
struct inode * pathsearch(struct inode *dir, char *_path);

int vfs_register_fs(vfs_fs_t *fs);

void vfs_init();
void vfs_mount_root(uint16_t dev, char *type);

struct file *vfs_open(char *path, int oflags, mode_t mode);
int vfs_close(struct file *file);
size_t vfs_read(struct file *file, void *buf, size_t nbyte);
off_t vfs_write(struct file *file, void *buf, size_t nbyte);
off_t vfs_seek(struct file *file, off_t offset, int whence);
int vfs_ioctl(struct file *file, int request, char *args);
int vfs_chdir(const char *path);
int vfs_stat(const char *path, struct stat *buf);
int vfs_stat64(const char *path, struct stat64 *buf);

/* ops.c - standard file ops */
int sys_open(const char *path, int oflag, mode_t mode);
int sys_close(int fd);
ssize_t sys_read(int fildes, void *buf, size_t nbyte);
ssize_t sys_write(int filedes, void *buf, size_t nbyte);
ssize_t sys_readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t sys_writev(int fd, const struct iovec *iov, int iovcnt);
char* sys_getcwd(char *buf, size_t size);

int sys_creat(const char *path, mode_t mode);
int sys_stat(const char *filename, struct stat *statbuf);
off_t sys_lseek(int fildes, off_t offset, int whence);
int sys_ioctl(int fildes, int request, char *args);
int sys_stat64(const char *path, struct stat64 *buf);
//device.c
#define INITRD_DEV 0x400
#define ATA0_0_DEV 0x301
#define MAJOR(x) ((x & 0xFF00) >> 8)
#define MINOR(x) (x & 0xFF)

typedef size_t (*char_read_fn)(dev_t dev, void *buf, size_t count, off_t offset);
typedef size_t (*char_write_fn)(dev_t dev, void *buf, size_t count, off_t offset);
typedef int (*char_ioctl_fn)(dev_t dev, int request, char *arg);

struct char_device_ops {
	char_read_fn read;
	char_write_fn write;
	char_ioctl_fn ioctl;
};

typedef size_t (*block_read_fn) (uint16_t dev, void *buf, int block);
typedef size_t (*block_write_fn)(uint16_t dev, void *buf, int block);

void  device_register(uint16_t type, dev_t dev, void *read, void *write, void *ioctl);
typedef int(*block_access_fn)(void *aux, void *buf, int block);

int char_device_ioctl(dev_t dev, int request, char *args);
size_t char_device_read(dev_t dev, void *buf, off_t offset, size_t nbyte);
size_t char_device_write(dev_t dev, void *buf, off_t offset, size_t nbyte);
size_t block_device_read(uint16_t dev, void *buf, uint32_t block);
size_t block_device_readn(uint16_t dev, void *buf, uint32_t block, off_t offset, size_t nbyte);

int read_block_at(uint16_t dev, void * _buf, int block,int block_size, off_t offset, size_t nbytes);
int read_block(uint16_t dev, void * _buf, int block, int block_size);

int write_block_at(uint16_t dev, void * _buf, int block,int block_size, off_t offset, size_t nbytes);
int write_block(uint16_t dev, void * _buf, int block, int block_size);

#endif
