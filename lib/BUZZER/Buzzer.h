#ifndef __BUZZER_H_
#define __BUZZER_H_

#include"Arduino.h"

#define BUZZER_PIN 3
#define BUZZER_FREQ 2000//频率
#define BUZZER_CHANNEL 0//通道
#define BUZZER_RESOLUTION 8//位数 

#define voice1 125

void Buzzer_Init();
void Buzzer_Voice(int duty);
void Buzzer_Clear();

#endif // !__BUZZER_H_
