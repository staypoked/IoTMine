#include <device.h>
#include <toolchain.h>

/* 1 : /soc/clock@40000000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_clock_40000000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 2 : /soc/uart@40002000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_uart_40002000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 3 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_sys_init_sys_clock_driver_init0[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 4 : /soc/gpio@50000000:
 * - (/soc)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_gpio_50000000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 5 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_vdd_pwr_ctrl_init[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 6 : /soc/i2c@40004000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_40004000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 7 : /soc/i2c@40003000:
 * - (/soc)
 * - (/soc/interrupt-controller@e000e100)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_40003000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 8 : /soc/i2c@40003000/sx1509b@3e:
 * - /vdd-pwr-ctrl
 * - /soc/i2c@40003000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_40003000_S_sx1509b_3e[] = { 7, 13, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 9 : /ccs-pwr-ctrl:
 * - (/)
 * - /soc/i2c@40003000/sx1509b@3e
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_ccs_pwr_ctrl[] = { 8, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 10 : /mic-pwr-ctrl:
 * - (/)
 * - /soc/i2c@40003000/sx1509b@3e
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_mic_pwr_ctrl[] = { 8, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 11 : /mpu-pwr-ctrl:
 * - (/)
 * - /soc/i2c@40003000/sx1509b@3e
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_mpu_pwr_ctrl[] = { 8, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 12 : /spk-pwr-ctrl:
 * - (/)
 * - /soc/gpio@50000000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_spk_pwr_ctrl[] = { 4, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 13 : /vdd-pwr-ctrl:
 * - (/)
 * - /soc/gpio@50000000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_vdd_pwr_ctrl[] = { 4, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 14 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_ccs_vdd_pwr_ctrl_init[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 15 : /soc/i2c@40003000/hts221@5f:
 * - /vdd-pwr-ctrl
 * - /soc/gpio@50000000
 * - /soc/i2c@40003000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_i2c_40003000_S_hts221_5f[] = { 7, 13, 4, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };
