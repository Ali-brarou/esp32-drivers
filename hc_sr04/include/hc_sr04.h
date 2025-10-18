#pragma once 

#include "driver/gpio.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    gpio_num_t trig_pin; 
    gpio_num_t echo_pin; 
} hc_sr04_config_t; 

esp_err_t hc_sr04_init(const hc_sr04_config_t *config); 
esp_err_t hc_sr04_measure(float *distance_cm); 

#ifdef __cplusplus
}
#endif
