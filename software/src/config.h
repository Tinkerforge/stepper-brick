/* stepper-brick
 * Copyright (C) 2010-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config.h: Stepper-Brick specific configuration
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

#ifndef CONFIG_H
#define CONFIG_H

#include "communication.h"
#include "bricklib/drivers/board/sam3s/SAM3S.h"
#include "stepper.h"

#define BRICK_FIRMWARE_VERSION_MAJOR 2
#define BRICK_FIRMWARE_VERSION_MINOR 3
#define BRICK_FIRMWARE_VERSION_REVISION 4

#define BRICK_HARDWARE_VERSION_MAJOR 1
#define BRICK_HARDWARE_VERSION_MINOR 1
#define BRICK_HARDWARE_VERSION_REVISION 0

#define BRICK_DEVICE_IDENTIFIER 15

// ************** DEBUG SETTINGS **************
#define DEBUG_SPI_STACK 1
#define DEBUG_I2C_EEPROM 0
#define DEBUG_STARTUP 1
#define DEBUG_BRICKLET 1
#define DEBUG_STEPPER 1
//#define PROFILING
//#define PROFILING_TIME 100 // After how many seconds profiling is printed

#define DISABLE_JTAG_ON_STARTUP
//#define LOGGING_SERIAL
//#define LOGGING_LEVEL LOGGING_DEBUG
#define LOGGING_LEVEL LOGGING_NONE


// ************** BRICK SETTINGS **************

// Frequencies
#define BOARD_MCK      64000000 // Frequency of brick
#define BOARD_MAINOSC  16000000 // Frequency of oscillator
#define BOARD_ADC_FREQ 16000000 // Frequency of ADC
#define BOARD_OSC_EXTERNAL      // Use external oscillator

#define BRICK_HAS_CO_MCU_SUPPORT

// UART for console output (printf)
#define PIN_CONSOLE_RXD  {1 << 21, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_CONSOLE_TXD  {1 << 22, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

#define CONSOLE_BAUDRATE 115200
#define CONSOLE_USART    USART1
#define CONSOLE_ID       ID_USART1
#define CONSOLE_PINS     {PIN_CONSOLE_RXD, PIN_CONSOLE_TXD}

#define PINS_UART        {PIN_CONSOLE_RXD, PIN_CONSOLE_TXD}

// TWI
// TWI version
#define TWI_V3XX

// TWI stack definitions (for reading of eeproms from Bricks in stack)
#define TWI_STACK           TWI1
#define PIN_TWI_TWD_STACK   {1 << 4, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWCK_STACK  {1 << 5, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PINS_TWI_STACK      PIN_TWI_TWD_STACK, PIN_TWI_TWCK_STACK

// TWI bricklet definitions (for bricklets, spi select and brick specific
//                           functions)
#define TWI_BRICKLET           TWI0
#define PIN_TWI_TWD_BRICKLET   {1 << 3, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWCK_BRICKLET  {1 << 4, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PINS_TWI_BRICKLET      PIN_TWI_TWD_BRICKLET, PIN_TWI_TWCK_BRICKLET

// USB
// USB VBUS monitoring pin for USB plug and play
#define PIN_USB_DETECT  {1 << 26, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
// USB product descriptor (name of brick)
#define PRODUCT_DESCRIPTOR { \
	USBStringDescriptor_LENGTH(13), \
    USBGenericDescriptor_STRING, \
    USBStringDescriptor_UNICODE('S'), \
    USBStringDescriptor_UNICODE('t'), \
    USBStringDescriptor_UNICODE('e'), \
    USBStringDescriptor_UNICODE('p'), \
    USBStringDescriptor_UNICODE('p'), \
    USBStringDescriptor_UNICODE('e'), \
    USBStringDescriptor_UNICODE('r'), \
    USBStringDescriptor_UNICODE(' '), \
    USBStringDescriptor_UNICODE('B'), \
    USBStringDescriptor_UNICODE('r'), \
    USBStringDescriptor_UNICODE('i'), \
    USBStringDescriptor_UNICODE('c'), \
    USBStringDescriptor_UNICODE('k') \
}


// SPI
#define PIN_SPI_MISO        {1 << 12, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SPI_MOSI        {1 << 13, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SPI_SPCK        {1 << 14, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

#define PINS_SPI            PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_SPCK

#define PIN_SPI_SELECT_SLAVE  {1 << 11, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

// LED
#define PIN_LED_STD_BLUE    {1 << 9, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_STD_RED     {1 << 10, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PINS_STD_LED        PIN_LED_STD_BLUE, PIN_LED_STD_RED
#define PINS_LED            PINS_STD_LED

#define LED_STD_BLUE        0
#define LED_STD_RED         1


// Brick Detect
// Set low by master
// TODO: Change name
#define PIN_DETECT        {1 << 6, PIOB, ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}



// ************** INTERRUPT PRIORITIES ***********
#define PRIORITY_EEPROM_MASTER_TWI0  1
#define PRIORITY_EEPROM_SLAVE_TWI1   1
#define PRIORITY_STACK_SLAVE_SPI     5
#define PRIORITY_PROFILING_TC0       0
#define PRIORITY_STEPPER_TC0         6

// ************** BRICKLET SETTINGS **************

// Number of bricklet ports
#define BRICKLET_NUM 2

// BRICKLET A
#define BRICKLET_A_ADDRESS 84
#define BRICKLET_A_ADC_CHANNEL 4

#define BRICKLET_A_PIN_1_AD   {1 << 0, PIOB, ID_PIOB, PIO_INPUT, PIO_DEFAULT}
#define BRICKLET_A_PIN_2_DA   {1 << 2, PIOB, ID_PIOB, PIO_INPUT, PIO_DEFAULT}
#define BRICKLET_A_PIN_3_PWM  {1 << 0, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
#define BRICKLET_A_PIN_4_IO   {1 << 25, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
#define BRICKLET_A_PIN_SELECT {0, 0, 0, 0, 0}

// BRICKLET B
#define BRICKLET_B_ADDRESS 80
#define BRICKLET_B_ADC_CHANNEL 5

#define BRICKLET_B_PIN_1_AD   {1 << 1, PIOB, ID_PIOB, PIO_INPUT, PIO_DEFAULT}
#define BRICKLET_B_PIN_2_DA   {1 << 3, PIOB, ID_PIOB, PIO_INPUT, PIO_DEFAULT}
#define BRICKLET_B_PIN_3_PWM  {1 << 1, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
#define BRICKLET_B_PIN_4_IO   {1 << 16, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
#define BRICKLET_B_PIN_SELECT {0, 0, 0, 0, 0}

// *************** STEPPER DEBUGGING **************
#if(DEBUG_STEPPER)
#define logstepperd(str, ...) do{logd("stepper: " str, ##__VA_ARGS__);}while(0)
#define logstepperi(str, ...) do{logi("stepper: " str, ##__VA_ARGS__);}while(0)
#define logstepperw(str, ...) do{logw("stepper: " str, ##__VA_ARGS__);}while(0)
#define logsteppere(str, ...) do{loge("stepper: " str, ##__VA_ARGS__);}while(0)
#define logstepperf(str, ...) do{logf("stepper: " str, ##__VA_ARGS__);}while(0)
#else
#define logstepperd(str, ...) {}
#define logstepperi(str, ...) {}
#define logstepperw(str, ...) {}
#define logsteppere(str, ...) {}
#define logstepperf(str, ...) {}
#endif
#endif

// *************** DRV8811 PINS ***************
#define PIN_ENABLE      {1 << 23, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_SLEEP       {1 << 24, PIOA, ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_STEP        {1 << 15, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_DIRECTION   {1 << 28, PIOA, ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_USM0        {1 << 29, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_USM1        {1 << 30, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_RESET       {1 << 31, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_SYNC_RECT   {1 << 2,  PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_HOME        {1 << 5,  PIOA, ID_PIOA, PIO_INPUT,    PIO_DEFAULT}
#define PIN_VREF        {1 << 13, PIOB, ID_PIOB, PIO_INPUT,    PIO_DEFAULT}
#define PIN_DECAY       {1 << 14, PIOB, ID_PIOB, PIO_INPUT,    PIO_DEFAULT}
#define PIN_PWR_DAC     {1 << 8,  PIOA, ID_PIOA, PIO_INPUT,    PIO_DEFAULT}

#define PINS_STEPPER    PIN_ENABLE, PIN_SLEEP, PIN_STEP, PIN_DIRECTION, \
                        PIN_USM0, PIN_USM1, PIN_RESET, PIN_SYNC_RECT, \
                        PIN_HOME, PIN_VREF, PIN_DECAY, PIN_PWR_DAC


// ************** POWER MANAGEMENT **************
#define VOLTAGE_MAX_VALUE 4095
#define VOLTAGE_MIN_VALUE 0
#define VOLTAGE_MIN_DAC (3300/6)
#define VOLTAGE_MAX_DAC (3300*5/6)

#define VOLTAGE_STACK_CHANNEL 3
#define VOLTAGE_STACK_MULTIPLIER 11
#define VOLTAGE_STACK_REFERENCE 3300
#define VOLTAGE_STACK_PIN {1 << 20, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLDOWN}
#define VOLTAGE_STACK_SWITCH_PIN {1 << 27, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}

#define VOLTAGE_EXTERN_CHANNEL 2
#define VOLTAGE_EXTERN_MULTIPLIER 11
#define VOLTAGE_EXTERN_REFERENCE 3300
#define VOLTAGE_EXTERN_PIN {1 << 19, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLDOWN}

#define VREF_CHANNEL 0
#define VREF_MULTIPLIER 1
#define VREF_REFERENCE 2750
#define VREF_DEFAULT_CURRENT 800

#define MIN_EXTERN_VOLTAGE 8000
#define MIN_EXTERN_VALUE ((MIN_EXTERN_VOLTAGE * VOLTAGE_MAX_VALUE) / \
                          (VOLTAGE_EXTERN_MULTIPLIER* \
                           VOLTAGE_EXTERN_REFERENCE))

#define STEPPER_CURRENT_CHANNEL 1
#define STEPPER_CURRENT_MULTIPLIER 2
#define STEPPER_CURRENT_REFERENCE 3300
#define STEPPER_CURRENT_PIN {1 << 18, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLDOWN}

// 15: 0.15 Ohm Resistor
// 1/6: Minimum value for DAC
// 5/6: Maximim value for DAC
#define VREF_MIN_CURRENT (330000/(6*8*15))
#define VREF_MAX_CURRENT (330000*5/(6*8*15))

// 2.7k voltage divider
#define VREF_RES_MIN_CURRENT ((330000*27/127)/(6*8*15))
#define VREF_RES_MAX_CURRENT ((330000*27/127)*5/(6*8*15))

#define DECAY_CHANNEL 1
