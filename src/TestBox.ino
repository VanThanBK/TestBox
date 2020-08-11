#include "homephone.h"
#include "LCD12864Menu.h"
#include "EncoderButtonLib.h"
#include "BuzzerLib.h"

homephone Screens(PB8, PB6, PB7, PB5); // sdin, slk, a, rst
EncoderButtonLib ControlKnob(PB1, PB0, PA7);
BuzzerLib Buzzer(PA6);

void setup() {
    Serial.begin(115200);

    //Screens.print("than");

    ControlKnob.Init();
    Buzzer.Init();

    attachInterrupt(ControlKnob.CLK_PIN, Handler, CHANGE);
}

void loop() {
    if (ControlKnob.IsPressed())
    {
        Serial.println("Pressed!");
        Buzzer.Bip();
    }
    Buzzer.Execute();
}

void Handler()
{
    ControlKnob.Handler();
}