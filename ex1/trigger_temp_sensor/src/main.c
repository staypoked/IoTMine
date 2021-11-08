#include <zephyr.h>
#include <drivers/sensor.h>
#include <device.h>
#include <devicetree.h>

// Important: Lowercase, convert @ to _ and - to _
#define MY_TEMPERATURE DT_PATH(soc, i2c_40003000, hts221_5f)
#define MY_TEMPERATURE_LABEL DT_NODELABEL(hts221)

static void trigger_handler(const struct device *dev,
			    const struct sensor_trigger *trigger)
{
	//ARG_UNUSED(dev);
	//ARG_UNUSED(trigger);
  printk("The room is getting to hot, please cool down.");
}

static void get_sample(const struct device *dev){
  struct sensor_value temp_value;
  int err;
  
  err = sensor_sample_fetch_chan(dev, SENSOR_CHAN_AMBIENT_TEMP);
  if(err){
    printk("Error when sampling sensor (err: %d)", err);
  }

  err = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP,
                            &temp_value);
  if(err){
    printk("Error obtaining sensor value (err: %d)", err);
  }

  printk("Temperature: %f \n",  sensor_value_to_double(&temp_value));
}

void main() {
  printk("Starting main.\n");

#if !DT_NODE_EXISTS(MY_TEMPERATURE_LABEL)
#error "The node does not exist, something is wrong!"
#endif

#if DT_NODE_HAS_STATUS(MY_TEMPERATURE, okay)
  //const struct device* sensor_device = DEVICE_DT_GET(MY_TEMPERATURE);
  //const struct device* sensor_device = device_get_binding("HTS221");
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

  // set threshold where val1 is before the decimal and val2 is after the decimal
  struct sensor_value attr = {
		.val1 = 27,
		.val2 = 0,
	};

  if (IS_ENABLED(CONFIG_HTS221_TRIGGER)){
    printk("HTS221 trigger is enabled and will be set to specified upper threshold.\n");
    
    struct sensor_trigger trig = {
      //.type = SENSOR_TRIG_THRESHOLD,
      .type = SENSOR_TRIG_DATA_READY,
      .chan = SENSOR_CHAN_AMBIENT_TEMP,
    };

    if (sensor_trigger_set(sensor_device, &trig, trigger_handler)) {
      printk("Could not set trigger\n");
      return;
    }

    int ret = sensor_attr_set(sensor_device, SENSOR_CHAN_AMBIENT_TEMP,
            SENSOR_ATTR_UPPER_THRESH, &attr);
            
    if (ret < 0) {
      printk("Could not set threshold as error occured:\"%d\" \n", ret);
      return;
    }

  }

  printk("Trigger set with upper threshold of: \"%d\".\"%d\" \n", attr.val1, attr.val2);
  
  while(true) {
    get_sample(sensor_device);
    k_msleep(1000);
  }

  return;
}