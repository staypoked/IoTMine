#include <zephyr.h>

int main() {
	// Additionally install the rtt j-link viewer of jegger to see the output
	printk("Welcome, starting system.\n");

	while(true){
		printk("Thingy52 is running.\n");
		k_msleep(500);
	}
}
