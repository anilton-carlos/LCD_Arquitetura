/*
 * digital.h
 *
 *  Created on: Dec 3, 2019
 *      Author: anilton
 */

#ifndef SOURCES_CLASSES_DIGITAL_H_
#define SOURCES_CLASSES_DIGITAL_H_

#include "stdint.h"
#include "devices.h"

class TimeDecoder
{
private:
    uint8_t time_out[4];

public:
    TimeDecoder()
    {
        for (uint8_t i; i < 4; i++)
            time_out[i] = 32;
    }

    void setInput(uint8_t time_in[4])
    {
        if (time_in[0] == 0)
        {
            time_out[0] = 32;
            if (time_in[1] == 0)
                time_out[1] = 32;
            else
                time_out[1] = time_in[1] + 48;
        }
        else
        {
            time_out[0] = time_in[0] + 48;
            time_out[1] = time_in[1] + 48;
        }
        time_out[2] = time_in[2] + 48;
        time_out[3] = time_in[3] + 48;
    }

    uint8_t *getOutput()
    {
        return time_out;
    }
};

typedef enum
{
    e,
    pp,
    pz,
    la,
    i3,
    i5,
    i7
} cookOption;
class CookDecoder
{
private:
    string cook_out;

public:
    CookDecoder()
    {
        cook_out = "        ";
    }
    void setInput(uint8_t cook_in)
    {
        switch (cook_in)
        {
        case e:
            cook_out = " EDICAO ";
            return;
        case pp:
            cook_out = " PIPOCA ";
            return;
        case pz:
            cook_out = " PIZZA  ";
            return;
        case la:
            cook_out = "LASANHA ";
            return;
        case i3:
            cook_out = " INC+3  ";
            return;
        case i5:
            cook_out = " INC+5  ";
            return;
        case i7:
            cook_out = " INC+7  ";
            return;
        default:
            cook_out = "        ";
            return;
        }
        cook_out = cook_in;
    }
    string getOutput()
    {
        return cook_out;
    }
};

class OperDecoder
{
private:
    string oper_out[3];

public:
    OperDecoder()
    {
        for (uint8_t i = 0; i < 3; i++)

            oper_out[i] = "   ";
    }
    void setInput(bool oper_in[3])
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            if (oper_in[i])
                oper_out[i] = "ON ";
            else
                oper_out[i] = "OFF";
        }
    }

    string getOutput()
    {
        return *oper_out;
    }
};

class Timer
{
private:
    uint8_t time[4];
    bool enableDecrement;
    void ula(bool operation, uint8_t input)
    {
        uint8_t vaiUm[3] = {0, 0, 0};
        /*
         * operation == 0 : Subtração
         * operation == 1 : Soma
         */
        if (operation)
        {
            time[3] += input;
            if (time[3] > 9)
            {
                vaiUm[2] = time[3] / 10;
                time[2] += vaiUm[2];

                if (time[2] > 5)
                {
                    vaiUm[1] = time[2] / 10;
                    time[1] += vaiUm[1];

                    if (time[1] > 9)
                    {
                        vaiUm[0] = time[1] / 10;
                        time[0] += vaiUm[0];
                    }
                }
            }
        }
    }

public:
    Timer()
    {
        enableDecrement = 0;
        for (uint8_t i = 0; i < 4; i++)
            time[i] = 0;
    }

    void enableTimer(bool input)
    {
        enableDecrement = input;
    }

    void setTime(uint8_t time_in[4])
    {
        if (!enableDecrement)
            for (uint8_t i = 0; i < 4; i++)
                time[i] = time_in[i];
    }

    uint8_t getTime()
    {
        return *time;
    }

    void increment(cookOption inc)
    {
        switch (inc)
        {
        case i3:

            break;

        default:
            break;
        }
    }

    void decrementTime()
    {
        if (enableDecrement)
        {
            if (!(time[0] == 0 && time[1] == time[2] == time[3]))
            {
            }
            else
                enableDecrement = 0;
        }
    }
};
#endif /* SOURCES_CLASSES_DIGITAL_H_ */
