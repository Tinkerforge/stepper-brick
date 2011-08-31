/* master-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * main.c: Servo Brick startup code
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pio/pio.h>
#include <FreeRTOS.h>
#include <task.h>

#include "bricklib/com/i2c/i2c_pca9549/i2c_pca9549.h"
#include "bricklib/com/spi/spi_stack/spi_stack_master.h"
#include "bricklib/com/spi/spi_stack/spi_stack_slave.h"
#include "bricklib/com/spi/spi_stack/spi_stack_common.h"
#include "bricklib/com/i2c/i2c_eeprom/i2c_eeprom_master.h"
#include "bricklib/com/i2c/i2c_eeprom/i2c_eeprom_slave.h"
#include "bricklib/com/usb/usb.h"
#include "bricklib/logging/logging.h"
#include "bricklib/bricklet/bricklet_init.h"
#include "bricklib/drivers/uid/uid.h"
#include "bricklib/utility/init.h"
#include "bricklib/utility/profiling.h"
#include "bricklib/utility/led.h"
#include "bricklib/logging/logging.h"

#include "config.h"
#include "communication.h"
#include "stepper.h"

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName) {
	logf("Stack Overflow\n\r");
	while(true);
}

int main() {
	SLEEP_MS(5);
	brick_init();

    if(usb_is_connected()) {
    	logi("Configure as USB device\n\r");
    	usb_init();

    	xTaskCreate(usb_message_loop,
    				(signed char *)"usb_ml",
    				1000,
    				NULL,
    				1,
    				(xTaskHandle *)NULL);
    } else {
    	logi("Configure as Stack Participant (SPI)\n\r");
        spi_stack_slave_init();

    	xTaskCreate(spi_stack_slave_message_loop,
    			    (signed char *)"spi_ml",
    			    2500,
    			    NULL,
    			    1,
    			    (xTaskHandle *)NULL);
    }

	stepper_init();

	brick_init_start_tick_task();
	vTaskStartScheduler();
}
