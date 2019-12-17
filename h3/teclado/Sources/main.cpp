#include <stdint.h>
#include <MKL25Z4.h>
#include "teclado/mkl_KeyboardParallelPort.h"
#include "Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.h"
#include "dispositivos/led.h"
#include "dispositivos/switche.h"
#include "./dispositivos/displaySegments.h"
#include "servicos/EditService.h"
#include "servicos/IncrementService.h"
#include "servicos/Cozimento.h"
//#include <assert.h>
#include "../Includes/mkl_HC06BluetoothSlave.h"

//Declaração do bluetooh
mkl_HC06BluetoothSlave bt(uart0_PTD7, uart0_PTD6);
char buf = '0';
char aux = '0';
//Declaração do teclado

mkl_KeyboardParallelPort keyboard(gpio_PTA13, gpio_PTD5, gpio_PTD0, gpio_PTD2,
gpio_PTC12, gpio_PTC13, gpio_PTC16, gpio_PTC17);



//Declaração do 7 segmentos
displaySegments display (gpio_PTC7,gpio_PTC0,gpio_PTC3,gpio_PTC4,gpio_PTC5,
		gpio_PTC6,gpio_PTC10,gpio_PTC1, gpio_PTE29, gpio_PTE23, gpio_PTE22);

mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(1, clock42Mhz);
//
registrador Us(0);
registrador Ds(0);
registrador Um(0);
registrador Dm(0);
//
switche botao3(gpio_PTB9),botao7(gpio_PTB11);

switche permission(gpio_PTE5);

controlador service_edit;

IncrementService service_inc;

CozimentoService service_coz;

char key;
int valor=0;

extern "C" {

	void UART0_IRQHandler() {
		buf = bt.receive8Bits();
	}
	void SysTick_Handler(void) {
//		buf = bt.receive8Bits();
		keyboard.update();
		key = keyboard.getKey();
		if(keyboard.keyIsPressed()){
			valor=key;
		}

	}
}


void setupBluetooth() {
	bt.setInterruptMode(uart_Rx);
	bt.setPriority(uart_Priority0);
	bt.enableInterrupt();
}


int main(){
	__disable_irq();
	setupBluetooth();  //! Configura o periférico bluetooth
	__enable_irq();
	while(1){
		service_edit.maq_est(keyboard.keyIsPressed(),!permission.read());
		service_edit.select_service();
		service_edit.do_service(&Dm,&Um,&Ds,&Us,valor);



    	service_inc.machineState(botao3.isOn(),botao7.isOn(),!permission.read());
    	service_inc.selectService();
    	service_inc.doService(&Dm,&Um,&Ds,&Us);
//
//
    	if(aux!=buf){
    		aux=buf;
    		service_coz.machineState(aux,1);
			service_coz.selectService();
			service_coz.doService(&Dm,&Um,&Ds,&Us);
    	}



		display.monitora(Dm.leValor(),Um.leValor(),Ds.leValor(),Us.leValor());

	}
	return 0;
}
