#include <linux/init.h>
#include <linux/module.h> // THIS_MODULE
#include <linux/kernel.h> // Kernel cosas
#include <linux/fs.h>     // File operations
#include <linux/cdev.h>   // Char devices
#include <linux/device.h> // Nodos filesystem
#include <linux/uaccess.h> // copy_to_user
#include <linux/slab.h>    // kmalloc
#include <linux/random.h>  // get_random_bytes

static int upper_bound = -1;

static ssize_t azar_read(struct file *filp, char __user *data, size_t size, loff_t *offset) {
    printk(KERN_ALERT "upper: %d", upper_bound);
    if(upper_bound == -1) return -EPERM;
    char* string_res = kmalloc(sizeof(char) * size, NULL);
    unsigned int num_azar;
    get_random_bytes(&num_azar, sizeof(num_azar));
    num_azar = num_azar % upper_bound;
    int size_string = snprintf(string_res, size, "%d\n", num_azar);
    copy_to_user(data, string_res, size_string);
    int res_size = sizeof(string_res);
    kfree(string_res);
    return size;
}

static ssize_t azar_write(struct file *filp, const char __user *data, size_t size, loff_t *offset) {
    int res = size;
    char* to = kmalloc(sizeof(char) * size + 1, NULL);
    copy_from_user(to, data, size);
    to[size] = 0;
    if(kstrtoint(to, 10, &upper_bound) != 0) {
        res = -EPERM;
    }
    kfree(to);
    return res;
}

static struct file_operations azar_fops = {
  .owner = THIS_MODULE,
  .read = azar_read,
  .write = azar_write,
};

static dev_t azar_devno;
static struct cdev azar_cdev;
static struct class *azar_class;

static int __init azar_init(void) {
    cdev_init(&azar_cdev, &azar_fops);
    alloc_chrdev_region(&azar_devno, 0, 1, "SO-azar");
    cdev_add(&azar_cdev, azar_devno, 1);

    azar_class = class_create(THIS_MODULE, "azar");
    device_create(azar_class, NULL, azar_devno, NULL, "azar");

    printk(KERN_ALERT "Loading module 'azar'\n");
    return 0;
}

static void __exit azar_exit(void) {
    printk(KERN_ALERT "Unloading module 'azar'\n");

    device_destroy(azar_class, azar_devno);
    class_destroy(azar_class);

    unregister_chrdev_region(azar_devno, 1);
    cdev_del(&azar_cdev);
}

module_init(azar_init);
module_exit(azar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Generador de números al azar");
