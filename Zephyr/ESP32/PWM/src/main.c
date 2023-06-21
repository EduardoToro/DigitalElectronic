#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>


#define NUM_STEPS 3U
#define SLEEP_DELTA_MSEC 1000U

static const struct pwm_dt_spec fanding_led = PWM_DT_SPEC_GET(DT_NODELABEL(fanding_led)); 

static uint32_t pulse_width_delta_nsec = 0U; 
void led_delta_timer_handler(struct k_timer *timer_info){

}

K_TIMER_DEFINE(led_delta_timer, led_delta_timer_handler, NULL); 

void main(){
    if(!device_is_ready(fanding_led.dev)){
        printk("Error: PWM device %s is not ready! \n", fanding_led.dev->name);
        return; 
    }

    k_timer_start(&led_delta_timer, K_MSEC(SLEEP_DELTA_MSEC), K_MSEC(SLEEP_DELTA_MSEC)); 
}