#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_AUTHOR("Jonathan Sid-Otmane");
MODULE_DESCRIPTION("TP 3 NMV");
MODULE_LICENSE("GPL");

static int how_many;
static char *whom;
module_param(how_many, int, 0700);
module_param(whom, charp, 0700);

static int __init hello(void){
	int i;

	if(how_many<0){
		printk(KERN_ALERT "how_many is not to be toyed with\n");
		return -1;
	}

	for(i=0; i < how_many ; i++)
		printk(KERN_ALERT "(%d) Hello %s\n", i, whom);

	





	return 0;
}
module_init(hello);

static void bye(void){
	printk(KERN_ALERT "See ya, %s!\n", whom);

}

module_exit(bye);
