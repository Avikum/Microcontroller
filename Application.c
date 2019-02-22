#include "stm32f407_gpio_header.h"
#include "stm32f407xx.h"

#define GREEN_LED		12
#define ORANGE_LED	13
#define RED					14
#define BLUE				15

#define USER_PUSH		0

void led_init()
{
	gpio_pin_configuration gpio_pin_config;
	/* Enable the clock for GPIOD */
	GPIO_PORT_D_CLOCK_ENABLE();
	gpio_pin_config.pin    = GREEN_LED;
	gpio_pin_config.mode   = GPIO_PIN_OUTPU_MODE;
	gpio_pin_config.optype = GPIO_PIN_OPTYPE_PUSHPULL;
	gpio_pin_config.speed  = GPIO_PIN_MEDIUM_SPEED;
	gpio_pin_config.pull   = GPIO_PIN_NO_PULL_UP_DOWN;
	stm32f407_gpio_init(GPIO_PORT_D, &gpio_pin_config);

	gpio_pin_config.pin    = ORANGE_LED;
	stm32f407_gpio_init(GPIO_PORT_D, &gpio_pin_config);

	gpio_pin_config.pin    = RED;
	stm32f407_gpio_init(GPIO_PORT_D, &gpio_pin_config);

	gpio_pin_config.pin    = BLUE;
	stm32f407_gpio_init(GPIO_PORT_D, &gpio_pin_config);

	
}

void led_on( uint16_t pin)
{
	stm32f407_gpio_write(GPIO_PORT_D, pin, 1);
}

void led_off(uint16_t pin)
{
	stm32f407_gpio_write(GPIO_PORT_D, pin, 0);
}

void led_toggle(uint16_t pin)
{
	if(stm32f407_gpio_read(GPIO_PORT_D,pin))
		stm32f407_gpio_write(GPIO_PORT_D, pin, 1);
	else
		stm32f407_gpio_write(GPIO_PORT_D, pin, 0);
}



int main()
{
	led_init();
	//led_on(GREEN_LED);
	//led_on(RED);
	//while(1);
	//led_on(GREEN_LED);
	//led_on(BLUE);
	
	GPIO_PORT_A_CLOCK_ENABLE();
	
	gpio_configure_interrupt(USER_PUSH,FALLING_EDGE);
	
	gpio_enable_interrupt(USER_PUSH,6);
	
	/*while(1)
	{
		//led_off(GREEN_LED);
		//for(uint32_t i =0; i<500000;i++);
		led_toggle(GREEN_LED);
	}*/
	while(1);
	return 0;
}

void EXTI0_IRQHandler(void)
{
	gpio_clear_pendingbit(USER_PUSH);
	led_on(GREEN_LED);
	led_on(RED);
	
	
}
	
