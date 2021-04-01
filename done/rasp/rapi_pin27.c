#include <linux/fs.h>		// declare file_operations
#include <linux/module.h>	// declare module_init, module_exit
#include <linux/init.h>		// declare __init __exit
#include <linux/device.h>	// declare class device
#include <linux/types.h>	// declare for dev_t (device no.)
#include <linux/uaccess.h>	// header copy_from_user
#include <asm/io.h>		// header of ioremap iounmap

static struct class *pin27_class;
static struct device *pin27_class_dev;

static dev_t devno;		// device no.
static int major = 123;		// device major no.
static int minor = 0;		// device minor no.
static char *module_name = "pin27";	// name of module

volatile unsigned int *GPFSEL0 = NULL;
volatile unsigned int *GPSET0  = NULL;
volatile unsigned int *GPCLR0 = NULL;

static int pin27_open(struct inode *inode, struct file *file)
{
	printk("pin27_open\n");

	// GPIO function select pin 4, (14-12) : OUTPUT: 001
	*GPFSEL0 &= ~(0x6 << 21);
	*GPFSEL0 |=  (0x1 << 21);

	return 0;
}

static int pin27_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	printk("pin27_read\n");

	return 0;
}

static ssize_t pin27_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	printk("pin27_write\n");

	int userCmd;
	copy_from_user(&userCmd, buf, count);

	if(userCmd == 1)
	{
		printk("set 1 \n");
		*GPSET0 |= 0x1 << 27;

	}else if(userCmd == 0) {
		printk("set 0 \n");
		*GPCLR0 |= 0x1 << 27;

	} else {
		printk("unknow \n");
	}

	return 0;
}

static struct file_operations pin27_fops = {
	.owner = THIS_MODULE,
	.open  = pin27_open,
	.write = pin27_write,
	.read  = pin27_read,
};

int __init pin27_drv_init(void) // execute when insmod() is called
{
	printk("insmod driver pin27 success \n");

	int ret;
	devno = MKDEV(major, minor); // 2. create device no.
	// regist driver - tell kernel to join this driver into the driver chain
	ret = register_chrdev(major, module_name, &pin27_fops);

	// same as: sudo mknod myfirstdemo c 231 0
	pin27_class = class_create( THIS_MODULE, "myfirstdemo");	// create class under /sys/class/
	pin27_class_dev = device_create( pin27_class, NULL, devno, NULL, module_name );	// create device under /dev


	GPFSEL0 = (volatile unsigned int *) ioremap(0x3f200008, 4);
	GPSET0  = (volatile unsigned int *) ioremap(0x3f20001C, 4);
	GPCLR0  = (volatile unsigned int *) ioremap(0x3f200028, 4);

	return 0;
}

void __exit pin27_drv_exit(void)
{

	iounmap(GPCLR0);
	iounmap(GPSET0);
	iounmap(GPFSEL0);

	device_destroy(pin27_class, devno);
	class_destroy(pin27_class);
	unregister_chrdev( major, module_name);
}

module_init(pin27_drv_init);
module_exit(pin27_drv_exit);
MODULE_LICENSE("GPL v2");

