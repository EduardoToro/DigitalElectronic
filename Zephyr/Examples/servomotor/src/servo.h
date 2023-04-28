/*
 * =====================================================================================
 *
 *       Filename:  pwm_servo.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/01/2022 02:40:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifdef PWM_SERVO_H_
#define PWM_SERVO_H_
#include <zephyr/types.h>
#include <zephyr/device.h>

typedef int (*servo_api_on)(const struct device *dev, uint32_t led);

__subsystem struct servo_driver_api {
	/* Mandatory callbacks. */
	servo_api_on on;
	/* led_api_off off; */
	/* Optional callbacks. */
	/* led_api_blink blink; */
	/* led_api_get_info get_info; */
	/* led_api_set_brightness set_brightness; */
	/* led_api_set_color set_color; */
	/* led_api_write_channels write_channels; */
};

__syscall int servo_on(const struct device *dev, uint32_t servo);

static inline int z_impl_servo_on(const struct device *dev, uint32_t servo)
{
	const struct servo_driver_api *api =
		(const struct servo_driver_api *)dev->api;

	return api->on(dev, servo);
}

#endif
