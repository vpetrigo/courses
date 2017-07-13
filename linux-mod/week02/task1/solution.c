#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/errno.h>
#include <linux/stat.h>
#include <linux/printk.h>

MODULE_AUTHOR("Vladimir Petrigo");
MODULE_LICENSE("Dual BSD/GPL");

#define TOPDIR_NAME "my_kobject"

struct solution_dev {
	unsigned read_ops_counter;
	unsigned write_ops_counter;
};

static struct solution_dev sdev = {
	.read_ops_counter = 0,
	.write_ops_counter = 0
};

static struct kobject *top_dir = NULL;

ssize_t sol_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	++sdev.read_ops_counter;
	pr_debug("solution: call show\n");
	return scnprintf(buf, PAGE_SIZE, "%u\n", sdev.read_ops_counter);
}

ssize_t sol_store(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	pr_debug("solution: call store\n");
	return 0;
}

static const struct kobj_attribute sd_file = __ATTR(my_sys, S_IRUGO | S_IWUSR, sol_show, sol_store);

static int __init solution_init(void)
{
	int retval = 0;

	top_dir = kobject_create_and_add(TOPDIR_NAME, kernel_kobj);
	
	if (!top_dir)
		return -ENOMEM;

	retval = sysfs_create_file(top_dir, &sd_file.attr);

	if (retval != 0)
		kobject_put(top_dir);

	return retval;
}

static void __exit solution_exit(void)
{
	kobject_put(top_dir);
}

module_init(solution_init);
module_exit(solution_exit);
