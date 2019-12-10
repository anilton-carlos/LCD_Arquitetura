/*
 * main.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: anilton
 */

#include "stdint.h"
#include "./Bibliotecas/GPIO/mkl_GPIOPort.h"
#include "MKL25Z4.h"
#include "./Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.h"
#include "./Classes/devices.h"
#include "./Classes/digital.h"

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
FreqDivisor clock1Hz = FreqDivisor(1);
FreqDivisor clock5Hz = FreqDivisor(2);
//FreqDivisor clock10Hz = FreqDivisor(0.3);
/*!
 * Declara��o da vari�vel a ser usada como flag para guardar o estado anterior dos led�s.
 */

uint8_t time[4] = {0, 1, 3, 0};
TimeDecoder timeDecod = TimeDecoder();
CookDecoder cookDecod = CookDecoder();
OperDecoder operDecod = OperDecoder();
Timer Temporizador = Timer();
uint8_t input = 40, option = 0;
bool operacoes[3] = {0, 1, 0};

/*!
 *   @brief    Realiza o blink dos leds vermelhor e azul.
 */

extern "C"
{
	void SysTick_Handler(void)
	{
		clock1Hz.increment();

		if (clock1Hz.getClock())
			Temporizador.decrement();
			Temporizador.setTime(time);
			cookDecod.setInput(pp);
	}
}

/*!
 *   @brief    Realiza a configura��es das io's e espera pelas interrup��es.
 *
 *   Este programa realiza o teste da classe do perif�rico systick.
 *
 *   @return  sempre retorna o valor 0.
 */

Led fimTimer = Led(gpio_PTB18);
int main(void)
{
	Visor LCD(mode4Lines, mode20Cols, mode5x10Dots, i2c_PTE1, i2c_PTE0, 0x27);
	Temporizador.setTime(time);
	Temporizador.enableTimer(play);
	while (1)
	{

		if(time[2] ==  4){
			cookDecod.setInput(pp);
			time[0]=1;
			time[1]=0;
			time[2]=3;
			time[3]=0;
		}
		timeDecod.setInput(Temporizador.getTime());
		LCD.printTime(timeDecod.getOutput());
		LCD.printCook(cookDecod.getOutput());
		LCD.printOper(operDecod.getOutput());
		if (Temporizador.endTimer())
			fimTimer.turnOn();
		else
			fimTimer.turnOff();
	}
}
