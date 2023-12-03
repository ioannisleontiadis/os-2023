#include <linux/kernel.h>
#include <linux/module.h>

MODULE_DESCRIPTION("My first kernel module");
MODULE_AUTHOR("Ioannis Leontiadis");
MODULE_LICENSE("GPL");

static int __init hello_world_init(void) {
	printk("Hello world!\n");
	return 0;
}

static void __exit hello_world_exit(void) { printk("Bye world!\n"); }

module_init(hello_world_init);
module_exit(hello_world_exit);
