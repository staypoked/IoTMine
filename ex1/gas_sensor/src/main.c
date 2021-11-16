#include <zephyr.h>
#include <drivers/sensor.h>
#include <device.h>
#include <devicetree.h>

// Important: Lowercase, convert @ to _ and - to _
// gas sensor node path
// check that the path in the DT is correct for the binding
/*
* INVESTIGATE WAYS OF ACCESSING DEVICES IN THE DEVICETREE (DT)
* There are different node identifiers to refer to the DT: DT_NODELABEL(), DT_PATH(), DT_ALIAS(), DT_INST()
* Additionally for a specific parent or child node DT_PARENT() or DT_CHILD() can be used
*/
#define MY_GAS DT_PATH(soc, i2c_40003000, ccs811_5a)
#define MY_GAS_LABEL DT_NODELABEL(ccs811)

void main() {
  printk("Starting main.\n");

#if !DT_NODE_EXISTS(MY_GAS_LABEL)
#error "The node does not exist, something is wrong!"
#endif

#if DT_NODE_HAS_STATUS(MY_GAS, okay)
  const struct device* sensor_device = device_get_binding(DT_LABEL(MY_GAS));
  // As alternative approach I tested with DT_INST() as described above
  //const struct device* sensor_device = device_get_binding(DT_LABEL(DT_INST(0, ams_ccs811)));
#else
#error "Node is disabled"
#endif

  if (sensor_device == NULL) {
    /* No such node, or the node does not have status "okay". */
    printk("\nError: no device found.\n");
    return;
  }

  printk("device is %p, name is %s\n", sensor_device, sensor_device->name);

  if (!device_is_ready(sensor_device)) {
    printk("\nError: Device \"%s\" is not ready; "
           "check the driver initialization logs for errors.\n",
           sensor_device->name);
    return;
  }

  printk("Found device \"%s\", getting sensor data\n", sensor_device->name);

  // Create value structs for all 4 values that can be retrieved from the gas sensor
  struct sensor_value co2, tvoc, voltage, current;
  int err, err_co2, err_tvoc, err_voltage, err_current;
  while(true) {

    // first fetch from the gas sensor 
    err = sensor_sample_fetch(sensor_device);
    if(err){
        printk("Error when sampling gas sensor (err: %d)", err);
    }

    // Get all 4 values from the channels of the gas sensor and check if an error occured
    err_co2 = sensor_channel_get(sensor_device, SENSOR_CHAN_CO2, &co2);
    if(err_co2){
      printk("Error obtaining co2 value (err: %d)", err);
    }
		err_tvoc = sensor_channel_get(sensor_device, SENSOR_CHAN_VOC, &tvoc);
    if(err_tvoc){
      printk("Error obtaining tvoc value (err: %d)", err);
    }
		err_voltage = sensor_channel_get(sensor_device, SENSOR_CHAN_VOLTAGE, &voltage);
    if(err_voltage){
      printk("Error obtaining voltage value (err: %d)", err);
    }
		err_current = sensor_channel_get(sensor_device, SENSOR_CHAN_CURRENT, &current);
    if(err_current){
      printk("Error obtaining current value (err: %d)", err);
    }

    // Print the values and do everything periodically with the specified delay
    printk("Fetched new values after 1 sec: \n");
    printk("CO2: %f \n",  sensor_value_to_double(&co2));
    printk("TVOC: %f \n",  sensor_value_to_double(&tvoc));
    printk("Voltage: %f \n",  sensor_value_to_double(&voltage));
    printk("Current: %f \n",  sensor_value_to_double(&current));
    printk("\n");

    k_msleep(1000);
  }

  return;
}