#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "LCD.h"
#include "snake.h"
//ALIENTEK Mini STM32开发板范例代码11
//TFTLCD显示实验
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{
	u8 x = 0;
	u8 lcd_id[12];		 //存放LCD ID字符串
	Stm32_Clock_Init(9); //系统时钟设置
	uart_init(72, 9600); //串口初始化为9600
	delay_init(72);		 //延时初始化
	LED_Init();			 //初始化与LED连接的硬件接口
	LCD_Init();
	//LED0 = !LED0;
	initialize();
	while (gamewithai())
		;

	POINT_COLOR = RED;
	sprintf((char *)lcd_id, "LCD ID:%04X", lcddev.id); //将LCD ID打印到lcd_id数组。

	while (1)
	{
		switch (x)
		{
		case 0:
			LCD_Clear(WHITE);
			break;
		case 1:
			LCD_Clear(BLACK);
			break;
		case 2:
			LCD_Clear(BLUE);
			break;
		case 3:
			LCD_Clear(RED);
			break;
		case 4:
			LCD_Clear(MAGENTA);
			break;
		case 5:
			LCD_Clear(GREEN);
			break;
		case 6:
			LCD_Clear(CYAN);
			break;

		case 7:
			LCD_Clear(YELLOW);
			break;
		case 8:
			LCD_Clear(BRRED);
			break;
		case 9:
			LCD_Clear(GRAY);
			break;
		case 10:
			LCD_Clear(LGRAY);
			break;
		case 11:
			LCD_Clear(BROWN);
			break;
		}

		POINT_COLOR = RED;
		LCD_ShowString(30, 40, 200, 24, 24, (u8 *)"Mini STM32 ^_^");
		LCD_ShowString(30, 70, 200, 16, 16, (u8 *)"TFTLCD TEST");
		LCD_ShowString(30, 90, 200, 16, 16, (u8 *)"ATOM@ALIENTEK");
		LCD_ShowString(30, 110, 200, 16, 16, lcd_id); //显示LCD ID
		LCD_ShowString(30, 130, 200, 12, 12, (u8 *)"2014/3/7");
		x++;
		if (x == 12)
			x = 0;
		LED0 = !LED0;
		delay_ms(1000);
	}
}
