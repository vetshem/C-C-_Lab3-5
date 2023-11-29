#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#define BUFSIZE  100


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Liran B.H");

static int irq=20;
module_param(irq,int,0660);


static struct proc_dir_entry *ent;
 int i;
static int is_prime_number(int n) {
    if (n <= 1) {
        return 0;  // Not a prime number
    }

    for (i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;  // Not a prime number
        }
    }
    return 1;  // Prime number
}


static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos)
{
    int num, i;
    char buf[BUFSIZE];

    if (*ppos > 0 || count > BUFSIZE)
        return -EFAULT;

    if (copy_from_user(buf, ubuf, count))
        return -EFAULT;

    num = sscanf(buf, "%d", &i);

    if (num != 1)
        return -EFAULT;

    if (is_prime_number(i)) {
        irq = i;
        printk(KERN_ALERT "mydev: Updated irq value to %d (prime)\n", irq);
    } else {
        printk(KERN_ALERT "mydev: The number %d is not prime. Ignoring.\n", i);
    }

    *ppos = count;
    return count;
}

static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos)
{
	char buf[BUFSIZE];
	int len=0;
	if(*ppos > 0 || count < BUFSIZE)
		return 0;
	len += sprintf(buf,"irq = %d\n",irq);

	if(copy_to_user(ubuf,buf,len))
		return -EFAULT;
	*ppos = len;
	return len;
}

static struct file_operations myops =
{
	.owner = THIS_MODULE,
	.read = myread,
	.write = mywrite,
};

static int simple_init(void)
{
	ent=proc_create("mydev",0660,NULL,&myops);
	printk(KERN_ALERT "hello...\n");
	return 0;
}

static void simple_cleanup(void)
{
	proc_remove(ent);
	printk(KERN_WARNING "bye ...\n");
}

module_init(simple_init);
module_exit(simple_cleanup);
