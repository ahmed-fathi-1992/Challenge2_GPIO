/*
 * gpio.c
 *
 * Created: 17/01/2020 14:44:58
 *  Author: ahmed_pc
 */ 


typedef enum prog {
  seg_counter,
  Button_press,
  Traffic_light,
}prog;

typedef enum{
	GO_state=0,Stop_state,Get_Ready_state
}prog_states;

void seg_counter_fun(void);
void Button_press_fun(void);
void Traffic_light_fun(void);

//#include <avr/io.h>
//#include "registers.h"
#include "gpio.h"
#include "led.h"
#include "softwareDelay.h"
#include "pushButton.h"
#include "sevenSeg.h"

int main(void)
{
	prog program = seg_counter; // select program to run GPIO_REQ7:(seg_counter) GPIO_REQ8:(Button_press) GPIO_REQ9:(Traffic_light)
 switch (program)
  {
		case seg_counter:
		 seg_counter_fun();				
		break;
		
		case Button_press:
		 Button_press_fun();
		break;
		
		case Traffic_light:
		 Traffic_light_fun();		
		break;

		default:
		break;
 }
	
}


	
void seg_counter_fun(void)
{
			sevenSegInit(SEG_0);
			sevenSegInit(SEG_1);
			while(1)
			{
				softwareDelayMs(1000);
				for (int digit_1 =0 ;digit_1<10 ;digit_1++)
				{
					for(int digit_0 =0 ;digit_0<10 ;digit_0++)
					{
						for (int count =0 ;count<100 ;count++)
						{
							
							sevenSegWrite(SEG_0, digit_0);
							softwareDelayMs(5);
							sevenSegDisable( SEG_0);
							
							sevenSegWrite(SEG_1, digit_1);
							softwareDelayMs(5);
							sevenSegDisable( SEG_1);
						}
					}
				}

			}	
}

void Button_press_fun(void)
{
	uint8_t led_on_repeat=0;
	pushButtonInit(BTN_1);
	Led_Init(LED_1);
	while(1)
	{  led_on_repeat=0;
		if( Prepressed== pushButtonGetStatus(BTN_1))
		{
			while(Prepressed== pushButtonGetStatus(BTN_1));
			Led_On(LED_1);
			for (int counter=0; counter<20;counter++)
			{
				if( Prepressed== pushButtonGetStatus(BTN_1))
				led_on_repeat++;
												
			}
			if( led_on_repeat>0) {softwareDelayMs(1000);}
			
			Led_Off(LED_1);
			
		}
		
		
	}
	
}

void Traffic_light_fun(void)
{
	prog_states state = GO_state;
	Led_Init(LED_1); Led_Init(LED_2); Led_Init(LED_3);
	Led_Off(LED_1);  Led_Off(LED_2);  Led_Off(LED_3);
	//	Led_On(LED_1);   Led_On(LED_2);   Led_On(LED_3);
	
	while(1){
		switch(state) {
			case GO_state:        {Led_On(LED_1); softwareDelayMs(1000); Led_Off(LED_1);     state=Stop_state;       break;}
			case Stop_state:      {Led_On(LED_3); softwareDelayMs(1000); Led_Off(LED_3);     state=Get_Ready_state;  break;}
			case Get_Ready_state: {Led_On(LED_2); softwareDelayMs(1000); Led_Off(LED_2);     state=GO_state;         break;}
		}//end of switch.
	}//end of while	
	
}