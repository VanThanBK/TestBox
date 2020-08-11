//EncoderButtonLib.h

#ifndef _ENCODERBUTTONLIN_h
#define _ENCODERBUTTONLIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define SCALE_NUMBER 1
#define NOISE_REDUCTION_TIME 100
#define BUTTON_RESPONSE_SPEED 300

#define ENCODER_CW 1
#define ENCODER_CCW -1

class EncoderButtonLib
{
private:
    /* data */
    int32_t PulsesNumber;
    int32_t PulsesNumberWhenPressing;
    uint8_t ScaleNumber;
    int EncoderDirection;
    bool IsButtonPressing;

    uint32_t LastTimeButton;
    uint32_t LastTimeButtonPressed;
    uint16_t ButtonResponseSpeed;
    
public:
    EncoderButtonLib(uint8 sw_pin, uint8 dt_pin, uint8 clk_pin)
    {
        SW_PIN = sw_pin;
        DT_PIN = dt_pin;
        CLK_PIN = clk_pin;
    }
    /*
        SW_PIN
        DT_PIN
        CLK_PIN
    */

    void Init();
    bool IsPressed();
    int EncoderMoved();
    int EncoderMovedWhenPressing();

    void SetEncoderScale(uint8_t scaleNumber);
    void SetEncoderDirection(int dir);
    void SetButtonResponseSpeed(uint16_t millisspeed);

    void Handler();

    uint8 SW_PIN, DT_PIN, CLK_PIN;
};

#endif