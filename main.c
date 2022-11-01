#include "main.h"

#define DEVICE_NAME "button4"
#define DEVICE_REQUEST "get"

FILE uart_stream = FDEV_SETUP_STREAM(uart_putc, uart_getc, _FDEV_SETUP_RW);

uint8_t Button_Pressed = 0;

uint8_t Button_0_State = 0;
uint8_t Button_1_State = 0;
uint8_t Button_2_State = 0;
uint8_t Button_3_State = 0;

uint32_t ButtonTimer_0 = 0;
uint32_t ButtonTimer_1 = 0;
uint32_t ButtonTimer_2 = 0;
uint32_t ButtonTimer_3 = 0;
#define ButtonTimerValue 0x18FFF

#define BUF_SIZE 128
char buf[BUF_SIZE];
unsigned char buf_cnt;

#define WORD_SIZE 128
char word_out[WORD_SIZE];
uint8_t word_cnt;

#define ANSWER "\r\nAnswer="

uint8_t Flag = 0;

void main(void)
{ 
  _delay_ms(500);

  TX_EN_PINCONFIG;
  TX_EN_OFF;
  
  LED_0_PINCONFIG; 
  LED_1_PINCONFIG; 
  LED_2_PINCONFIG;
  LED_3_PINCONFIG;
	
  BUTTON_0_PINCONFIG;
  BUTTON_1_PINCONFIG;
  BUTTON_2_PINCONFIG;
  BUTTON_3_PINCONFIG;
	
  BUTTON_0_PULLUP_EN;
  BUTTON_1_PULLUP_EN;
  BUTTON_2_PULLUP_EN;
  BUTTON_3_PULLUP_EN;

  INT0_INTERNAL_PULLUP_ON;
  INT0_PIN_CONF_INPUT;
  INT0_TYPE_FALLING_FRONT;
  INT0_ENABLE;
	
  stdout = stdin = &uart_stream;
  uart_init(UBRR_VAL);

  //puts( "Hello world\r\n" );

  GLOBAL_INTERRUPTS_ENABLE;


  uint8_t i = 0;
  int c = 0;
  char str[8];
  
  /*
  TX_EN_OFF;
  while(1){
    _delay_ms(1000);      
		  
    TX_EN_ON;_delay_ms(1);
    {puts("123456789\r\n");}
    _delay_ms(10);TX_EN_OFF;
  }
  TX_EN_OFF;*/

  

  while(1)
  {

	TX_EN_OFF;
	
    if(ButtonTimer_0>0)
	{LED_0_ON;ButtonTimer_0--;}
    else
	{LED_0_OFF;}
	if(ButtonTimer_1>0)
	{LED_1_ON;ButtonTimer_1--;}
    else
	{LED_1_OFF;}
	if(ButtonTimer_2>0)
	{LED_2_ON;ButtonTimer_2--;}
    else
	{LED_2_OFF;}
	if(ButtonTimer_3>0)
	{LED_3_ON;ButtonTimer_3--;}
    else
	{LED_3_OFF;}
	

    if((c = getchar())!= EOF)
    {
      if((c == '\r')||(c == '\n'))
      { 
        buf[buf_cnt] = '\0';

		
        if (!strcmp(buf,DEVICE_REQUEST))
        {
          _delay_ms(100);
          TX_EN_ON;_delay_ms(100);
		  /*if(Button_0_State>0){putchar(48);Flag=0xFF;}
		  if(Button_1_State>0){putchar(49);Flag=0xFF;}
		  if(Button_2_State>0){putchar(50);Flag=0xFF;}
		  if(Button_3_State>0){putchar(51);Flag=0xFF;}
		  if(Flag == 0)
		  {puts("012\r\n");}
          else
		  {putchar(13);}*/
	      sprintf(str,"%01d%\r\n",Button_Pressed);
		  puts(str);
		  _delay_ms(100);TX_EN_OFF;

		  Button_Pressed = 0;
		  /*Flag=0x00;
          Button_0_State = 0x00;
          Button_1_State = 0x00;
          Button_2_State = 0x00;
          Button_3_State = 0x00;  */
        }

        for(i=0; i<BUF_SIZE; i++)
        {
          buf[i] = 0; 
	    }
		buf_cnt = 0;
		
      } 
      else 
      if( buf_cnt < (BUF_SIZE-1) )
      {
        //пока есть место в буфере помещаем туда принятые байты
          buf[buf_cnt] = c;
          buf_cnt++;
      }
	  //putchar(c);
    } 
    
	
  }  // while(1){}*/
  
  
  
} // main()



ISR(INT0_vect)
{
  cli(); //запрещаем прерывания

  if(BUTTON_0_NOT_PRESSED)
  {}
  else
  {
    if(ButtonTimer_0==0)
	{
	  ButtonTimer_0 = ButtonTimerValue;
	  Button_0_State = 0xFF;
	  Button_Pressed = 1;
	}
  }
  
  if(BUTTON_1_NOT_PRESSED)
  {}
  else
  {
    if(ButtonTimer_1==0)
	{
	  ButtonTimer_1 = ButtonTimerValue;
	  Button_1_State = 0xFF;
	  Button_Pressed = 2;
	}
  }
  
  if(BUTTON_2_NOT_PRESSED)
  {}
  else
  {
    if(ButtonTimer_2==0)
	{
	  ButtonTimer_2 = ButtonTimerValue;
	  Button_2_State = 0xFF;
	  Button_Pressed = 3;
	}
  }
  
  if(BUTTON_3_NOT_PRESSED)
  {}
  else
  {
    if(ButtonTimer_3==0)
	{
	  ButtonTimer_3 = ButtonTimerValue;
	  Button_3_State = 0xFF;
	  Button_Pressed = 4;
	}
  }
  sei(); //разрешаем прерывания
}
