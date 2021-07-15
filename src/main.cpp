#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t xQueue1;

void task1 (void *parameter)
{
  while(1)
  {
  // vTaskDelay(10);
  // vtaskDelay(pdMS_TO_TICKS(1000))
  unsigned long x = 500;
  xQueueSendToFront( xQueue1, &x, 10);
  }
}
void task2 (void *parameter)
{
  while(1)
  {
  unsigned long recievedvalue = 0;
  xQueueReceive(xQueue1, &recievedvalue, 10);
  Serial.println(recievedvalue);
  digitalWrite(LED_BUILTIN, HIGH);
  vTaskDelay(pdMS_TO_TICKS(1000));
  digitalWrite(LED_BUILTIN, LOW);
  vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  xQueue1 = xQueueCreate( 10, sizeof( unsigned long ));
  xTaskCreate(task1,"task1",  128  , NULL,  1,  NULL);
  xTaskCreate(task2,"task2",  128  , NULL,  2,  NULL);
  vTaskStartScheduler();
}

void loop() 
{

}