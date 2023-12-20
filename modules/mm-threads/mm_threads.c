#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <asm/atomic.h>
#define TIMER_SECONDS 10

MODULE_DESCRIPTION("Number of users sharing the same address space");
MODULE_AUTHOR("Ioannis Leontiadis");
MODULE_LICENSE("GPL");

static int pid;
module_param(pid, int, 0);

void callback(struct timer_list *data);
DEFINE_TIMER(timer, callback);

static int __init mm_threads_init(void) {
	mod_timer(&timer, jiffies + TIMER_SECONDS * HZ);
	return 0;
}

static void __exit mm_threads_exit(void) {
	printk("Cleanup!\n");
	del_timer(&timer);
}

void callback(struct timer_list *data) {
	struct task_struct *task;

	rcu_read_lock();
	task = pid_task(find_pid_ns(pid, &init_pid_ns), PIDTYPE_PID);

	if (task) {
		int users = atomic_read(&task->mm->mm_users);
		printk("Address space of pid = %d | users = %d", task->pid, users);
	}

	rcu_read_unlock();
	mod_timer(&timer, jiffies + TIMER_SECONDS * HZ);
}

module_init(mm_threads_init);
module_exit(mm_threads_exit);
