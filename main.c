/*
 * main.c
 *
 *  Created on: 2024 May 27 10:00:46
 *  Author: Administrator
 */

#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

int delay1000;
int appCount1;
int appCount2;

// 1ms
void callback() {
	if(delay1000 > 0)
		delay1000--;
	if(appCount1 > 0)
		appCount1--;
	if(appCount2 > 0)
		appCount2--;
}

void delay(int d) {
	delay1000 = d;
	while(delay1000 > 0)
		;
}

int main(void) {
	DAVE_STATUS_t status;

	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if(status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while(1U)
			;
	}
	// 초기화 코드 삽입 부분

	int id = SYSTIMER_CreateTimer(1000, SYSTIMER_MODE_PERIODIC, callback, NULL);
	SYSTIMER_StartTimer(id);

	const DIGITAL_IO_t handler = { .gpio_port = XMC_GPIO_PORT5, .gpio_pin = 9U,
			.gpio_config = { .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL, .output_level =
					XMC_GPIO_OUTPUT_LEVEL_LOW,

			}, .hwctrl = XMC_GPIO_HWCTRL_DISABLED };
	XMC_GPIO_Init(handler.gpio_port, handler.gpio_pin, &handler.gpio_config);
	const DIGITAL_IO_t handler2 = { .gpio_port = XMC_GPIO_PORT5, .gpio_pin = 8U,
			.gpio_config = { .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL, .output_level =
					XMC_GPIO_OUTPUT_LEVEL_LOW,

			}, .hwctrl = XMC_GPIO_HWCTRL_DISABLED };
	XMC_GPIO_Init(handler2.gpio_port, handler2.gpio_pin, &handler2.gpio_config);

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while(1U) {
		if(appCount1 == 0) {
			appCount1 = 120;
			// 120ms
			PORT5->OUT ^= (1 << 8);
		}
		if(appCount2 == 0 && DIGITAL_IO_GetInput(&SW1)) {
			appCount2 = 180;
			// 180ms
			PORT5->OUT ^= (1 << 9);
		}
	}
}
