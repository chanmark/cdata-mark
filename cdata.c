#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/wait.h>
#include <asm/io.h>
#include <linux/ioctl.h>
#include "cdata_ioctl.h"

#ifdef CONFIG_SMP
#define __SMP__
#endif

#define	CDATA_MAJOR 121 

struct cdata_t {
	char data[1024];
	int  index;
}

static int cdata_open(struct inode *inode, struct file *filp)
{
	int minor;
	struct cdata_t *cdata;
	minor = MINOR(inode->i_rdev);
	printk(KERN_ALERT "filp Address = %p\n", filp);

	cdata = (struct cdata_t *)kmalloc(sizeof(struct cdata_t),GFP_KERNEL);
	
	filp->privdate_data = (void *)cdata; 

	return 0;
}

static int cdata_ioctl(struct inode *inode, struct file *filp, 
			unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case IOCTL_EMPTY:
			printk(KERN_ALERT "in ioctl: IOCTL_EMPTY");
			filp->private_data = '\0';

			break;
		case IOCTL_SYNC:
			printk(KERN_ALERT "Stream = %s",(char*)filp->private_data);
			break;
		default:
			return EINVAL;
	}
			
	printk(KERN_ALERT "cdata: in cdata_ioctl()\n");
	return 0;
}

static ssize_t cdata_read(struct file *filp, char *buf, 
				size_t size, loff_t *off)
{
	printk(KERN_ALERT "cdata: in cdata_read()\n");
}

static ssize_t cdata_write(struct file *filp, const char *buf, 
				size_t size, loff_t *off)
{
	printk(KERN_ALERT "cdata_write: %s\n", buf);

	if(size == 0) return 0;

	if(copy_from_user(filp->private_data,buf,size))
		return -EFAULT;

	return 0;
}

static int cdata_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "cdata: in cdata_release()\n");
	kfree(filp->private_data);
	return 0;
}

struct file_operations cdata_fops = {	
	owner:		THIS_MODULE,
	open:		cdata_open,
	release:	cdata_release,
	ioctl:		cdata_ioctl,
	read:		cdata_read,
	write:		cdata_write,
};

int my_init_module(void)
{
	register_chrdev(CDATA_MAJOR, "cdata", &cdata_fops);
	printk(KERN_ALERT "cdata module: registered.\n");

	return 0;
}

void my_cleanup_module(void)
{
	unregister_chrdev(CDATA_MAJOR, "cdata");
	printk(KERN_ALERT "cdata module: unregisterd.\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_LICENSE("GPL");
