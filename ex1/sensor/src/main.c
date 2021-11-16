#include <zephyr.h>
#include <drivers/sensor.h>
#include <device.h>
#include <devicetree.h>

// Important: Lowercase, convert @ to _ and - to _
// search and get the specific sensor for the temp: hts221
#define MY_TEMPERATURE DT_PATH(soc, i2c_40003000, hts221_5f)
#define MY_TEMPERATURE_LABEL DT_NODELABEL(hts221)

void main() {
  printk("Starting main.\n");

#if !DT_NODE_EXISTS(MY_TEMPERATURE_LABEL)
#error "The node does not exist, something is wrong!"
#endif

// bind the device from the DT
#if DT_NODE_HAS_STATUS(MY_TEMPERATURE, okay)
  const struct device* sensor_device = device_get_binding(DT_LABEL(MY_TEMPERATURE));
#else
#error "Node is disabled"
#endif

  if (sensor_device == NULL) {
    /* No such node, or the node does not have status "okay". */
    printk("\nError: no device found.\n");
    return;
  }

  if (!device_is_ready(sensor_device)) {
    printk("\nError: Device \"%s\" is not ready; "
           "check the driver initialization logs for errors.\n",
           sensor_device->name);
    return;
  }

  printk("Found device \"%s\", getting sensor data\n", sensor_device->name);

  struct sensor_value temp_value;
  int err;
  while(true) {
    // first sample fetch from the channel and the use sensor_channel_get to the get temp_value
    err = sensor_sample_fetch_chan(sensor_device, SENSOR_CHAN_AMBIENT_TEMP);
    if(err){
      printk("Error when sampling sensor (err: %d)", err);
    }

    err = sensor_channel_get(sensor_device, SENSOR_CHAN_AMBIENT_TEMP,
                             &temp_value);
    if(err){
      printk("Error obtaining sensor value (err: %d)", err);
    }

    // get the value periodically with k_msleep
    printk("Temperature: %f \n",  sensor_value_to_double(&temp_value));
    k_msleep(1000);
  }

  return;
}