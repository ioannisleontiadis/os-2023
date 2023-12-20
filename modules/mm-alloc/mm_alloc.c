#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_DESCRIPTION("Allocating 4 kB");
MODULE_AUTHOR("Ioannis Leontiadis");
MODULE_LICENSE("GPL");

static int __init mm_alloc_init(void) {
	size_t req_size = 4096;
	size_t real_size;
	void *address;

	address = kmalloc(req_size, GFP_KERNEL);
	real_size = ksize(address);

	if (address) {
		printk("Allocated %zu bytes from %px to %px\n", real_size, address, address+real_size-1);
		print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 32, 4, address, real_size, false);
	}

	kfree(address);

	return 0;
}

static void __exit mm_alloc_exit(void) { 
	printk("Bye!\n");
}

module_init(mm_alloc_init);
module_exit(mm_alloc_exit);
