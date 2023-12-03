#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

MODULE_DESCRIPTION("List current processes");
MODULE_AUTHOR("Ioannis Leontiadis");
MODULE_LICENSE("GPL");

static int __init list_processes_init(void) {
	struct task_struct *p;

	printk("Current process: pid = %d name = %s\n", current->pid,
		   current->comm);

	printk("Process list: \n");
	for_each_process(p) { printk("pid = %4d\t name = %s", p->pid, p->comm); }

	return 0;
}

static void __exit list_processes_exit(void) { printk("Cleanup\n"); }

module_init(list_processes_init);
module_exit(list_processes_exit);
