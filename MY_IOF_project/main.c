#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_err.h>
#define ECHO_GPIO 12
#define TRIGGER_GPIO 13
#define MAX_DISTANCE_CM 500 
#define BUZZER_PIN 14
#define LED_RED 4
#define LED_YELLOW 5
#define LED_GREEN 19
#include "wiringpi.h"
#include "ultrasonic.h"
int distance;
void ultrasonic_test(void *pvParameters)
{
    float distance;
    ultrasonic_sensor_t sensor = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO
    };
    ultrasonic_init(&sensor);
    while (true) {
        esp_err_t res = ultrasonic_measure(&sensor, MAX_DISTANCE_CM, &distance);
        if ( 21 >= distance*100)  { 
            analogWrite(LED_RED,1);
            analogWrite(BUZZER_PIN,0);
            analogWrite(LED_YELLOW,0);
            analogWrite(BUZZER_PIN,1);
            printf("bin was full !!....\n");
            }
        else if( 120 <= distance*100){
           analogWrite(LED_GREEN,1);
           analogWrite(LED_YELLOW,0);
           analogWrite(LED_RED,0);
           analogWrite(BUZZER_PIN,0);
             printf("bin was Empty...\n");
             }
        else if ((110<=distance*100)&(120>=distance*100)){
           analogWrite(LED_GREEN,1);
           analogWrite(LED_YELLOW,0);
           analogWrite(LED_RED,0);
           analogWrite(BUZZER_PIN,0);
          printf("bin was 10%% full...\n");
        }
        else if((99<=distance*100)&(110>=distance*100)){
          analogWrite(LED_GREEN,1);
          analogWrite(LED_YELLOW,0);
           analogWrite(LED_RED,0);
           analogWrite(BUZZER_PIN,0);
          printf("bin was 20%% full...\n");
        }
        else if((88<=distance*100)&(99>=distance*100)){
           analogWrite(LED_GREEN,1);
           analogWrite(LED_YELLOW,0);
           analogWrite(LED_RED,0);
           analogWrite(BUZZER_PIN,0);
          printf("bin was 30%% full...\n");
        }
        else if ((77<=distance*100)&(88>=distance*100)){
           analogWrite(LED_GREEN,1);
           analogWrite(LED_YELLOW,0);
           analogWrite(LED_RED,0);
           analogWrite(BUZZER_PIN,0);
          printf("bin was 40%% full....\n");
        }
        else if ((66<=distance*100)&(77>=distance*100)){
           analogWrite(LED_GREEN,1);
           analogWrite(LED_YELLOW,0);
           analogWrite(LED_RED,0);
           analogWrite(BUZZER_PIN,0);
          printf("bin was 50%% full....\n");
        }
        else if ((55<=distance*100)&(66>=distance*100)){
           analogWrite(LED_YELLOW,1);
           analogWrite(LED_RED,0);
           analogWrite(LED_GREEN,0);
           analogWrite(BUZZER_PIN,0);
          printf("bin was 60%% full....\n");
        }
        else if ((44<=distance*100)&(55>=distance*100)){
           analogWrite(LED_YELLOW,1);
           analogWrite(LED_RED,0);
           analogWrite(LED_GREEN,0);
           analogWrite(BUZZER_PIN,0);
          printf("bin was 70%% full....\n");
        }
        else if ((33<=distance*100)&(44>=distance*100)){
          analogWrite(LED_YELLOW,1);
          analogWrite(LED_RED,0);
          analogWrite(LED_GREEN,0);
          analogWrite(BUZZER_PIN,0);
          printf("bin was 80%% full....\n");
        }
        else if ((22<=distance*100)&(33>=distance*100)){
          analogWrite(LED_YELLOW,0);
           analogWrite(LED_GREEN,0);
          analogWrite(LED_RED,1);
          analogWrite(BUZZER_PIN,0);
          printf("bin was 90%% full....\n");
        }
        else {
          analogWrite(LED_GREEN,1);
          analogWrite(BUZZER_PIN,0);
            printf("bin was Empty...\n");   
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
     analogWrite(BUZZER_PIN,0);
}
void app_main()
{
    xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
