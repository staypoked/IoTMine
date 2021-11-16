#include <zephyr.h>

int main() {
	// Additionally install the rtt j-link viewer of jegger to see the output
	printk("Welcome, starting system.\n");

	// CONFIG_USE_SEGGER_RTT has to be enabled in the prj.conf file to be useable on the thingy 52
	while(true){
		printk("Thingy52 is running.\n");
		k_msleep(1000);
	}
}
