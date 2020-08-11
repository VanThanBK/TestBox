#include "EncoderButtonLib.h"

void EncoderButtonLib::Init()
{
    pinMode(SW_PIN, INPUT_PULLUP);
    pinMode(DT_PIN, INPUT_PULLUP);
    pinMode(CLK_PIN, INPUT_PULLUP);
    ScaleNumber = SCALE_NUMBER;
    PulsesNumber = 0;
    PulsesNumberWhenPressing = 0;
    EncoderDirection = ENCODER_CW;
    IsButtonPressing = false;
    ButtonResponseSpeed = BUTTON_RESPONSE_SPEED ;
}

void EncoderButtonLib::SetEncoderScale(uint8_t scale)
{
    ScaleNumber = scale;
}

void EncoderButtonLib::SetEncoderDirection(int dir)
{
    EncoderDirection = dir;
}

void EncoderButtonLib::SetButtonResponseSpeed(uint16_t millisspeed)
{
    ButtonResponseSpeed = millisspeed;
}

bool EncoderButtonLib::IsPressed()
{
    if (digitalRead(SW_PIN))
    {
        LastTimeButton = millis();
        return false;
    }
    
    if (millis() - LastTimeButtonPressed > ButtonResponseSpeed)
    {
        if (millis() - LastTimeButton > NOISE_REDUCTION_TIME)
        {
            LastTimeButtonPressed = millis();
            return true;
        }
        else
        {
            return false;
        }   
    }
    else
    {
        return false;
    }
}

int EncoderButtonLib::EncoderMoved()
{
    int pulse = PulsesNumber / ScaleNumber;
    if (pulse != 0)
    {
        PulsesNumber = PulsesNumber - (pulse * ScaleNumber);
    }
    return pulse;
}

int EncoderButtonLib::EncoderMovedWhenPressing()
{
    int pulse = PulsesNumberWhenPressing / ScaleNumber;
    if (pulse != 0)
    {
        PulsesNumberWhenPressing = PulsesNumberWhenPressing - (pulse * ScaleNumber);
    }
    return pulse;
}

void EncoderButtonLib::Handler()
{
    if (digitalRead(SW_PIN) == 0)
    {
        if (digitalRead(DT_PIN) == digitalRead(CLK_PIN))
        {
            PulsesNumberWhenPressing += EncoderDirection;
        } 
        else
        {
            PulsesNumberWhenPressing -= EncoderDirection;
        }
    }
    else
    {
        if (digitalRead(DT_PIN) == digitalRead(CLK_PIN))
        {
            PulsesNumber += EncoderDirection;
        } 
        else
        {
            PulsesNumber -= EncoderDirection;
        }
    }
}