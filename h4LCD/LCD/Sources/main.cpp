/*
 * main.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: anilton
 */

/*
#include "./Bibliotecas/I2C/mkl_LCD.h"
#include "MKL25Z4.h"
#include "./Classes/devices.h"

int main(void)
{
	Visor LCD(mode2Lines, mode16Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27);
	uint8_t tempo[4] = {57, 52, 53, 54};
	LCD.printTime(tempo);
	LCD.printCook("EDICAO");
	LCD.printOper("ON", "OFF", "ON");
}
*/

#include "stdint.h"
#include "./Bibliotecas/GPIO/mkl_GPIOPort.h"
#include "MKL25Z4.h"
#include "./Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.h"

/*!
 * 	Declara��o do led RGB interno da placa
 */
mkl_GPIOPort blueLed(gpio_PTD1);

/*!
 * 	Declara��o do led RGB interno da placa
 */
mkl_GPIOPort redLed(gpio_PTB18);

/*!
 * 	Declara��o do objeto systick e configura��o para acontecer uma interrup��o a cada 100ms
 * 	e usar o clock da placa de 42MHz
 */
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(1, clock42Mhz);

/*!
 * Declara��o da vari�vel a ser usada como flag para guardar o estado anterior dos led�s.
 */
bool bit = 0;


/*!
 *   @brief    Realiza o blink dos leds vermelhor e azul.
 */
extern "C" {
    void SysTick_Handler(void) {
        // LED TOGGLE
        bit = !bit;
        blueLed.writeBit(bit);
        redLed.writeBit(!bit);
    }
}

/*!
 *   @brief    Realiza a configura��es das io's e espera pelas interrup��es.
 *
 *   Este programa realiza o teste da classe do perif�rico systick.
 *
 *   @return  sempre retorna o valor 0.
 */
int main(void) {
    blueLed.setPortMode(gpio_output);
    redLed.setPortMode(gpio_output);
    while (1) {
        /* Espera aqui por uma interrupcao */
    }
}
