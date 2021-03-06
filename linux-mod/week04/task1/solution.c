#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/errno.h>
#include <linux/stat.h>
#include <linux/printk.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/sort.h>
#include <linux/string.h>


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Vladimir Petrigo");

#define TOPDIR_NAME "my_kobject"
#define ARR_SIZE 5
#define PREDEF_MAJOR 240
#define PREDEF_MINOR 0
#define DEV_NAME "solution_node"
#define PRINTBUF_SIZE 128
#define STRING_CONT_MUL	8

struct solution_dev {
	struct kobj_attribute sd_file;
	unsigned read_ops_counter;
	unsigned write_ops_counter;
};

struct solution_char_dev {
	struct cdev s_cdev;
	dev_t id;
	ssize_t access_counter;
	ssize_t write_bytes;
};

#define to_solution_cdev(x) container_of((x), struct solution_char_dev, s_cdev)

static int a = 0;
module_param(a, int, S_IRUGO);
static int b = 0;
module_param(b, int, S_IRUGO);
static int c[ARR_SIZE];
module_param_array(c, int, NULL, S_IRUGO);
static char *node_name = "solution";
module_param(node_name, charp, S_IRUGO);

static struct kobject *top_dir = NULL;

struct string_container {
	const char **storage;
	size_t size;
	size_t capacity;
};

static struct string_container modules_name = {
	.storage = NULL,
	.size = 0,
	.capacity = 0
};

static int init_string_container(struct string_container *sc)
{
	int retval = 0;

	sc->storage = kmalloc(sizeof(const char *) * STRING_CONT_MUL, GFP_KERNEL);
	
	if (!sc->storage)
	{
		pr_debug("Cannot allocate memory for string container\n");
		retval = -ENOMEM;
		goto end;
	}

	sc->size = 0;
	sc->capacity = STRING_CONT_MUL;

end:
	return retval;
}

static int realloc_string_container(struct string_container *sc)
{
	int retval = 0;

	if (sc->storage)
	{
		size_t new_capacity = sc->capacity * STRING_CONT_MUL;
		const char **new_storage = 
			kmalloc(sizeof(const char *) * new_capacity, GFP_KERNEL);

		if (!new_storage)
		{
			retval = -ENOMEM;
			goto end;
		}

		memmove(new_storage, sc->storage, sc->size * sizeof(const char *));
		kfree(sc->storage);
		sc->storage = new_storage;
		sc->capacity = new_capacity;
	}

end:
	return retval;
}

static int string_container_add(struct string_container *sc, const char *el)
{
	int retval = 0;

	if (sc->size == sc->capacity)
	{
		retval = realloc_string_container(sc);

		if (retval != 0)
			goto end;
	}
	
	sc->storage[sc->size++] = el;
end:
	return retval;
}

static int string_container_free(struct string_container *sc)
{
	if (sc->storage)
	{
		kfree(sc->storage);
		sc->storage = NULL;
	}

	sc->size = 0;
	sc->capacity = 0;

	return 0;
}

int string_compare(const void *a, const void *b)
{
	return strcmp(*((const char **) a), *((const char **) b));
}

void string_swap(void *a, void *b, int size)
{
	const char **a_p = a;
	const char **b_p = b;

	const char *tmp = *a_p;
	*a_p = *b_p; 
	*b_p = tmp;
}

ssize_t sol_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	ssize_t retval = 0;
	pr_debug("solution: call show\n");
	
	for (size_t i = 0; i < modules_name.size; ++i)
	{
		retval += scnprintf(buf + retval, PAGE_SIZE,
				"%s\n", modules_name.storage[i]);

		if (retval >= PAGE_SIZE)
			break;
	}

	return retval;
}

ssize_t sol_store(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	struct solution_dev *sdev_p = container_of(attr, struct solution_dev, sd_file);

	++sdev_p->write_ops_counter;
	pr_debug("solution: call store\n");
	return 0;
}

