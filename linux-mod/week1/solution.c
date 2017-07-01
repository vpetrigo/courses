#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_AUTHOR("Vladimir Petrigo");
MODULE_LICENSE("Dual BSD/GPL");

int __init solution_init(void)
{
	pr_info("solution: [kernel_mooc] module initialization\n");
}

void __exit solution_exit(void)
{
	pr_info("solution: [kernel_mooc] module exit\n");
}

module_init(solution_init);
module_exit(solution_exit);
