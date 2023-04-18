#include <Arduino.h>
#include"Freenove_WS2812_Lib_for_ESP32.h"
#include"FreeRTOS.h"
#include"SSR.h"
#include"Buzzer.h"
#include"Max6675.h"
#include"lvgl.h"
#include"TFT_eSPI.h"
#include"SimpleFOC.h"
#include "Pages\Pages.h"
///////////////LCD&LVGL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static lv_disp_draw_buf_t draw_buf;//显示器变量
static lv_color_t buf[TFT_WIDTH * 10];//刷新缓存
TFT_eSPI tft=TFT_eSPI();
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
 
    tft.startWrite();                                        //使能写功能
    tft.setAddrWindow(area->x1, area->y1, w, h);             //设置填充区域
    tft.pushColors((uint16_t *)&color_p->full, w * h, true); //写入颜色缓存和缓存大小
    tft.endWrite();                                          //关闭写功能
 
    lv_disp_flush_ready(disp); //调用区域填充颜色函数
}

void LCD_Init()
{
    tft.init();
    tft.setRotation(0);
    // lv_init();

    // lv_disp_draw_buf_init(&draw_buf, buf, NULL, TFT_WIDTH * 10);
 
    // /*Initialize the display*/
    // static lv_disp_drv_t disp_drv;
    // lv_disp_drv_init(&disp_drv);
    // /*Change the following line to your display resolution*/
    // disp_drv.hor_res = TFT_WIDTH;
    // disp_drv.ver_res = TFT_HEIGHT;
    // disp_drv.flush_cb = my_disp_flush;
    // disp_drv.draw_buf = &draw_buf;
    // lv_disp_drv_register(&disp_drv);
}
///////////////MAX6675
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MAX6675 thermocouple(MAX6675_CS,MAX6675_SCK,MAX6675_SO);

///////////////WS2812
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LEDS_COUNT  2
#define LEDS_PIN	4
#define CHANNEL		0
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);
u8 m_color[5][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0} };
int delayval = 100;
///////////////FreeRTOS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QueueHandle_t queue;//声明数据指针全局变量
TaskHandle_t taskone,tasktwo,getcelsiustask,lvgltask;//声明任务句柄
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
//热电偶温度获取及SSR调温
void GetcelsiusTask(void * parameter)
{
  // Serial.print(thermocouple.readCelsius());
  vTaskDelete(NULL);
}
void LvglTask(void * parameter)
{
  // while(1)
  // {
  // }
    vTaskDelete(NULL);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
	strip.begin();//开启ws2812闪烁
	strip.setBrightness(10);	
  queue=xQueueCreate(10,sizeof(int));//队列长度为10，队列数据类型为整型
  xTaskCreate(Taskone,"TaskOne",10000,NULL,1,&taskone);//创建Taskone
  xTaskCreate(Tasktwo,"TaskTwo",10000,NULL,1,&tasktwo);//创建Tasktwo
  // xTaskCreate(GetcelsiusTask,"GetCelsiusTask",10000,NULL,1,&getcelsiustask);
  xTaskCreate(LvglTask,"LvglTask",10000,NULL,1,&lvgltask);
  SSR_Init();
  // Buzzer_Init();
  LCD_Init();
  tft.setTextSize(2);
tft.setTextColor(TFT_GREEN);
tft.setCursor(100, 100);

tft.setTextDatum(MC_DATUM);

tft.drawString("Moonbeam ", 10, 10);
}
void loop() {
}