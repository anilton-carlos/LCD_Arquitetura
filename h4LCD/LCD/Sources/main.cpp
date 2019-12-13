#include "MKL25Z4.h"
#include "./Bibliotecas/Systick/mkl_SystickPeriodicInterrupt.h"
#include "./Classes/services.h"
#include "./Classes/monitor.h"
#include "./Classes/devices.h"

//MONITOR
MonitorLCD LCDTimerMonitor = MonitorLCD();

/*
 * SYSTICK TIMER
 */
mkl_SystickPeriodicInterrupt systick = mkl_SystickPeriodicInterrupt(10, clock42Mhz);

uint8_t tempo[4] = {0, 2, 0, 0};
// BOTOES DE ENTRADA
Button PlayPause = Button(gpio_PTD4);
Button Cancel = Button(gpio_PTA12);
Button TempoB = Button(gpio_PTA4);
Button CookOperB = Button(gpio_PTA5);
uint8_t trocaT = 0, trocaCO = 0;
bool oper[3] = {1, 0, 1};
cookOption cookOpt = ed;
enableType state = play;
uint8_t debounce = 0;
extern "C"
{
    void SysTick_Handler(void)
    {
        LCDTimerMonitor.doServiceFromIRQ();

        // ENTRADAS PARA TESTE:
        if (PlayPause.readButton() == 0)
        {
            LCDTimerMonitor.monMemory.setAction(state);
            if (state == pause)
                state = play;
            else
                state = pause;
        }

        if (Cancel.readButton() == 0)
        {
            LCDTimerMonitor.monMemory.setCancelAction(1);
        }

        if (TempoB.readButton() == 0)
        {
            if (trocaT == 0)
            {
                tempo[3] = 0;
                tempo[2] = 2;
                tempo[1] = 0;
                tempo[0] = 0;
            }

            else if (trocaT == 1)
            {
                tempo[3] = 5;
                tempo[2] = 0;
                tempo[1] = 8;
                tempo[0] = 0;
            }
            else if (trocaT == 2)
            {
                tempo[3] = 0;
                tempo[2] = 3;
                tempo[1] = 0;
                tempo[0] = 0;
            }

            trocaT++;
            if (trocaT == 3)
                trocaT = 0;

            LCDTimerMonitor.monMemory.setTempoGeral(tempo);
        }

        if (CookOperB.readButton() == 0)
        {
            if (debounce)
            {
                if (trocaCO == 0)
                {
                    cookOpt = ed;
                    oper[0] = 0;
                    oper[1] = 0;
                    oper[2] = 0;
                }
                else if (trocaCO == 1)
                {
                    cookOpt = pp;
                    oper[0] = 0;
                    oper[1] = 0;
                    oper[2] = 1;
                }
                else if (trocaCO == 2)
                {
                    cookOpt = pz;
                    oper[0] = 0;
                    oper[1] = 1;
                    oper[2] = 0;
                }
                else if (trocaCO == 3)
                {
                    cookOpt = la;
                    oper[0] = 0;
                    oper[1] = 1;
                    oper[2] = 1;
                }
                else if (trocaCO == 4)
                {
                    cookOpt = i3;
                    oper[0] = 1;
                    oper[1] = 0;
                    oper[2] = 0;
                }
                else if (trocaCO == 5)
                {
                    cookOpt = i5;
                    oper[0] = 1;
                    oper[1] = 0;
                    oper[2] = 1;
                }

                LCDTimerMonitor.monMemory.setCookGeral(cookOpt);
                LCDTimerMonitor.monMemory.setOperGeral(oper);
                trocaCO++;
                if (trocaCO == 6)
                {
                    trocaCO = 0;
                }
            }
            debounce++;
            if (debounce == 10)
                debounce = 0;
        }
        // FIM ENTRADAS PARA TESTE
    }
}

int main(void)
{

    LCDTimerMonitor.monMemory.setTempoGeral(tempo);
    LCDTimerMonitor.monMemory.setOperGeral(oper);
    LCDTimerMonitor.monMemory.setCookGeral(ed);
    while (1)
    {
        LCDTimerMonitor.doService();
    }
}
