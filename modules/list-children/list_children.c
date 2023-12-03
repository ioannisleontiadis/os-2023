#include <linux/kernel.h>
#include <linux/module.h>

MODULE_DESCRIPTION("List children");
MODULE_AUTHOR("Ioannis Leontiadis");
MODULE_LICENSE("GPL");

#define FORK_CHILDREN_PID 9207
#define TIMER_SECONDS 12

void callback(struct timer_list *data);
DEFINE_TIMER(timer, callback);

static int __init list_children_init(void) {
	mod_timer(&timer, jiffies + TIMER_SECONDS * HZ);
	return 0;
}

static void __exit list_children_exit(void) {
	printk("Cleanup!\n");
	del_timer(&timer);
}

void callback(struct timer_list *data) {
	struct task_struct *task;
	struct task_struct *child;

	rcu_read_lock();
	task = pid_task(find_pid_ns(FORK_CHILDREN_PID, &init_pid_ns), PIDTYPE_PID);

	if (task) {
		printk("Children of %s:", task->comm);
		list_for_each_entry(child, &task->children, sibling) {
			printk("pid = %d\n", child->pid);
		}
	}

	rcu_read_unlock();
	mod_timer(&timer, jiffies + TIMER_SECONDS * HZ);
}

module_init(list_children_init);
module_exit(list_children_exit);