ssize_t solution_read(struct file *filp, char __user *to, size_t size, loff_t *pos)
{
	char buf[PRINTBUF_SIZE];
	struct solution_char_dev *sdev_p = to_solution_cdev(filp->private_data);
	int retval = 0;

	if (*pos != 0)
		goto end;

	pr_debug("solution: read from file\n");
	pr_debug("solution: major id %d\n", MAJOR(sdev_p->id));
	retval = scnprintf(buf, PRINTBUF_SIZE, "%d\n", MAJOR(sdev_p->id));

	if (copy_to_user(to, buf, retval) != 0)
		retval = -EFAULT;

	*pos += retval;
end:
	return retval;
}

ssize_t solution_write(struct file *filp, const char __user *from, size_t size, loff_t *pos)
{
	struct solution_char_dev *sdev_p = to_solution_cdev(filp->private_data);	

	sdev_p->write_bytes += size;

	return size;
}

int solution_release(struct inode *inode, struct file *filp)
{
	return 0;
}

int solution_open(struct inode *inode, struct file *filp)
{
	struct solution_char_dev *sdev_p = container_of(inode->i_cdev, struct solution_char_dev, s_cdev); 

	pr_debug("solution: open file\n");
	filp->private_data = sdev_p;
	++sdev_p->access_counter;

	return 0;
}

static struct solution_dev sdev = {
	.read_ops_counter = 0,
	.write_ops_counter = 0,
	.sd_file = __ATTR(my_sys, S_IRUGO | S_IWUSR, sol_show, sol_store)
};

static struct solution_char_dev sdev_char = {
	.id = MKDEV(PREDEF_MAJOR, PREDEF_MINOR),
	.write_bytes = 0,
	.access_counter = 0
};

static struct class *solution_class;

static struct file_operations solution_fops = {
	.owner = THIS_MODULE,
	.read = solution_read,
	.write = solution_write,
	.open = solution_open,
	.release = solution_release
};

static int modules_name_list(void)
{
	struct list_head *ptr;
	struct list_head *head = THIS_MODULE->list.prev;
	int retval = 0;

	retval = init_string_container(&modules_name);

	if (retval != 0)
		goto end;

	list_for_each(ptr, head)
	{
		struct module *mod = list_entry(ptr, struct module, list);

		if (string_container_add(&modules_name, (const char *) mod->name) != 0)
		{
			pr_debug("Cannot add element <%s> to container\n", mod->name);
			retval = -EACCES;
			goto end;
		}
	}

	sort(modules_name.storage, modules_name.size, 
			sizeof(const char *), string_compare, string_swap);
	for (size_t i = 0; i < modules_name.size; ++i)
		pr_debug("mod[%zu]: %s\n", i, modules_name.storage[i]);

end:
	return retval;
}

static int __init solution_init(void)
{
	int retval = 0;

	retval = modules_name_list();

	if (retval != 0)
	{
		string_container_free(&modules_name);
		goto fail;
	}

	top_dir = kobject_create_and_add(TOPDIR_NAME, kernel_kobj);

	if (!top_dir) {
		retval = -ENOMEM;
		goto fail;
	}

	retval = sysfs_create_file(top_dir, &sdev.sd_file.attr);

	if (retval != 0) {
		kobject_put(top_dir);
		goto fail;
	}

	retval = alloc_chrdev_region(&sdev_char.id, 0, 1, node_name);

	if (retval != 0) {
		pr_debug("Cannot get allocate chrdev\n");
		goto fail;
	}

	pr_debug("solution: init cdev\n");
	cdev_init(&sdev_char.s_cdev, &solution_fops);
	sdev_char.s_cdev.owner = THIS_MODULE;
	retval = cdev_add(&sdev_char.s_cdev, sdev_char.id, 1);

	if (retval != 0) {
		pr_debug("Error %d adding node", retval);
		goto fail;
	}

	solution_class = class_create(THIS_MODULE, node_name);
	device_create(solution_class, NULL, sdev_char.id, "%s", node_name);

fail:
	return retval;
}

static void __exit solution_exit(void)
{
	kobject_put(top_dir);
	device_destroy(solution_class, sdev_char.id);
	class_destroy(solution_class);
	cdev_del(&sdev_char.s_cdev);
	unregister_chrdev_region(sdev_char.id, 1);
	string_container_free(&modules_name);
}

module_init(solution_init);
module_exit(solution_exit);
