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
#include "./Classes/devices.h"

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
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);

/*!
 * Declara��o da vari�vel a ser usada como flag para guardar o estado anterior dos led�s.
 */
bool bit = 1;
bool count = false;
uint16_t divisor = 0;
uint8_t t[4] = {48, 48, 48, 48};
/*

uint8_t increment(uint8_t t[4])
{
    t[3] += '1';
    if (t[3] > '9')
    {
        t[2] += '1';
        t[3] = '0';
        if (t[2] > 5)
        {
            t[1] += '1';
            t[2] = '0';
            if (t[1] > '9')
            {
                t[0] += '1';
                t[1] = '0';
                if (t[0] > 5)
                {
                    t[0] = '0';
                }
            }
        }
    }
    return t;
}
*/

/*!
 *   @brief    Realiza o blink dos leds vermelhor e azul.
 */
extern "C"
{
    void SysTick_Handler(void)
    {
        // LED TOGGLE
        //bit = !bit;
        blueLed.writeBit(bit);
        redLed.writeBit(bit);
        if (count)
        {
            if (divisor == 1)
            {
                t[3] += 1;
                if (t[3] > 57)
                {
                    t[2] += 1;
                    t[3] = 48;
                    if (t[2] > 53)
                    {
                        t[1] += 1;
                        t[2] = 48;
                        if (t[1] > 57)
                        {
                            t[0] += 1;
                            t[1] = 48;
                            if (t[0] > 53)
                            {
                                t[0] = 48;
                            }
                        }
                    }
                }
            }
            else if (divisor == 100)
                divisor = 0;
            divisor++;
        }
    }
}

/*!
 *   @brief    Realiza a configura��es das io's e espera pelas interrup��es.
 *
 *   Este programa realiza o teste da classe do perif�rico systick.
 *
 *   @return  sempre retorna o valor 0.
 */
int main(void)
{
    blueLed.setPortMode(gpio_output);
    redLed.setPortMode(gpio_output);
    Visor LCD(mode2Lines, mode16Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27);
    while (1)
    {
        count = true;
        LCD.printTime(t);
        /* Espera aqui por uma interrupcao */
    }
}
