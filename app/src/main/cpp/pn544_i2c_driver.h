/*
 * pn548_i2c_driver.h
 *
 *  Created on: Feb 20, 2017
 *      Author: root
 */

#ifndef PN544_I2C_DRIVER_H_
#define PN544_I2C_DRIVER_H_

#define PN544_MAGIC	0xE9

/*
 * PN544 power control via ioctl
 * PN544_SET_PWR(0): power off
 * PN544_SET_PWR(1): power on
 * PN544_SET_PWR(2): reset and power on with firmware download enabled
 */
#define PN544_SET_PWR	_IOW(PN544_MAGIC, 0x01, unsigned int)

struct pn544_i2c_platform_data
{
	unsigned int irq_gpio;
	unsigned int ven_gpio;
	unsigned int firm_gpio;	//firmware download mode GPIO4
	const char *clk_src_name;
	unsigned int clkreq_gpio;
	unsigned int clk_src_gpio;
	unsigned int irq_gpio_clk_req;
};





#endif /* PN544_I2C_DRIVER_H_ */


