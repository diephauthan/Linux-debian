#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>

#undef	pr_fmt
#define DEV_MEM_SIZE 512
#define pr_fmt(fmt) "%s :" fmt,__func__

/* pseudo device's memory */
char device_buffer[DEV_MEM_SIZE];

/*this holds the device number*/
dev_t device_number;

/*Cdev variable*/
struct cdev pcd_cdev;

loff_t pcd_lseek(struct file *filp, loff_t off, int whence)
{
	return 0;
}

ssize_t pcd_read(struct file *flip, char __user *buff, size_t count, loff_t *f_pos)
{
	return 0;
}
ssize_t pcd_write(struct file *flip, const char __user *buff, size_t count, loff_t *f_pos)
{
	return 0;
}
        
int pcd_open(struct inode *inode, struct file *flip)
{
	return 0;
}
int pcd_release(struct inode *inode, struct file *flip)
{
	return 0;
}


/*file operations of the driver*/
struct file_operations pcd_fops =
{
	.open =pcd_open,
	.write = pcd_write,
	.read = pcd_read,
	.llseek = pcd_lseek,
	.release = pcd_release,
	.owner = THIS_MODULE
};

struct class *class_pcd;

struct device *device_pcd;

static int __init pcd_driver_init(void)
{
	/*1. Dynamically allocate a device number */
	alloc_chrdev_region(&device_number,0,1,"pcd_devices");

	pr_info("device number <major>:<minor> = %d:%d\n",MAJOR(device_number),MINOR(device_number));

	/*2. init the cdev structure with fops*/
	cdev_init(&pcd_cdev, &pcd_fops);

	/*3. Register a device (cdev) structure with VFS*/
	pcd_cdev.owner = THIS_MODULE;
	cdev_add(&pcd_cdev, device_number,1);

	/*4. create device class under /sys/class/ */
	class_pcd = class_create(THIS_MODULE,"pcd_class");
	
	/*5. populate the sysfs with device information*/
	device_pcd = device_create(class_pcd,NULL,device_number,NULL,"pcd");

	pr_info("Module init was successful\n");
	return 0;
}

static void __exit pcd_driver_cleanup(void)
{

}

module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("A pseudo character driver");
