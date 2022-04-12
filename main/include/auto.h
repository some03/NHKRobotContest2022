//for stm32nucleoF446RE
#ifndef AUTO
#define AUTO
#include<Arduino.h>
#include<math.h>
#include<tuple>

std::tuple<int16_t,int16_t,int16_t>get_rotational_speed(bool init)
{
    if(init) 
    {   //use timer1,timer2,timer3 
        TIM2->CCMR1=0b00000001; 
        TIM3->CCMR1=0b00000001; 
        TIM4->CCMR1=0b00000001;
       
        TIM2->CCMR2=0b00000001;
        TIM3->CCMR2=0b00000001;
        TIM4->CCMR2=0b00000001;
        
        TIM2->SMCR=0b00000100;//initalize counter
        TIM3->SMCR=0b00000100;
        TIM4->SMCR=0b00000100;

        TIM2->SMCR=0b00000011;//select TI1 and TI2
        TIM3->SMCR=0b00000011;
        TIM4->SMCR=0b00000011;
   
        TIM2->CCER=0x00;//detect rising edge
        TIM3->CCER=0x00;
        TIM4->CCER=0x00;
    
        TIM2->CR1=0b00000001;//enable TI1 TI2
        TIM3->CR1=0b00000001;
        TIM4->CR1=0b00000001;

        TIM2->ARR=0xFF;//counts 0x00 to 0xff
        TIM3->ARR=0xFF;
        TIM4->ARR=0xFF;
    } 

    int16_t a=TIM2->CNT;
    int16_t b=TIM3->CNT;
    int16_t c=TIM4->CNT;
   
    uint16_t enc_buffa=a;
    uint16_t enc_buffb=b; 
    uint16_t enc_buffc=c;

    TIM2->CNT=0x00;
    TIM3->CNT=0x00;
    TIM4->CNT=0x00;

    if(enc_buffa>32767)a=(int16_t)enc_buffa;
    if(enc_buffb>32767)b=(int16_t)enc_buffb;
    if(enc_buffc>32767)c=(int16_t)enc_buffc;

    Serial.println(enc_buffa);

    
    return std::forward_as_tuple(a,b,c);

}

#endif

