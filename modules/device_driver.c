#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEV_MAJOR 42
#define DEV_MINOR 0
#define MAX_DEV_MINORS 2
#define MODULE_NAME "device_driver"
#define MESSAGE	"Hello!\n"
#define BUFFER_SIZE 4096

MODULE_DESCRIPTION("Character Device Driver");
MODULE_AUTHOR("Ioannis Leontiadis");
MODULE_LICENSE("GPL");

struct device_data {
	struct cdev cdev;
	char buffer[BUFFER_SIZE];
	size_t size;
	atomic_t access;
};

struct device_data dev[MAX_DEV_MINORS];

static int device_open(struct inode *inode, struct file *file)
{
	struct device_data *data;

	data = container_of(inode->i_cdev, struct device_data, cdev); 
	file->private_data = data;

	if (atomic_cmpxchg(&data->access, 0, 1) != 0) {
		pr_info("Device busy.\n");
		return -EBUSY;
	}

	pr_info("Device opened.\n");
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	struct device_data *data =
		(struct device_data *) file->private_data;

	atomic_set(&data->access, 0);

	pr_info("Device released.\n");
	return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset)
{
	struct device_data *data =
		(struct device_data *) file->private_data;

	ssize_t to_read = min((size_t)(data->size - *offset), size);

	if (to_read <= 0) {
		return 0;
	}

    	pr_info("[READ] Size: %lu Offset: %lld", size, *offset);

	if (copy_to_user(user_buffer, data->buffer + *offset, to_read)) {
		return -EFAULT;
	}

	*offset += to_read;

	return to_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t size, loff_t *offset)
{
	struct device_data *data =
		(struct device_data *) file->private_data;

	ssize_t to_write = min((size_t)(BUFFER_SIZE - *offset), size);

	if (to_write <= 0) {
		return 0;
	}

    	pr_info("[WRITE] Size: %lu Offset: %lld", size, *offset);

	if (copy_from_user(data->buffer + *offset, user_buffer, to_write)) {
		return -EFAULT;
	}

	*offset += to_write;
	data->size = *offset;
	
    return to_write;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	.release = device_release,
	.read = device_read,
	.write = device_write
};

static int device_driver_init(void)
{
	int err = register_chrdev_region(MKDEV(DEV_MAJOR, 0), MAX_DEV_MINORS, MODULE_NAME);

	pr_info("Devices rigistered.\n");

	if (err != 0) {
		return err;
	}

	for (int i = 0; i < MAX_DEV_MINORS; i++) {
		memcpy(dev[i].buffer, MESSAGE, sizeof(MESSAGE));
		dev[i].size = sizeof(MESSAGE);

		atomic_set(&dev[i].access, 0);

		cdev_init(&dev[i].cdev, &fops);
		cdev_add(&dev[i].cdev, MKDEV(DEV_MAJOR, i), 1);
	}

	return 0;
}

static void device_driver_exit(void)
{
	for (int i = 0; i < MAX_DEV_MINORS; i++) {
		cdev_del(&dev[i].cdev);
		
	}

	unregister_chrdev_region(MKDEV(DEV_MAJOR, 0), MAX_DEV_MINORS);

	pr_info("Devices unregistered.\n");
}

module_init(device_driver_init);
module_exit(device_driver_exit);
