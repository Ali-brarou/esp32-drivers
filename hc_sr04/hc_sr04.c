#include "hc_sr04.h"
#include "esp_timer.h"
#include "rom/ets_sys.h"
#include <stdlib.h> 

static __attribute__((unused)) const char *TAG = "hc_sr04"; 
static gpio_num_t echo_pin, trig_pin;

esp_err_t hc_sr04_init(const hc_sr04_config_t *config)
{   
    if (!config)
        return ESP_ERR_INVALID_ARG; 

    echo_pin = config->echo_pin; 
    trig_pin = config->trig_pin; 
    
    gpio_reset_pin(echo_pin); 
    gpio_reset_pin(trig_pin); 

    gpio_set_direction(echo_pin, GPIO_MODE_INPUT); 
    gpio_set_direction(trig_pin, GPIO_MODE_OUTPUT); 

    gpio_set_level(trig_pin, 0); 

    return ESP_OK;  
}

esp_err_t hc_sr04_measure(float *distance_cm)
{
    uint64_t echo_start, echo_end; 

    if (!distance_cm)
        return ESP_ERR_INVALID_ARG; 

    gpio_set_level(trig_pin, 0); 
    ets_delay_us(2);
    gpio_set_level(trig_pin, 1); 
    ets_delay_us(10);
    gpio_set_level(trig_pin, 0); 

    while (!gpio_get_level(echo_pin)); 
    echo_start = esp_timer_get_time(); 
    while (gpio_get_level(echo_pin)); 
    echo_end = esp_timer_get_time(); 

    *distance_cm = (float)(echo_end - echo_start) / 58.0f;
    return ESP_OK; 
}
