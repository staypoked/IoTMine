#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

// time between switches on/off in millisecond
#define DELAY 1000

// get a handle on the device-node with the name led0 in the devicetree
// more information on how to access the device tree from C is available at
// https://docs.zephyrproject.org/latest/guides/dts/api-usage.html
#define LED_NODE DT_ALIAS(led0)
#define LED_GREEN_NODE DT_NODELABEL(led1)
// extended to use all three colors
#define LED_BLUE_NODE DT_NODELABEL(led2)

// check if the device is set up properly (led0, the red one)
#if DT_NODE_HAS_STATUS(LED_NODE, okay)
// get the label in the device tree of the device node
#define LED0	DT_GPIO_LABEL(LED_NODE, gpios)
// get the PIN-property of the device node
#define PIN	DT_GPIO_PIN(LED_NODE, gpios)
// get the FLAGS-property of the gpio device node with index 0
#define FLAGS	DT_GPIO_FLAGS(LED_NODE, gpios)
#else
// in case the node is not "okay", i.e., the board does not support led
#error "The alias in the devicetree is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif

// check if the device is set up properly (led1, the green one)
#if DT_NODE_HAS_STATUS(LED_GREEN_NODE, okay)
// get the label in the device tree of the device node
#define LED1	DT_GPIO_LABEL(LED_GREEN_NODE, gpios)
// get the PIN-property of the device node
#define PIN1	DT_GPIO_PIN(LED_GREEN_NODE, gpios)
// you can also explicitly provide the index (here 0)
#define FLAGS1 DT_GPIO_FLAGS_BY_IDX(LED_GREEN_NODE, gpios, 0)
#else
// in case the node is not "okay", i.e., the board does not support led
#error "The node in the devicetree is not defined"
#define LED1	""
#define PIN1	0
#define FLAGS1	0
#endif

// check if the device is set up properly (led2, the blue one)
#if DT_NODE_HAS_STATUS(LED_BLUE_NODE, okay)
// get the label in the device tree of the device node
#define LED2	DT_GPIO_LABEL(LED_BLUE_NODE, gpios)
// get the PIN-property of the device node
#define PIN2	DT_GPIO_PIN(LED_BLUE_NODE, gpios)
// get the FLAGS-property of the gpio device node with index 0
#define FLAGS2	DT_GPIO_FLAGS(LED_BLUE_NODE, gpios)
#else
// in case the node is not "okay", i.e., the board does not support led
#error "The alias in the devicetree is not defined"
#define LED2	""
#define PIN2	0
#define FLAGS	0
#endif


void main(void)
{
        // struct for the led device (red)
	const struct device *red_led_device;
        const struct device *green_led_device;
        const struct device *blue_led_device;
        // flag to memorize the state of the led
	//bool led_red = true;
        // store potential error values
	int ret;
        // set specific state for each color (RED is 0, GREEN is 1 and BLUE is 2)
        int state = 0; 

        // get binding for the led device based on the device tree label
	red_led_device = device_get_binding(LED0);
        green_led_device = device_get_binding(LED1);
        blue_led_device = device_get_binding(LED2);
	if (red_led_device == NULL || green_led_device == NULL || blue_led_device == NULL) {
          // something went wrong with getting the device struct from the
          // device tree
		return;
	}

        // configure the led_device at pin PIN as output and initialize it to a
        // logical 1
        // all gpio-flags are described at https://docs.zephyrproject.org/latest/reference/peripherals/gpio.html
	ret = gpio_pin_configure(red_led_device, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	}
        // also configure the green led device at PIN1 for output and
        // initialize it to a logical 0
        ret = gpio_pin_configure(green_led_device, PIN1, GPIO_OUTPUT_INACTIVE |
                                                         FLAGS1);
        if (ret < 0) {
          return;
        }

        // Blue led configuration on PIN2 for output and initialize it to a logical 0
        ret = gpio_pin_configure(green_led_device, PIN2, GPIO_OUTPUT_INACTIVE |
                                                         FLAGS2);
        if (ret < 0) {
          return;
        }

        // After setting everything up, I 
        // make them blink periodically
	while (1) {
		// gpio_pin_set(red_led_device, PIN, (int)led_red);
                // gpio_pin_set(green_led_device, PIN1, 1-(int)led_red);
                // led_red = !led_red;
		if (state == 0){
                        gpio_pin_set(red_led_device, PIN, true);
                        // do not forget to set the other pins back to false
                        gpio_pin_set(green_led_device, PIN1, false);
                        gpio_pin_set(blue_led_device, PIN2, false);
                } else if (state == 1) {
                        gpio_pin_set(red_led_device, PIN, false);
                        gpio_pin_set(green_led_device, PIN1, true);
                        gpio_pin_set(blue_led_device, PIN2, false);
                } else {
                        gpio_pin_set(red_led_device, PIN, false);
                        gpio_pin_set(green_led_device, PIN1, false);
                        gpio_pin_set(blue_led_device, PIN2, true);
                }
                
                state++;
                if (state > 2) {
                        state = 0;
                }                
                
                k_msleep(DELAY);
	}
}
