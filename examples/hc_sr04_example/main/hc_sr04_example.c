#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "hc_sr04.h"
#include <stdio.h>

#define TRIG_GPIO CONFIG_TRIG_GPIO 
#define ECHO_GPIO CONFIG_ECHO_GPIO

static const char *TAG = "HC_SR04_example"; 

void app_main(void)
{
    float distance_cm; 
    hc_sr04_config_t config = {
        .trig_pin = TRIG_GPIO,
        .echo_pin = ECHO_GPIO,
    }; 

    hc_sr04_init(&config); 
    ESP_LOGI(TAG, "initialization successful echo pin : %d, trig pin : %d", ECHO_GPIO,
                                                                            TRIG_GPIO); 

    while (1) {
        hc_sr04_measure(&distance_cm); 
        printf("Distance : %.2fcm\n", distance_cm); 
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
