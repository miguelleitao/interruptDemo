#include <linux/init.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/io.h>
//#include <linux/irqdomain.h>
#include <linux/interrupt.h>
#include <linux/of.h>
//#include <linux/of_address.h>

//#include <asm/exception.h>
//#include <asm/mach/irq.h>
/*
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,4,0)
MODULE_LICENSE("GPL");
#endif
*/

MODULE_LICENSE("GPL");

#define IRQ_NR  (1)
char my_data[200]; 

long counter = 0;

irqreturn_t my_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
    printk("Interrupt should be handled there\n");
	return (irqreturn_t)0;
}

static int __init
int_init(void)
{
    unsigned int irq;
    unsigned int irqflags;
    int ret;


    irq=IRQ_NR;
    irqflags=IRQF_SHARED; // | IRQF_NO_SUSPEND;

    ret = request_irq(irq, (irq_handler_t)my_interrupt,
            irqflags, "ARCOM Interrupt", my_data);

    if (ret!=0) {
            printk("ERROR: Cannot request IRQ %d", irq);
            printk(" - code %d , EIO %d , EINVAL %d\n", ret, EIO, EINVAL);
    }

    printk("Interrupt Demo Init\n");
    return 0;
}

module_init(int_init);

static void __exit
int_exit(void)
{
    unsigned int irq;
    irq=IRQ_NR;
    free_irq(irq, my_data);
    printk("Interrupt Demo Exit\n");
}

module_exit(int_exit);

