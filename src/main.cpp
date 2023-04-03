#include <Arduino.h>
#include"Freenove_WS2812_Lib_for_ESP32.h"
#include"FreeRTOS.h"
#include"SSR.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////WS2812
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LEDS_COUNT  2
#define LEDS_PIN	4
#define CHANNEL		0
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);
u8 m_color[5][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0} };
int delayval = 100;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////FreeRTOS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QueueHandle_t queue;//声明数据指针全局变量
TaskHandle_t taskone,tasktwo;//声明任务句柄
void Taskone( void * parameter )
{
  while(1)
  {  
  	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < LEDS_COUNT; i++) {
			strip.setLedColorData(i, m_color[j][0], m_color[j][1], m_color[j][2]);
			strip.show();
			delay(delayval);
		}
		delay(500);
	}  
  }
  vTaskDelete( NULL );

}
void Tasktwo(void * parameter)
{
  while(1)
  {
  digitalWrite(SSR_PIN,SSR_OPEN);
  delay(500);
  digitalWrite(SSR_PIN,SSR_CLOSE);
  delay(500);   
  }
  vTaskDelete( NULL );
 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
	strip.begin();
	strip.setBrightness(10);	
  queue=xQueueCreate(10,sizeof(int));//队列长度为10，队列数据类型为整型
  xTaskCreate(Taskone,"TaskOne",10000,NULL,1,&taskone);//创建Taskone
  xTaskCreate(Tasktwo,"TaskTwo",10000,NULL,1,&tasktwo);//创建Tasktwo
  SSR_Init();

}
void loop() {
}