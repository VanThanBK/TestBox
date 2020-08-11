#include "BuzzerLib.h"

void BuzzerLib::Init()
{
    MelodyIndex = 0;
    NoteBip = NOTE_BIP;
    TimeBip = TIME_BIP;

    IsPlay = false;
    IsPlayLoop = false;
    IsBip = false;
    IsPlayCurrentNote = false;

    Melody = new uint16_t[8]{NOTE_C6, NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G3, NOTE_B4, NOTE_B7, NOTE_C8};
    NoteDurations = new uint16_t[8]{4, 8, 8, 4, 4, 2, 4, 4 };
    NumberNotes = 8;
}

void BuzzerLib::PlayOneNote()
{
    if (!IsPlayCurrentNote)
    {
        uint16_t duration = 1000 / NoteDurations[MelodyIndex];
        tone(BuzzerPin, Melody[MelodyIndex], duration);
        TimeDelayAfterNote = duration + 30;
        IsPlayCurrentNote = true;
        MelodyIndex ++;
        LastTimePlayNote = millis();
    }

    if (millis() - LastTimePlayNote > TimeDelayAfterNote)
    {
        IsPlayCurrentNote = false;
    }
}

void BuzzerLib::AddBeat(uint16_t* melody, uint16_t* noteDurations, uint8_t numberNotes)
{
    if (Melody != NULL)
	{
		delete[] Melody;
	}
    Melody = melody;
    if (NoteDurations != NULL)
	{
		delete[] NoteDurations;
	}
    NoteDurations = noteDurations;
    NumberNotes = numberNotes;
}

void BuzzerLib::AddTone(uint16_t tone, uint16_t time)
{
    NoteBip = tone;
    TimeBip = time;
}

void BuzzerLib::AddTone(uint16_t tone)
{
    NoteBip = tone;
}

void BuzzerLib::Bip()
{
    IsBip = true;
    if (IsBip)
    {
        tone(BuzzerPin, NoteBip, TimeBip);
        IsBip = false;
    }
}

void BuzzerLib::Play()
{
    IsPlay = true;
}

void BuzzerLib::PlayLoop()
{
    IsPlayLoop = true;
}

void BuzzerLib::StopLoop()
{
    IsPlayLoop = false;
}

void BuzzerLib::Execute()
{
    if (IsPlay && !IsPlayLoop)
    {
        if (MelodyIndex == NumberNotes)
        {
            MelodyIndex = 0;
            IsPlay = false;
        }

        PlayOneNote();      
    }
    
    if (IsPlayLoop)
    {
        if (MelodyIndex == NumberNotes)
        {
            MelodyIndex = 0;
        }

        PlayOneNote();      
    }
}