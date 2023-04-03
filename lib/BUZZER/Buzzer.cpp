#include"Buzzer.h"

void Buzzer_Init()
{
    ledcSetup(BUZZER_CHANNEL,BUZZER_FREQ,BUZZER_RESOLUTION);//设置PWM通道、频率和占空比分辨率
    ledcAttachPin(BUZZER_PIN,BUZZER_CHANNEL);//将PWM通道绑定到实际的GPIO    
}

void Buzzer_Voice(int duty)
{
    ledcWriteTone(BUZZER_CHANNEL,BUZZER_FREQ);
    ledcWrite(BUZZER_CHANNEL,duty);
}

void Buzzer_Clear()
{
    ledcWriteTone(BUZZER_CHANNEL,BUZZER_FREQ);
    ledcWrite(BUZZER_CHANNEL,0);
}
